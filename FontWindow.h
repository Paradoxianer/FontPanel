#ifndef FONT_WINDOW_H_
#define FONT_WINDOW_H_

#include <Window.h>
#include <PopUpMenu.h>

#include "FontView.h"
#include "FontPreview.h"



class FontWindow : public BWindow
{
public:
					FontWindow(const BRect frame, float fontsize);
					~FontWindow(void);
	bool			QuitRequested(void);
	void			MessageReceived(BMessage *msg);
	
	void			ReallyQuit(void) { fReallyQuit = true; }
	
	FontView		*fView;

private:
	bool			fReallyQuit;
	FontPreview		*fPrevView;
	
	/*BCheckBox		fBold;
	BCheckBox		fItalic;
	
	BCheckBox		fStrikeOut;*/
	
	BPopUpMenu		*fForeGroundColor;
	BPopUpMenu		*fBackGroundColor;
	
	/*BSpinner		fSize;
	BDecimalSpinner	fOutline;*/
	
	
	
	//shear
	//rotation
	//spacing
	
	//ForeGroundColor
	//BackGroundColor
	
	
	//Italic
	//Bold
	
	//Outlined
	
	//Strike Out
	//Underline
	
};

#endif
