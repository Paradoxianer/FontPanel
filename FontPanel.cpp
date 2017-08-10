/*
	FontPanel.cpp: A general-purpose font selection class
	Written by DarkWyrm <darkwyrm@earthlink.net>, Copyright 2007
	Released under the MIT license.
*/

#include "FontPanel.h"

#include "FontView.h"

#include <Application.h>
#include <Invoker.h>
#include <Message.h>
#include <Messenger.h>
#include <String.h>
#include <Screen.h>
#include <Window.h>
#include <stdio.h>



FontPanel::FontPanel(font_panel_mode mode,
			BMessenger *target,
			const BFont *font,
			const BString *prevString ,
			BMessage *message,
			bool modal,
			bool hide_when_done,
			bool update_on_change):
			BWindow(BRect(100,100,400,200),"FontPanel",
				B_DOCUMENT_WINDOW_LOOK, modal ? B_MODAL_APP_WINDOW_FEEL : B_NORMAL_WINDOW_FEEL,
				B_WILL_ACCEPT_FIRST_CLICK | B_NO_WORKSPACE_ACTIVATION,
				B_CURRENT_WORKSPACE)
{
	fMode = mode;
	fHideWhenDone = hide_when_done;
	fUpdateOnChange=update_on_change;
	if (target)
		fTarget = *target;
	else
		fTarget = BMessenger(be_app);

	if (message)
		SetMessage(message);
	else
		fMessage = new BMessage(B_REFS_RECEIVED);


}


FontPanel::~FontPanel(void)
{
}


void FontPanel::SetFont(const BFont &font)
{
	//lock Window??
	//fWindow->SetFont();
}

status_t FontPanel::SetFamilyAndStyle(const font_family family,
							const font_style style)
{
}
status_t FontPanel::SetFamilyAndFace(const font_family family,
							uint16 face)
{
}


void FontPanel::SetSize(uint16 size)
{
}


void
FontPanel::Show()
{
	// if the window is already showing, don't jerk the workspaces around,
	// just pull it to us
	uint32 workspace = 1UL << (uint32)current_workspace();
	uint32 windowWorkspaces = fWindow->Workspaces();
	if (!(windowWorkspaces & workspace)) {
		// window in a different workspace, reopen in current
		fWindow->SetWorkspaces(workspace);
	}

	// Position the file panel like an alert
	BWindow* parent = dynamic_cast<BWindow*>(
		BLooper::LooperForThread(find_thread(NULL)));
	const BRect frame = parent != NULL ? parent->Frame()
		: BScreen(fWindow).Frame();

	fWindow->MoveTo(fWindow->AlertPosition(frame));
	if (!IsShowing())
		fWindow->Show();

	fWindow->Activate();
}


void
FontPanel::Hide()
{
	if (!fWindow->IsHidden())
		fWindow->QuitRequested();
	fWindow->Hide();
}


bool
FontPanel::IsShowing(void) const
{
	return !fWindow->IsHidden();
}


BWindow *
FontPanel::Window(void) const
{
	return fWindow;
}


void
FontPanel::SetTarget(BMessenger msgr)
{
	fTarget = target;
}


void
FontPanel::SetMessage(BMessage *msg)
{
	delete fMessage;
	fMessage = new BMessage(*message);
}


void
FontPanel::SetHideWhenDone(bool value)
{
//	fWindow->SetHideWhenDone(value);
}


bool
FontPanel::HidesWhenDone(void) const
{
//	return fWindow->HideWhenDone();
}


void
FontPanel::SetFontSize(uint16 size)
{
	//fWindow->fView->SetFontSize(size);
}
