/*
	FontPanel.cpp: A general-purpose font selection class
	Written by DarkWyrm <darkwyrm@earthlink.net>, Copyright 2007
	Released under the MIT license.
	Edit by Paradoxon 2018
*/

#include "FontPanel.h"

#include "FontView.h"

#include <Application.h>
#include <Button.h>
#include <Catalog.h>
#include <GroupLayout.h>
#include <GroupLayoutBuilder.h>
#include <GridLayout.h>
#include <GridLayoutBuilder.h>
#include <Invoker.h>
#include <Message.h>
#include <Messenger.h>
#include <String.h>
#include <StringView.h>
#include <Screen.h>
#include <Window.h>
#include <stdio.h>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "FontPanel"


FontPanel::FontPanel(font_panel_mode mode,
			const BFont *font,
			const BString *prevString,
			BMessenger *target,
			BMessage *message,
			bool modal,
			bool hide_when_done,
			bool update_on_change):
			BWindow(BRect(100,100,400,200),"FontPanel",
				B_DOCUMENT_WINDOW_LOOK, modal ? B_MODAL_APP_WINDOW_FEEL : B_NORMAL_WINDOW_FEEL,
				B_WILL_ACCEPT_FIRST_CLICK | B_NO_WORKSPACE_ACTIVATION,
				B_CURRENT_WORKSPACE)
{
	defaultFont=*font;
	fHidesWhenDone = hide_when_done;
	fUpdateOnChange=update_on_change;
	if (target)
		fTarget = *target;
	else
		fTarget = BMessenger(be_app);

	if (message)
		SetMessage(message);
	else
	fFontView = new FontView(mode,font, prevString, &fTarget, message, true);
	fOKButton = new BButton("ok",B_TRANSLATE("OK"),new BMessage(M_OK));
	fCancelButton = new BButton("cancel",B_TRANSLATE("Cancel"),new BMessage(M_CANCEL));
	fDefaultButton = new BButton("default",B_TRANSLATE("Default"),new BMessage(M_CANCEL));
	fStatus = new BStringView("statusbar",B_TRANSLATE("Type to filter"));

	RemoveShortcut('w',B_COMMAND_KEY);
	AddShortcut('w',B_COMMAND_KEY,new BMessage(M_HIDE_WINDOW));
	//check if this is enought
	SetSizeLimits(300,2400,300,2400);
	SetLayout(new BGroupLayout(B_VERTICAL));
	AddChild(BGroupLayoutBuilder(B_VERTICAL)
 		.Add(fFontView)
		.Add(BGroupLayoutBuilder(B_HORIZONTAL)
			.AddGlue()
			.Add(fOKButton)
			.Add(fCancelButton)
			.Add(fDefaultButton)
		)
		.Add(fStatus,0.2)
 	);
 	fFontView->MakeFocus();
}


FontPanel::~FontPanel(void)
{
}


void FontPanel::SetFont(const BFont &font)
{
}

BFont* FontPanel::Font(void) const
{
	return fFontView->Font();
}

status_t FontPanel::SetFamilyAndStyle(const font_family family,
							const font_style style)
{
}

status_t FontPanel::SetFamilyAndFace(const font_family family,
							uint16 face)
{
}


void FontPanel::SetFontSize(uint16 size)
{
}


void
FontPanel::Show()
{
	// if the window is already showing, don't jerk the workspaces around,
	// just pull it to us
	uint32 workspace = 1UL << (uint32)current_workspace();
	uint32 windowWorkspaces = Workspaces();
	if (!(windowWorkspaces & workspace)) {
		// window in a different workspace, reopen in current
		SetWorkspaces(workspace);
	}

	// Position the file panel like an alert
	BWindow* parent = dynamic_cast<BWindow*>(
		BLooper::LooperForThread(find_thread(NULL)));
	const BRect frame = parent != NULL ? parent->Frame()
		: BScreen(this).Frame();
	
	//MoveTo(AlertPosition(frame));
	if (!IsShowing())
		BWindow::Show();
	Activate();
	ResizeToPreferred();
}


void
FontPanel::Hide()
{
	BWindow::Hide();
}


bool
FontPanel::IsShowing(void) const
{
	return !IsHidden();
}


BWindow *
FontPanel::Window(void)
{
	return this;
}


void
FontPanel::SetTarget(BMessenger target)
{
	fTarget = target;
}


void
FontPanel::SetMessage(BMessage *message)
{
	delete fMessage;
	fMessage = new BMessage(*message);
}


void
FontPanel::SetHideWhenDone(bool value)
{
	//SetHideWhenDone(value);
}


bool
FontPanel::HidesWhenDone(void) const
{
	return fHidesWhenDone;
}


void FontPanel::MessageReceived(BMessage* message)
{
	switch (message->what) {
		
		case M_OK:
			{
				BFont *returnFont = fFontView->Font();
				BMessage *messageToSend= new BMessage(message);
				messageToSend->AddMessage("font",MessageForFont(returnFont);
				fTarget->SendMessage(messageToSend );
				returnFont->PrintToStream();
				Quit();
			}
			break;
		case M_CANCEL:{
				fFontView->SetFont(defaultFont);
				Quit();
			}
			break;
		default:  {
			BWindow::MessageReceived(message);
			break;
		}
	}
}

BMessage *MessageForFont(BFont *font){
	BMessage *returnMessage = new Message(B_FONT_TYPE);
	if (font != NULL){
		returnMessage->AddInt16("Font::Face",font->Face());
		returnMessage->AddString("Font::Family", font->font_family);
		returnMessage->AddInt32("Font::Flags", font->Flags());
		returnMessage->AddFloat("Font::Rotation", font->Rotation());
		returnMessage->AddFloat("Font::Shear", font->Shear());
		returnMessage->AddFloat("Font::Size", font->Size());	
		returnMessage->AddInt8("Font::Spacing", font->Spacing());
		returnMessage->AddString("Font::Style" , font->font_style); 
	}
}



