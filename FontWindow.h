#ifndef FONT_WINDOW_H_
#define FONT_WINDOW_H_

#include <Window.h>

#include "FontView.h"

class FontPanel;

class FontWindow : public BWindow
{
public:
					FontWindow(const BRect frame, float fontsize);
					~FontWindow(void);
	void			SetClientObject(FontPanel *client);
	bool			QuitRequested(void);
	void			MessageReceived(BMessage *msg);
	
	
	

private:
		FontView		*fFontView;
		BButton			*fOKButton;
		BButton			*fCancelButton;
		BButton			*fDefaultButton;	
		
		FontPanel		*fClientObject;

};

#endif
