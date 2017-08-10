#include <ScrollView.h>
#include <ScrollBar.h>
#include <StringView.h>
#include <CheckBox.h>
#include <Spinner.h>
#include <DecimalSpinner.h>
#include <PopUpMenu.h>
#include <GroupLayout.h>
#include <GroupLayoutBuilder.h>
#include <GridLayout.h>
#include <GridLayoutBuilder.h>
#include <Button.h>

#include "FontWindow.h"
#include "FontPanel.h"




FontWindow::FontWindow(const BRect frame, float fontsize)
 :	BWindow(frame,B_TRANSLATE("Choose a Font"), B_TITLED_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,0)
{	
	RemoveShortcut('w',B_COMMAND_KEY);
	AddShortcut('w',B_COMMAND_KEY,new BMessage(M_HIDE_WINDOW));
	//check if this is enought
	SetSizeLimits(400,2400,300,2400);
	fView = new FontView();
	fView->SetSelectionMessage(new BMessage(M_FONT_SELECTED));
	fView->SetTarget(this);
	SetLayout(new BGroupLayout(B_VERTICAL));
	AddChild(BGroupLayoutBuilder(B_VERTICAL)
 		.Add(fView)
		.Add(BGroupLayoutBuilder(B_HORIZONTAL)
			.AddGlue()
			.Add(new BButton("cancel",B_TRANSLATE("Cancel"),new BMessage(M_CANCEL)))
			.Add(new BButton("ok",B_TRANSLATE("OK"),new BMessage(M_OK)))
		)
 	);
}


FontWindow::~FontWindow(void)
{
	
}


bool
FontWindow::QuitRequested(void)
{
	if (fClientObject != NULL) {
		Hide();
		if (fClientObject != NULL)
			fClientObject->WasHidden();

		BMessage message(*fMessage);
		message.what = B_CANCEL;
		message.AddInt32("old_what", (int32)fMessage->what);
		message.AddPointer("source", fClientObject);
		fTarget.SendMessage(&message);

		return false;
	}

	return _inherited::QuitRequested();
	return fReallyQuit;
}


void FontWindow::SetClientObject(FontPanel *panel)
{
	fClientObject = panel;
}

 
void
FontWindow::MessageReceived(BMessage *msg)
{
	msg->PrintToStream();
		switch (msg->what) {
		case M_HIDE_WINDOW: {
			Hide();
			break;
		}
		case M_FONT_SELECTED: {
			int32 sel = fView->CurrentSelection();
			if (sel > 0) {
				FontItem *fItem = dynamic_cast<FontItem*>(fView->ItemAt(sel));
				if (fItem !=NULL)
				{
					BFont font;
					fPrevView->GetFont(&font);
					uint16 face=font.Face();
					font.SetFamilyAndFace(fItem->GetFamily(),face);
					fPrevView->SetFont(&font);
					fPrevView->Draw(Bounds());
				}
			}
		}
		default: {
			BWindow::MessageReceived(msg);
			break;
		}
	}
}


