/*
 * Copyright 2017 Paradoxon
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef FONT_VIEW_H
#define FONT_VIEW_H


#include <SupportDefs.h>
#include <CheckBox.h>
#include <PopUpMenu.h>
#include <private/interface/DecimalSpinner.h>
#include "FontListView.h"
#include "FontPanel.h"


class FontView {

	public:
		FontView(font_panel_mode mode,	BMessenger *target,
			const BFont *font,
			const BString *prevString ,
			BMessage *message,
			bool live_update);
		~FontView(void);
		
		BMessenger		Messenger() const;

		void			SetTarget(BMessenger target);
		void			SetMessage(BMessage *message);
	
		void			SetFont(const BFont &font);
		status_t		SetFamilyAndStyle(const font_family family,
							const font_style style);
		status_t		SetFamilyAndFace(const font_family family,
							uint16 face);
		void			SetSize(uint16 size);
			
	private:
		
		FontListView	*fFontListView;
		BCheckBox		*fBold;
		BCheckBox		*fItalic;
			
		BCheckBox		*fStrikeOut;
		BCheckBox		*fUnderline;

	//tab Font tab Color tab more (shear, rotation, spacing and so on)
	
		BPopUpMenu		*fForeGroundColor;
		BPopUpMenu		*fFillColor;
		BPopUpMenu		*fBackGroundColor;
	
		BDecimalSpinner	*fSize;
	
		BDecimalSpinner	*fOutline;
		
		BDecimalSpinner	*fShear;

		BDecimalSpinner	*fSpacing;
	
		//Book?
		//Condensed?
		//Oblique?


};


#endif // FONT_VIEW_H
