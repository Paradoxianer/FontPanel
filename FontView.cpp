/*
 * Copyright 2017 Paradoxon
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include <Catalog.h>
#include <GroupLayout.h>
#include <GroupLayoutBuilder.h>
#include <GridLayoutBuilder.h>
#include <ScrollView.h>
#include <SpaceLayoutItem.h>

#include "FontView.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "FontView"

FontView::FontView(font_panel_mode mode,
			const BFont *font,
			const BString *prevString,
			BMessenger *target,
			BMessage *message,
			bool live_update)
			:BView("FontView",
				B_FOLLOW_ALL_SIDES,
				0)
{
	Init();
	SetLayout(new BGroupLayout(B_VERTICAL));
	AddChild(BGroupLayoutBuilder(B_VERTICAL)
		.Add(BGroupLayoutBuilder(B_HORIZONTAL)
			.Add(new BScrollView("fontListScroller",fFontListView,B_FOLLOW_ALL_SIDES, 0, false, true),100)
			//.Add(fFontListView,100)
			)
		.Add(BGridLayoutBuilder()
			.Add(BSpaceLayoutItem::CreateGlue(),0,0)
			.Add(fSize->CreateLabelLayoutItem(),1,0)
			.Add(fSize->CreateTextViewLayoutItem(),2,0)
			.Add(BSpaceLayoutItem::CreateGlue(),0,1)
			.Add(fOutline->CreateLabelLayoutItem(),1,1)
			.Add(fOutline->CreateTextViewLayoutItem(),2,1)
			.Add(BSpaceLayoutItem::CreateGlue(),0,2)
			.Add(fShear->CreateLabelLayoutItem(),1,2)
			.Add(fShear->CreateTextViewLayoutItem(),2,2)
			.Add(fBold,3,0)
			.Add(fItalic,3,1)
			.Add(fStrikeOut,4,0)
			.Add(fUnderline,4,1)
			.Add(BSpaceLayoutItem::CreateGlue(),5,0)
			.Add(BSpaceLayoutItem::CreateGlue(),5,1)
			.Add(BSpaceLayoutItem::CreateGlue(),5,2)
			.SetInsets(10,10,10,10),1
			)
		//.Add(new BScrollView("previewScroller",fPreview,B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, true, true),1)
		.Add(fPreview,1)
		.SetInsets(10,10,10,10)
		);
}

FontView::~FontView(void)
{}

void
FontView::Init()
{
	fFontListView		= new FontListView();
	fFontListView->SetResizingMode(B_FOLLOW_ALL_SIDES);
	fBold				= new BCheckBox("Bold",B_TRANSLATE("Bold"),new BMessage(M_BOLD_CHANGED));
	fItalic				= new BCheckBox("Italic",B_TRANSLATE("Italic"), new BMessage(M_ITALIC_CHANGED));
		
	fStrikeOut			= new BCheckBox("StrikeOut",B_TRANSLATE("strike out"), new BMessage(M_STRIKE_OUT_CHANGED));
	fUnderline			= new BCheckBox("Underline",B_TRANSLATE("underline"), new BMessage(M_UNDERLINE_CHANGED));

	//tab Font tab Color tab more (shear, rotation, spacing and so on)
	
	fForeGroundColor	= new BPopUpMenu(B_TRANSLATE("foreground color"), true, true, B_ITEMS_IN_MATRIX);
	fFillColor			= new BPopUpMenu(B_TRANSLATE("fill color"), true, true, B_ITEMS_IN_MATRIX);
	fBackGroundColor	= new BPopUpMenu(B_TRANSLATE("background color"), true, true, B_ITEMS_IN_MATRIX);
	
	fSize				= new BDecimalSpinner("size", B_TRANSLATE("size"),new BMessage(M_SIZE_CHANGED));
	fSize->SetMaxValue(2000);

	fOutline			= new BDecimalSpinner("outline", B_TRANSLATE("outline"),new BMessage(M_OUTLINE_CHANGED));
	
	fShear				= new BDecimalSpinner("shear", B_TRANSLATE("shear"),new BMessage(M_SHEAR_CHANGED));
	fSpacing			= new BSpinner("spacing", B_TRANSLATE("spacing"),new BMessage(M_SPACING_CHANGED));
	
	fPreview			= new FontPreview();
		
	fTypeAhead			= BString();
}

void
FontView::AttachedToWindow()
{
	fFontListView->SetTarget(this);
	fFontListView->SetSelectionMessage(new BMessage(M_FAMILY_CHANGED));
	fBold->SetTarget(this);
	fItalic->SetTarget(this);
		
	fStrikeOut->SetTarget(this);
	fUnderline->SetTarget(this);

	fSize->SetTarget(this);

	fOutline->SetTarget(this);
	
	fShear->SetTarget(this);
	fSpacing->SetTarget(this);
}

BMessenger
FontView::Messenger() const
{

}

void
FontView::SetTarget(BMessenger target)
{}

void
FontView::SetMessage(BMessage *message)
{}
	
void 
FontView::SetFont(const BFont &font)
{
	ChangeFont(&font);

	font_family family;
	font_style	style;
	uint16		face;
	font.GetFamilyAndStyle(&family, &style);
	face = font.Face();
	fFontListView->SelectFont(family);
	fBold->SetValue(face & B_BOLD_FACE);
	fItalic->SetValue(face & B_ITALIC_FACE);
	fStrikeOut->SetValue(face & B_STRIKEOUT_FACE);
	fUnderline->SetValue(face & B_UNDERSCORE_FACE);
	//tab Font tab Color tab more (shear, rotation, spacing and so on)
	/*
		BPopUpMenu		*fForeGroundColor;
		BPopUpMenu		*fFillColor;
		BPopUpMenu		*fBackGroundColor;
	*/
	fSize->SetValue(font.Size());
	fOutline->SetValue(int32(face & B_OUTLINED_FACE));
	fShear->SetValue(font.Shear());
	fSpacing->SetValue(font.Spacing());
}

