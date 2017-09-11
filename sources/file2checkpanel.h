#ifndef __FILE2CHECKPANEL_H_INCLUDED__
#define __FILE2CHECKPANEL_H_INCLUDED__

#include <wx/wx.h>

wxDECLARE_EVENT(wxEVT_CHECKSUM_CHANGED, wxCommandEvent);

#include "checksums.h"
class FileHashThread;

class File2CheckPanel : public wxPanel
{
	public:
		File2CheckPanel(wxWindow* parent, const wxString& title);
		virtual ~File2CheckPanel();
		bool HasResult();
		wxString GetResult(HashType type);
		void UpdateEnabledHashTypes();
		HashType GetSelectedHashType();
	private:
		// Misc functions
		void CreateControls(const wxString& title);
		void ConnectControls();
		// Events handlers
		void OnButtonBrowseClicked(wxCommandEvent& event);
		void OnFileDropped(wxCommandEvent &event);
		void OnFilenameChanged(wxCommandEvent& event);
		void OnResultChanged(wxCommandEvent& event);
		void OnBtnCancelClicked(wxCommandEvent &event);
		void OnThreadEvent(wxThreadEvent &event);
		void OnCmbHashTypeChanged(wxCommandEvent &event);
		// Controls vars
		wxBoxSizer *m_szrLine2;
		wxTextCtrl *m_txtFileName, *m_txtResult;
		wxChoice *m_cmbHashType;
		wxGauge *m_pgbProgress;
		wxButton *m_btnBrowse, *m_btnCancel;
		// Misc vars
		FileHashThread *m_thread;
		wxString m_sHash[HT_COUNT];
};

#endif // __FILE2CHECKPANEL_H_INCLUDED__
