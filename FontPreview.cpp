#include <stdlib.h>

#include "FontPreview.h"
#include "FontPanel.h"


FontPreview::FontPreview()
 :	BView("fontpreview",B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP),
 	fPreviewText(PREVIEW_STR),
 	fShapes(NULL)
{
	SetFlags(B_WILL_DRAW);
	SetDrawingMode(B_OP_COPY);
	_RecalcSize();
}


void
FontPreview::SetPreviewText(const char *text)
{
	if (fPreviewText.Compare(text) != 0) {
		fPreviewText = text;
		BFont font;
		GetFont(&font);
		if ((font.Face() & B_OUTLINED_FACE) != 0){
			_AddShapes(fPreviewText);
			font.GetGlyphShapes(fPreviewText, fPreviewText.CountChars(), fShapes);
			//if so we need ot get the escapements to calculate it right
		}
		_RecalcSize();
		Invalidate();
	}
}


const char *
FontPreview::PreviewText(void) const
{
	return fPreviewText.String();
} 


void
FontPreview::SetFont(const BFont* font,uint32 mask)
{
	
	if ((font->Face() & B_OUTLINED_FACE) != 0){
			_AddShapes(fPreviewText);
			font->GetGlyphShapes(fPreviewText, fPreviewText.CountChars(), fShapes);
			//if so we need ot get the escapements to calculate it right
	}
	_RecalcSize();
	BView::SetFont(font,mask);
	Invalidate();
}


void
FontPreview::Draw(BRect r)
{
	BFont font;
	GetFont(&font);
	font.PrintToStream();
	int32 width = (int32)font.StringWidth(fPreviewText.String());	
	BPoint drawpt;
	if (width < Bounds().IntegerWidth())
		drawpt.x = (Bounds().IntegerWidth() - width) / 2;
	else
		drawpt.x = 10;
	
	font_height fheight;
	font.GetHeight(&fheight);
	int32 fullHeight = (int32)(fheight.ascent + fheight.descent + fheight.leading);
	
	if (fullHeight < Bounds().IntegerHeight() - 10)
		drawpt.y = (Bounds().IntegerHeight() + fheight.ascent) / 2;
	else
		drawpt.y = Bounds().bottom - 10;
	
	BRect rect = Bounds();
	rgb_color hColor = HighColor();
	SetHighColor(255,255,255,255);
	FillRect(rect);
	SetHighColor(hColor);
	
	if ((font.Face() & B_OUTLINED_FACE) != 0){
		for (size_t i = 0; i < fPreviewText.CountChars(); i++) {
			MovePenTo(drawpt);
			SetHighColor(255,255,255,255);
			FillShape(fShapes[i]);
			SetPenSize(1.5);
			SetHighColor(0, 0, 0);
			StrokeShape(fShapes[i]);
			//**calulate the starting point of the next letter
		}
	}
	else
		DrawString(fPreviewText.String(), drawpt);
}

void
FontPreview::_AddShapes(BString string)
{
	const size_t size = string.CountChars();
	fShapes = (BShape**)malloc(sizeof(BShape*) * size);

	for (size_t i = 0; i < size; i++) {
		fShapes[i] = new BShape();
	}
}

void
FontPreview::_RecalcSize(void)
{
	BFont font;
	font_height fheight;

	GetFont(&font);
	font.GetHeight(&fheight);
	int32 fullHeight = (int32)(fheight.ascent + fheight.descent + fheight.leading+20);
	SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, fullHeight));
}

