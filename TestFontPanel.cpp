#include <Application.h>
#include "FontPanel.h"



int main() {
	new BApplication("application/x-vnd.TestFontPanel");
   /* Further initialization goes here -- read settings,
      set globals, etc. */
   FontPanel fPanel = FontPanel();
	fPanel.Show();
   be_app->Run();
   /* Clean up -- write settings, etc. */
	delete be_app;
	return 0;
}
