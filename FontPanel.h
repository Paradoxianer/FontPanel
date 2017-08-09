/*
 * Copyright 2017, Paradoxon. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */

#ifndef FONT_PANEL_H
#define FONT_PANEL_H

#include <Font.h>
#include "FontView.h"

class BMessage;
class BMessenger;
class BWindow;

enum font_panel_mode {
	FONT_PANEL,
	MIN_FONT_PANEL
	MAX_FONT_PANEL
};

enum font_panel_button {
	B_CANCEL_BUTTON,
	B_DEFAULT_BUTTON
};

enum
{
	M_FONT_SELECTED='mfsl'
};

enum
{
	M_OK = 'm_ok',
	M_CANCEL,
	M_SIZE_CHANGED,
	M_FAMILY_SELECTED,
	M_STYLE_SELECTED,
	M_HIDE_WINDOW
};




class FontPanel {
	public:
		FontPanel(font_panel_mode = FONT_PANEL,
			BMessenger *target = NULL,
			const BFont* font	= NULL,
			const BString *prevString = NULL,
			BMessage *message = NULL,
			bool modal = false,
			bool hide_when_done = true);
		virtual			~FontPanel(void);
	
		void			Show();
		void			Hide();
		bool			IsShowing(void) const;
	
		virtual void	WasHidden();
		virtual void	SelectionChanged();
		virtual void	SendMessage(const BMessenger* target, BMessage* message);
	
		BWindow*		Window() const;
		BMessenger		Messenger() const;
	
		font_panel_mode	PanelMode() const;
		void			SetTarget(BMessenger target);
		void			SetMessage(BMessage *message);
	
	
		void			SetFont(const BFont &font);
		statust_t		SetFamilyAndStyle(const font_family family,
							const font_style style);
		status_t		SetFamilyAndFace(const font_family family,
							uint16 face);
		void			SetSize(uint16 size);
		
		
		
		void			SetButtonLabel(font_panel_button button, const char* label);							
		
		void			SetHideWhenDone(bool hideWhenDone);
		bool			HidesWhenDone(void) const;
		void			Refresh();

	
private:
		BWindow			*fWindow;
		FontView		*fFontView;
};

#endif  /* FONT_PANEL_H */
