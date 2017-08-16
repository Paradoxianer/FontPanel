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
			.Add(fFontListView,100)
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
	fBold				= new BCheckBox("Bold",B_TRANSLATE("Bold"),new BMessage(M_BOLD_CHANGED));
	fItalic				= new BCheckBox("Italic",B_TRANSLATE("Italic"), new BMessage(M_ITALIC_CHANGED));
		
	fStrikeOut			= new BCheckBox("StrikeOut",B_TRANSLATE("strike out"), new BMessage(M_STRIKE_OUT_CHANGED));
	fUnderline			= new BCheckBox("Underline",B_TRANSLATE("underline"), new BMessage(M_UNDERLINE_CHANGED));

	//tab Font tab Color tab more (shear, rotation, spacing and so on)
	
	fForeGroundColor	= new BPopUpMenu(B_TRANSLATE("foreground color"), true, true, B_ITEMS_IN_MATRIX);
	fFillColor			= new BPopUpMenu(B_TRANSLATE("fill color"), true, true, B_ITEMS_IN_MATRIX);
	fBackGroundColor	= new BPopUpMenu(B_TRANSLATE("background color"), true, true, B_ITEMS_IN_MATRIX);
	
	fSize				= new BDecimalSpinner("size", B_TRANSLATE("size"),new BMessage(M_SIZE_CHANGED));

	fOutline			= new BDecimalSpinner("outline", B_TRANSLATE("outline"),new BMessage(M_OUTLINE_CHANGED));
	
	fShear				= new BDecimalSpinner("shear", B_TRANSLATE("shear"),new BMessage(M_SHEAR_CHANGED));
	fSpacing			= new BDecimalSpinner("spacing", B_TRANSLATE("spacing"),new BMessage(M_SPACING_CHANGED));
	
	fPreview			= new FontPreview();
	
	fTypeAhead			= BString();
}



BMessenger
FontView::Messenger() const
{}

void
FontView::SetTarget(BMessenger target)
{}

void
FontView::SetMessage(BMessage *message)
{}
	
void 
FontView::SetFont(const BFont &font)
{}

status_t
FontView::SetFamilyAndStyle(const font_family family,
							const font_style style)
{}

status_t
FontView::SetFamilyAndFace(const font_family family,
							uint16 face)
{}

void
FontView::SetFontSize(uint16 size)
{}
		
void
FontView::MessageReceived(BMessage* message)
{}
