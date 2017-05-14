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
	SetSizeLimits(400,2400,300,2400);
	fReallyQuit = false;
	fView = new FontView();
	fView->SetSelectionMessage(new BMessage(M_FONT_SELECTED));
	fView->SetTarget(this);
	fPrevView = new FontPreview();
	SetLayout(new BGroupLayout(B_VERTICAL));

 	AddChild(BGroupLayoutBuilder(B_VERTICAL)
 		.Add(new BScrollView("fontScroller",fView, 0,false, true))
 		.Add(BGridLayoutBuilder()
 			.Add(new BCheckBox(B_TRANSLATE("Bold")),0,0)
 			.Add(new BCheckBox(B_TRANSLATE("Italic")),0,1)
 			.Add(new BCheckBox(B_TRANSLATE("Strike Out")),1,0)
 		)
		.Add(fPrevView)
		.Add(BGroupLayoutBuilder(B_HORIZONTAL)
			.AddGlue()
			.Add(new BButton("cancel",B_TRANSLATE("Cancel"),new BMessage(M_CANCEL)))
			.Add(new BButton("ok",B_TRANSLATE("OK"),new BMessage(M_OK)))
		)
 	);
}


FontWindow::~FontWindow(void)
{
	ReallyQuit();
	PostMessage(B_QUIT_REQUESTED);
}


bool
FontWindow::QuitRequested(void)
{
	if (!fReallyQuit)
		PostMessage(M_HIDE_WINDOW);
	return fReallyQuit;
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

/*Update StyleList
			const int32 styles = count_font_styles(fontFamilyName);

			BMessage* familyMsg = new BMessage(FONTFAMILY_CHANGED_MSG);
			familyMsg->AddString("_family", fontFamilyName);
			BMenuItem* familyItem = new BMenuItem(stylemenu, familyMsg);
			fFontFamilyMenu->AddItem(familyItem);

			for (int32 j = 0; j < styles; j++) {
				if (get_font_style(fontFamilyName, j, &fontStyleName) == B_OK) {
					BMessage* fontMsg = new BMessage(FONTSTYLE_CHANGED_MSG);
					fontMsg->AddString("_family", fontFamilyName);
					fontMsg->AddString("_style", fontStyleName);

					BMenuItem* styleItem = new BMenuItem(fontStyleName, fontMsg);
					styleItem->SetMarked(false);

					// setInitialfont is used when we attach the FontField
					if (!strcmp(fontStyleName, currentStyle)
						&& !strcmp(fontFamilyName, currentFamily)
						&& setInitialfont) {
						styleItem->SetMarked(true);
						familyItem->SetMarked(true);

						BString string;
						string << currentFamily << " " << currentStyle;

						if (fFontMenuField)
							fFontMenuField->MenuItem()->SetLabel(string.String());
					}
					stylemenu->AddItem(styleItem);
				}
			}

			stylemenu->SetRadioMode(true);
			stylemenu->SetTargetForItems(this);
*/