void 
FontView::ChangeFont(const BFont &font)
{
	BView::SetFont(&font,B_FONT_ALL);
	fPreview->SetFont(&font);
}

BFont*
FontView::Font(void) const
{
	return const_cast<BFont*>(&fFont);
}

status_t
FontView::SetFamilyAndStyle(const font_family family,
							const font_style style)
{}

status_t
FontView::SetFamilyAndFace(const font_family family,
							uint16 face)
{
}

void
FontView::SetFontSize(uint16 size)
{
}
		
void
FontView::MessageReceived(BMessage* message)
{
	BFont	font;
	uint16	face = font.Face();
	GetFont(&font);
	switch (message->what) {
		case M_SIZE_CHANGED:
			font.SetSize(fSize->Value());
			break;
		case M_FAMILY_CHANGED:{
				FontItem* item;
				int32 selected;
				int32 i = 0;
				while ( (selected = fFontListView->CurrentSelection(i)) >= 0 ) {
   					item = (FontItem*)fFontListView->ItemAt(selected);
   					char* family = item->GetFamily();
					font.SetFamilyAndFace(family,_FaceFromUI());
					i++;
				}
				font=_FindFontForFace(font,_FaceFromUI());
				font.SetFace(face);
 			}
			break;
		case M_BOLD_CHANGED:
				if (fUnderline->Value() != 0)
					face = face | B_BOLD_FACE;
				else
					face = face & (~B_BOLD_FACE);
				font=_FindFontForFace(font,_FaceFromUI());
			break;
		case M_ITALIC_CHANGED:
				if (fUnderline->Value() != 0)
					face = face | B_ITALIC_FACE;
				else
					face = face & (~B_ITALIC_FACE);
				font=_FindFontForFace(font,_FaceFromUI());
			break;
		case M_STRIKE_OUT_CHANGED:
				if (fUnderline->Value() != 0)
					face = face | B_STRIKEOUT_FACE;
				else
					face = face & (~B_STRIKEOUT_FACE);
			break;
		case M_UNDERLINE_CHANGED:
				if (fUnderline->Value() != 0)
					face = face | B_UNDERSCORE_FACE;
				else
					face = face & (~B_UNDERSCORE_FACE);
			break;
		case M_FORE_GROUND_COLOR_CHANGED:
		case M_FILL_COLOR_CHANGED:
		case M_BACK_GROUND_COLOR_CHANGED:
		case M_OUTLINE_CHANGED:
			if (fOutline->Value() != 0)
				face = face | B_OUTLINED_FACE;
			else
				face = face & (~B_OUTLINED_FACE);
			break;
		case M_SHEAR_CHANGED:
		case M_SPACING_CHANGED:
		case M_ROTATION_CHANGED:
			break;
		default:  {
			BView::MessageReceived(message);
			break;
		}
	}
	ChangeFont(font);
}


BFont
FontView::_FindFontForFace(const BFont &font,uint16 face) const
{
	//** later maybe better implmeentation to calculate wich style
	// is the closest to the selected one...
	BFont newFont(font);
	font_family family;
	font_style style;
	font.GetFamilyAndStyle(&family, &style);
	int32 styleCount = count_font_styles(family);
	for (int32 i = 0; i < styleCount; i++) {
		uint16 styleFace;
		if (get_font_style(family, i, &style, &styleFace) == B_OK) {
			if (styleFace == face) {
				newFont.SetFamilyAndStyle(family, style);
				return newFont;
			}
		}
	}
	return newFont;
}

uint16
FontView::_FaceFromUI()
{
	uint16 face=0;
	if (fBold->Value() != 0)
		face = face | B_BOLD_FACE;
	if (fItalic->Value() != 0)
		face = face | B_ITALIC_FACE;
	if (face == 0)
		face = B_REGULAR_FACE;
	return face;
	
}
