#ifndef FONT_VIEW_H_
#define FONT_VIEW_H_

#include <Font.h>
#include <InterfaceDefs.h>
#include <ListView.h>
#include <ListItem.h>
#include <String.h>

const float kMarginLeftRight = 5.0;
const float kMarginTopBottom = 5.0;


class FontListView : public BListView
{
public:
				FontListView(void);
				~FontListView(void);
	
	void		AttachedToWindow(void);
	void		MessageReceived(BMessage *message);
	
	void		KeyDown(const char* bytes, int32 numBytes);

					
	void		SetUnderline(bool underline);
	void		SetStrikeout(bool strkeout);
	void		SetItalic(bool italic);
	void		SetOutlined(int32 outline);

	void		SelectFont(const BFont &font);
	void		SelectFont(font_family family);

	void		SetFilter(char *newFilter);
	void		ResetFilter(void);
	void		SetDividerPosition(float pos){fDivider = pos;}
	float		DividerPosition(void){return fDivider;}
	
	BString*	PreviewString(void){return &fPrevString;};
	void		SetPreviewString(char *prevString){fPrevString.SetTo(prevString);};
	void		SetPreviewString(BString prevString){fPrevString.SetTo(prevString);};
	
	int32		IndexOf(BFont *font) const;
	int32		IndexOf(font_family family) const;
	
private:	
	void		RescanForFonts(void);
	void		DeleteAll(void);
	
	float		fDivider;
	BString		filterString;
	BString		fPrevString;
	

	
};

class FontItem : public BListItem
{
public:
							FontItem(font_family myFamily);
	
	virtual void			DrawItem(BView *owner,
							BRect frame,
							bool complete = false);
            char*			GetFamily(void){return family;};
            void			SetSize(float size){font.SetSize(size);};
			void			SetShear(float shear){font.SetShear(shear);};
			void			SetRotation(float rotation){font.SetRotation(rotation);};
			void			SetFalseBoldWidth(float width){font.SetFalseBoldWidth(width);};
			void			SetSpacing(uint8 spacing){font.SetSpacing(spacing);};
			void			SetEncoding(uint8 encoding){font.SetEncoding(encoding);};
			void			SetFace(uint16 face){font.SetFace(face);};
			void			SetFlags(uint32 flags){font.SetFlags(flags);};
			void			Update( BView *owner, const BFont *fFont);
			

private:
		font_family	family;
		BFont		font;		
};


#endif
