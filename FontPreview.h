#ifndef FONT_PREVIEW_H_
#define FONT_PREVIEW_H_

#include <View.h>
#include <Font.h>
#include <InterfaceDefs.h>
#include <String.h>

#define	PREVIEW_STR "AaBbCcDdEeFfGg!?1234567890"

class FontPreview : public BView
{
public:
					FontPreview();
	
	void			SetPreviewText(const char *text);
	const char *	PreviewText(void) const;
			
	void			Draw(BRect r);
	
private:
	BString	fPreviewText;
};

#endif
