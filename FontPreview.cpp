#include "FontPreview.h"


FontPreview::FontPreview()
 :	BView("fontpreview",B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP),
 	fPreviewText(PREVIEW_STR)
{
	SetFlags(B_WILL_DRAW);
}


void
FontPreview::SetPreviewText(const char *text)
{
	fPreviewText = text ? text : PREVIEW_STR;
}


const char *
FontPreview::PreviewText(void) const
{
	return fPreviewText.String();
} 


void
FontPreview::Draw(BRect r)
{
	BFont font;
	GetFont(&font);
	int32 width = (int32)font.StringWidth(fPreviewText.String());
	
	BPoint drawpt;
	if (width < Bounds().IntegerWidth())
		drawpt.x = (Bounds().IntegerWidth() - width) / 2;
	else
		drawpt.x = 10;
	
	font_height fheight;
	font.GetHeight(&fheight);
	int32 size = (int32)(fheight.ascent + fheight.descent + fheight.leading);
	
	if (size < Bounds().IntegerHeight() - 10)
		drawpt.y = (Bounds().IntegerHeight() + fheight.ascent) / 2;
	else
		drawpt.y = Bounds().bottom - 10;
	SetDrawingMode(B_OP_COPY);
	BRect rect = Bounds();
	rgb_color hColor = HighColor();
	SetHighColor(ViewColor());
	FillRect(rect);
	SetHighColor(hColor);
	DrawString(fPreviewText.String(), drawpt);
}
