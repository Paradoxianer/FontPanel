/*
 * Copyright 2017 Paradoxon
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef FONT_VIEW_H
#define FONT_VIEW_H


#include <SupportDefs.h>
#include <CheckBox.h>
#include <PopUpMenu.h>
#include <private/interface/ColorMenuItem.h>
#include <private/interface/DecimalSpinner.h>

#include "FontListView.h"
#include "FontPanel.h"
#include "FontPreview.h"

class FontView : public BView{

	public:
		FontView(font_panel_mode mode = FONT_PANEL,
			const BFont *font = be_plain_font,
			const BString *prevString = new BString(PREVIEW_STR),
			BMessenger *target = NULL,
			BMessage *message = NULL,
			bool live_update = true);
		~FontView(void);
		
		void			Init(void);
		void			AttachedToWindow();
		BMessenger		Messenger(void) const;

		void			SetTarget(BMessenger target);
		void			SetMessage(BMessage *message);
	
		void			SetFont(const BFont &font);
		void			ChangeFont(const BFont &font);

		BFont*			Font(void) const;
		status_t		SetFamilyAndStyle(const font_family family,
							const font_style style);
		status_t		SetFamilyAndFace(const font_family family,
							uint16 face);
		void			SetFontSize(uint16 size);
		
		void			MessageReceived(BMessage* message);
		
					
	private:
		BFont			_FindFontForFace(const BFont &font,uint16 face) const;
		uint16			_FaceFromUI();
		
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

		BSpinner		*fSpacing;
	
		FontPreview		*fPreview;
		
		BString			fTypeAhead;
		
		BFont			fFont;
		//Book?
		//Condensed?
		//Oblique?


};


#endif // FONT_VIEW_H
