#ifndef __FILE2CHECKPANEL_H_INCLUDED__
#define __FILE2CHECKPANEL_H_INCLUDED__

#include <wx/wx.h>

wxDECLARE_EVENT(wxEVT_CHECKSUM_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_FILEPANEL_STARTED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_FILEPANEL_STOPPED, wxCommandEvent);

#include "checksums.h"
class FileHashThread;

class File2CheckPanel : public wxPanel
{
	public:
		File2CheckPanel(wxWindow* parent, const wxString& title);
		virtual ~File2CheckPanel();
		bool HasResult();
		bool IsRunning();
		wxString GetResult(HashType type);
		void UpdateEnabledHashTypes(int mask=0);
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
		void OnUpdateUI_BtnCopy(wxUpdateUIEvent &event);
		void OnBtnCopyclicked(wxCommandEvent &event);
		void OnUpdateUI_BtnCopyAll(wxUpdateUIEvent &event);
		void OnBtnCopyAllClicked(wxCommandEvent &event);
		// Controls vars
		wxBoxSizer *m_szrLine2;
		wxTextCtrl *m_txtFileName, *m_txtResult;
		wxChoice *m_cmbHashType;
		wxGauge *m_pgbProgress;
		wxButton *m_btnBrowse, *m_btnCancel;
		wxBitmapButton *m_btnCopy, *m_btnCopyAll;
		// Misc vars
		FileHashThread *m_thread;
		wxString m_sHash[HT_COUNT];
#ifdef __WXDEBUG__
		wxDateTime m_dtStart;
#endif // __WXDEBUG__
};

#endif // __FILE2CHECKPANEL_H_INCLUDED__
