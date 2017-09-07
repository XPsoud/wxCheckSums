#ifndef __FILEDROPTARGETS_H_INCLUDED__
#define __FILEDROPTARGETS_H_INCLUDED__

#include <wx/wx.h>
#include <wx/dnd.h>

wxDECLARE_EVENT(wxEVT_FILES_DROPPED, wxCommandEvent);

class SingleFileDropTarget : public wxFileDropTarget
{
	public:
		SingleFileDropTarget(wxWindow *dstHandler);
		virtual ~SingleFileDropTarget();
		virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &filenames);
	private:
		wxWindow *m_wndTarget;
};

class MultiFilesDropTarget : public wxFileDropTarget
{
	public:
		MultiFilesDropTarget(wxWindow *dstHandler);
		virtual ~MultiFilesDropTarget();
		virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &filenames);
	private:
		wxWindow *m_wndTarget;
};

#endif // __FILEDROPTARGETS_H_INCLUDED__
