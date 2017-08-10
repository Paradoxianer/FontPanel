
#include "FontListView.h"
#include "FontPanel.h"
#include <string.h>



FontListView::FontListView(void)
 : BListView("font_view"),
   fDivider(140.0),
   filterString("")
{
	SetSelectionMessage(new BMessage(M_FONT_SELECTED));
	//first find the normal font then use it to construck the 
	//fonts for the fontitems
}


FontListView::~FontListView(void)
{

}


void
FontListView::AttachedToWindow(void)
{
	RescanForFonts();
}


void
FontListView::SetFontSize(uint16 size)
{
}


void
FontListView::SelectFont(font_family family, font_style style, float size)
{
}


void
FontListView::SelectFont(const BFont &font)
{
}


void
FontListView::MessageReceived(BMessage *msg)
{
	switch (msg->what) {
/*		case '': {
			break;
		}*/
		default: {
			BView::MessageReceived(msg);
			break;
		}
	}
}

void
FontListView::RescanForFonts(void)
{	
	DeleteAll();
	int32 numFamilies = count_font_families();
	for ( int32 i = 0; i < numFamilies; i++ )
	{
		font_family localfamily;
		if ( get_font_family ( i, &localfamily ) == B_OK )
		{
			if (strcasestr(localfamily,filterString) != NULL)
				AddItem(new FontItem(localfamily));
		}
	}
}

void FontListView::SetFilter(char *newFilter)
{
	filterString=newFilter;
	int32		count	= CountItems();
	RescanForFonts();
}

void
FontListView::DeleteAll(void)
{	
	MakeEmpty();
}

FontItem::FontItem(font_family myFamily): BListItem()
{
	memcpy(family,myFamily,B_FONT_FAMILY_LENGTH + 1);
	font	= BFont();
	font.SetFamilyAndFace(family,B_REGULAR_FACE);	
}

void  FontItem::DrawItem(BView *owner, BRect frame, bool complete)
{
	FontListView *fView = static_cast<FontListView *>(owner);
	font_height			m_fontHeight;
	rgb_color			color;
	fView->SetDrawingMode(B_OP_OVER);
	
	if (IsSelected())
		color = ui_color(B_LIST_SELECTED_BACKGROUND_COLOR);
	else
		color = ui_color(B_LIST_BACKGROUND_COLOR);
	
	fView->SetHighColor(color);
	fView->FillRect(frame);
	if (IsSelected()) 
		color = ui_color(B_LIST_SELECTED_ITEM_TEXT_COLOR);
	else
		color = ui_color(B_LIST_ITEM_TEXT_COLOR);
	
	fView->GetFontHeight(&m_fontHeight);
	fView->SetHighColor(color);
	fView->MovePenTo(frame.left+kMarginLeftRight, frame.top+kMarginTopBottom+m_fontHeight.ascent+m_fontHeight.leading);
   	fView->DrawString(family);
	//save the BView font
	
	BFont tmpFont;
	owner->GetFont(&tmpFont);
	owner->SetFont(&font);
	fView->GetFontHeight(&m_fontHeight);
	fView->MovePenTo(frame.left+kMarginLeftRight+fView->DividerPosition(), frame.top+kMarginTopBottom+m_fontHeight.ascent+m_fontHeight.leading);
	//draw the PreviewString
	owner->DrawString(PREVIEW_STR);
	//and restore the default BView Font
	owner->SetFont(&tmpFont);
}



void
FontItem::Update( BView *owner, const BFont *fFont)
{
	BListItem::Update(owner, fFont);
	FontListView *fView = static_cast<FontListView *>(owner);
	if ((fFont->StringWidth(family)+2*kMarginLeftRight)>fView->DividerPosition())
		fView->SetDividerPosition(fFont->StringWidth(family)+2*kMarginLeftRight);
	SetWidth(font.StringWidth(PREVIEW_STR) + fView->DividerPosition()+(2*kMarginLeftRight));
	font_height			m_fontHeight;
	font.GetHeight(&m_fontHeight);
	float newHeight = m_fontHeight.ascent + m_fontHeight.descent + m_fontHeight.leading + kMarginTopBottom;
	fFont->GetHeight(&m_fontHeight);
	float newHeight2 = m_fontHeight.ascent + m_fontHeight.descent + m_fontHeight.leading+ kMarginTopBottom;
	if (newHeight > newHeight2)
		SetHeight(newHeight);
	else
		SetHeight(newHeight2);
}