/*
 * Copyright 2017, Paradoxon. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */

#ifndef FONT_PANEL_H
#define FONT_PANEL_H

#include <Font.h>
#include <String.h>
#include <Window.h>
#include <Messenger.h>


class BMessage;
class BButton;
class BStringView;
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

enum font_panel_messages {
	M_OK			= 'm_ok',
	M_CANCEL		= 'm_cl',
	M_HIDE_WINDOW	= 'm_hw',
	M_FONT_SELECTED	= 'm_fs'
};

enum font_messages{
	M_SIZE_CHANGED				= 'm_sz',
	M_FAMILY_CHANGED			= 'm_fm',
	M_BOLD_CHANGED				= 'm_bd',
	M_ITALIC_CHANGED			= 'm_it',
	M_STRIKE_OUT_CHANGED		= 'm_so',
	M_UNDERLINE_CHANGED 		= 'm_ul',
	M_FORE_GROUND_COLOR_CHANGED	= 'm_fc',
	M_FILL_COLOR_CHANGED		= 'm_ic',
	M_BACK_GROUND_COLOR_CHANGED	= 'm_bc',
	M_OUTLINE_CHANGED			= 'm_ol',
	M_SHEAR_CHANGED				= 'm_sh',
	M_SPACING_CHANGED			= 'm_sp',
	M_ROTATION_CHANGED			= 'm_rt',

};

#define	PREVIEW_STR "AaBbCcDdEeFfGg!?1234567890"


class FontPanel: public BWindow {
	public:
		FontPanel(font_panel_mode mode = FONT_PANEL,
			const BFont* font	= NULL,
			const BString *prevString = new BString(PREVIEW_STR),
			BMessenger *target = NULL,
			BMessage *message = NULL,
			bool modal = false,
			bool hide_when_done = true,
			bool update_on_change = true);
		virtual			~FontPanel(void);
	
		void			Show();
		void			Hide();
		bool			IsShowing(void) const;
	
		virtual void	WasHidden(){};
		virtual void	SelectionChanged(){};
		virtual void	SendMessage(const BMessenger* target, BMessage* message){};
	
		BWindow*		Window();
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

		void			MessageReceived(BMessage* message);
	
	private:
		FontView		*fFontView;
		BButton			*fOKButton;
		BButton			*fCancelButton;
		BButton			*fDefaultButton;			
		bool			fHidesWhenDone;
		bool			fUpdateOnChange;
		BStringView		*fStatus;
		BMessage		*fMessage;
		BMessenger		fTarget;
		BFont			defaultFont;
		
};

#endif  /* FONT_PANEL_H */
