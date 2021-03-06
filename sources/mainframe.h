#ifndef __MAINFRAME_H_INCLUDED__
#define __MAINFRAME_H_INCLUDED__

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/dataview.h>

class SettingsManager;
class File2CheckPanel;
class FilterPanel;
class File2CheckModel;
#include "checksums.h"

#define FILESPANEL_COUNT 2
class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title);
		~MainFrame();
	private:
		// Misc functions
		void CreateControls();
		void ConnectControls();
		void UpdateEnabledHashTypes(int mask=0); // For simple text panel
		HashType GetSelectedHashType(); // For simple text panel
		// Events handlers
		void OnSize(wxSizeEvent &event);
		void OnMove(wxMoveEvent &event);
		void OnClose(wxCloseEvent &event);
		void OnPreferencesClicked(wxCommandEvent &event);
		void OnExitClicked(wxCommandEvent &event);
		void OnAboutClicked(wxCommandEvent &event);
		void OnCheckSumsChanged(wxCommandEvent &event);
		void OnFilePanelEvent(wxCommandEvent &event);
		void OnFilterChanged(wxCommandEvent &event);
		// Simple text panel events handlers
		void OnText2HashChanged(wxCommandEvent &event);
		void OnCmbHashTypeChanged(wxCommandEvent &event);
		void OnUpdateUI_BtnCopy(wxUpdateUIEvent &event);
		void OnBtnCopyclicked(wxCommandEvent &event);
		void OnUpdateUI_BtnCopyAll(wxUpdateUIEvent &event);
		void OnBtnCopyAllClicked(wxCommandEvent &event);
		// Controls vars
		wxNotebook *m_nBook;
		File2CheckPanel *m_pnlFile[FILESPANEL_COUNT];
		FilterPanel *m_pnlFilter[2]; // One per tab
		//wxDataViewCtrl *m_dvcFiles;
		wxTextCtrl *m_txtText2Hash, *m_txtResult;
		wxChoice *m_cmbHashType;
		wxBitmapButton *m_btnCopy, *m_btnCopyAll;
		// Misc vars
		SettingsManager& m_settings;
		//wxObjectDataPtr<File2CheckModel> m_f2cModel;
		wxArrayString m_arsResults;
};

#endif // __MAINFRAME_H_INCLUDED__
