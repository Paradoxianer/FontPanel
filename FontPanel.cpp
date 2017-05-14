/*
	FontPanel.cpp: A general-purpose font selection class
	Written by DarkWyrm <darkwyrm@earthlink.net>, Copyright 2007
	Released under the MIT license.
*/

#include "FontPanel.h"

#include "FontView.h"
#include "FontWindow.h"

#include <Spinner.h>
#include <Application.h>
#include <Invoker.h>
#include <String.h>
#include <stdio.h>

// TODO: Add Escape key as a shortcut for cancelling



FontPanel::FontPanel(BMessenger *target,BMessage *msg, float size, bool modal,
					bool hide_when_done)
{
	fWindow = new FontWindow(BRect(200,200,600,500),size);
	fWindow->ReallyQuit();
	if (target)
		fWindow->fView->SetTarget(*target);
	
	if (msg)
		fWindow->fView->SetMessage(msg);
	
	if (modal)
		fWindow->SetFeel(B_MODAL_APP_WINDOW_FEEL);
	
	
	fWindow->fView->SetFontSize(size);
//	fWindow->fView->SetHideWhenDone(hide_when_done);
}


FontPanel::~FontPanel(void)
{
	fWindow->ReallyQuit();
	fWindow->PostMessage(B_QUIT_REQUESTED);
}


void
FontPanel::SelectFont(const BFont &font)
{
	fWindow->fView->SelectFont(&font);
}


void
FontPanel::SelectFont(font_family family, font_style style, float size)
{
	fWindow->fView->SelectFont(family,style,size);
}


void
FontPanel::Show()
{
	fWindow->Show();
}


void
FontPanel::Hide()
{
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
	fWindow->fView->SetTarget(msgr);
}


void
FontPanel::SetMessage(BMessage *msg)
{
	fWindow->fView->SetMessage(msg);
}


void
FontPanel::SetHideWhenDone(bool value)
{
//	fWindow->fView->SetHideWhenDone(value);
}


bool
FontPanel::HideWhenDone(void) const
{
//	return fWindow->fView->HideWhenDone();
}


void
FontPanel::SetFontSize(uint16 size)
{
	fWindow->fView->SetFontSize(size);
}
