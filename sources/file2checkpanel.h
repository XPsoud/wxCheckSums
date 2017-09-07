#ifndef __FILE2CHECKPANEL_H_INCLUDED__
#define __FILE2CHECKPANEL_H_INCLUDED__

#include <wx/wx.h>

wxDECLARE_EVENT(wxEVT_CHECKSUM_CHANGED, wxCommandEvent);

class File2CheckPanel : public wxPanel
{
	public:
		File2CheckPanel(wxWindow* parent, const wxString& title);
		virtual ~File2CheckPanel();
	private:
		// Misc functions
		void CreateControls(const wxString& title);
		void ConnectControls();
		// Events handlers
		void OnButtonBrowseClicked(wxCommandEvent& event);
		void OnFilenameChanged(wxCommandEvent& event);
		void OnResultChanged(wxCommandEvent& event);
		// Controls vars
		wxTextCtrl *m_txtFileName, *m_txtResult;
		wxButton *m_btnBrowse;
};

#endif // __FILE2CHECKPANEL_H_INCLUDED__
