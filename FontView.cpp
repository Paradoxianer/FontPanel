/*
 * Copyright 2017 Paradoxon
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include <Catalog.h>

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
		
		fFontListView = new FontListView();
		fBold = new BCheckBox("Bold",B_TRANSLATE("Bold"),new BMessage(M_BOLD_CHANGED));
		fItalic= new BCheckBox("Italic",B_TRANSLATE("Italic", new BMessage(M_ITALIC_CHANGED));
			
		fStrikeOut = new BCheckBox("StrikeOut",B_TRANSLATE("strike out", new BMessage(M_STRIKE_OUT_CHANGED));
		fUnderline; = new BCheckBox();

	//tab Font tab Color tab more (shear, rotation, spacing and so on)
	
		fForeGroundColor = new BPopUpMenu;
		fFillColor = new BPopUpMenu();
		fBackGroundColor = new BPopUpMenu();
	
		fSize = new BDecimalSpinner();
	
		fOutline = new BDecimalSpinner();
		
		fShear = new BDecimalSpinner();

		fSpacing; = new BDecimalSpinner();
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
FontView::MessageReceived(BMessage* message)
{}
