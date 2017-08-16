#include <Application.h>
#include <Font.h>
#include <String.h>
#include "FontPanel.h"



int main() {
	new BApplication("application/x-vnd.TestFontPanel");
   /* Further initialization goes here -- read settings,
      set globals, etc. */
   FontPanel *fPanel = new FontPanel(FONT_PANEL,be_plain_font, new BString("Timon"),NULL,
		NULL, false, true, true);
	fPanel->SetHideWhenDone(false);
	fPanel->Show();
   be_app->Run();
   /* Clean up -- write settings, etc. */
	delete be_app;
	return 0;
}
