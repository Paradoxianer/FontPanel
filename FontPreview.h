#ifndef FONT_PREVIEW_H_
#define FONT_PREVIEW_H_


#include <Font.h>
#include <InterfaceDefs.h>
#include <Shape.h>
#include <String.h>
#include <View.h>

class FontPreview : public BView
{
public:
					FontPreview();
	
	void			SetPreviewText(const char *text);
	const char *	PreviewText(void) const;
			 
	void			Draw(BRect r);
	
	//overwrite SetFont and set the new SetExplicitMaxSize
	void			SetFont(const BFont* font,
							uint32 mask = B_FONT_ALL);
	
private:
	void			_AddShapes(BString string);
	void			_RecalcSize(void);
	BString			fPreviewText;
	BShape**		fShapes;
};

#endif
