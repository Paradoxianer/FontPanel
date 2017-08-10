/*
 * Copyright 2017, Paradoxon. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */

#ifndef FONT_PANEL_H
#define FONT_PANEL_H

#include <Font.h>
#include <Window.h>

class BMessage;
class BMessenger;
class BButton;
class FontView;


enum font_panel_mode {
	FONT_PANEL,
	MIN_FONT_PANEL, //not yet supported .. just a List of Fontnames + FontSize
	MAX_FONT_PANEL  //with spacing and so on
};

enum font_panel_button {
	B_CANCEL_BUTTON,
	B_DEFAULT_BUTTON
};

enum font_messages{
	M_OK = 'm_ok',
	M_CANCEL,
	M_SIZE_CHANGED,
	M_FAMILY_SELECTED ='mfsl',
	M_STYLE_SELECTED,
	M_HIDE_WINDOW
};


class FontPanel: public BWindow {
	public:
		FontPanel(font_panel_mode mode = FONT_PANEL,
			BMessenger *target = NULL,
			const BFont* font	= NULL,
			const BString *prevString = NULL,
			BMessage *message = NULL,
			bool modal = false,
			bool hide_when_done = true,
			bool update_on_change = true);
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
		status_t		SetFamilyAndStyle(const font_family family,
							const font_style style);
		status_t		SetFamilyAndFace(const font_family family,
							uint16 face);
		void			SetFontSize(uint16 size);
		
		BFont*			Font(void) const;
		uint32			FontMask(void) const;
		
		
		void			SetButtonLabel(font_panel_button button, const char* label);							
		
		void			SetHideWhenDone(bool hideWhenDone);
		bool			HidesWhenDone(void) const;
		void			Refresh();

	
	private:
		FontView		*fFontView;
		BButton			*fOKButton;
		BButton			*fCancelButton;
		BButton			*fDefaultButton;			
		font_panel_mode	fMode;
		bool			fHideWhenDone;
		bool			fUpdateOnChange;
		BMessenger		fTarget;
		BMessage		*fMessage;
};

#endif  /* FONT_PANEL_H */
