/**********************************************************

	Project: ralf_tracker
	-------- ------------

	Version : 0.3.1a (alpha)
	6 july 1996 for BeOS DR 7.1 (and DR 7)

	Sample wrapper around the Marc Espie's "tracker 3.19".
	Please feel free to reuse that code, as either a sample code
	for programing onto the BeBox or to add a more robust
	interface with nice features.
	
	Once I get another version of "tracker" from Marc Espie which
	uses something else that K&R formating, I will suppress the tracker_lib.so.
	This library is here because I can't mix C K&R code and C++ code in the
	same project with CodeWarior.

	There is no copyright on this code. You can modify it, destroy it,
	reuse it or simply trash it. If you reuse it, please mention my
	name somewhere. If you did something beautifull, please send me
	a copy. I'd like to see "be-demos" like there was "amiga-demos".

	Raphael MOLL,
	moll@linux.utc.fr

	Disclaimer : there is no link between this code and my work
	at MIPSYS, France.
	
	Bug fixes by Hubert Figuiere (june 1996)
	figuiere@kagi.com

***********************************************************/



#include "CFileList.h"

#include "RalfTypes.h"

//*************************************
CFileList::CFileList(BRect frame, char *name,
						ULONG resizeMode,
						ULONG flags)
					:BListView(frame,name,resizeMode,flags)
//*************************************
{
}

//*************************************
CFileList::~CFileList()
//*************************************
{
}


//*************************************
bool CFileList::MessageDropped(BMessage *msg, BPoint point, BPoint offset)
//*************************************
{
	if (msg->HasRef("refs"))
	{
		HiliteDragRegion(FALSE);
		InvalidateItem(CurrentSelection());
		msg->what = B_REFS_RECEIVED;
		be_app->RefsReceived(msg);
		return FALSE;
	}
	return TRUE;
}

//*************************************
void CFileList::MouseMoved(BPoint pt, ulong transit, BMessage * msg)
//*************************************
{
	if ((transit == B_ENTERED_VIEW) && (msg != NULL))
	{
		if (msg->HasRef("refs"))
		{
			HiliteDragRegion(TRUE);
			return;
		}/*if*/
	}/*if*/
	if ((transit == B_EXITED_VIEW) && (msg != NULL))
	{
		if (msg->HasRef("refs"))
		{
			HiliteDragRegion(FALSE);
			return;
		}/*if*/	
	}/*if*/
}


//*************************************
void CFileList::HiliteDragRegion(bool hilite)
//*************************************
// hilite the view if it can receive the datas
// true -> hilite
// false -> unhilite
{
	float oldPenSize;
	drawing_mode oldMode;
	
	oldMode = DrawingMode();
	SetDrawingMode(B_OP_INVERT);

	oldPenSize = PenSize();
	SetPenSize(2.0);
	
	if (hilite) {
		StrokeRect(Bounds(), B_SOLID_HIGH);
	} else {
		StrokeRect(Bounds(), B_SOLID_HIGH);
	}/*else*/
	SetDrawingMode(oldMode);
}
