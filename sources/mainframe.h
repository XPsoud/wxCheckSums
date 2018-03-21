#ifndef __MAINFRAME_H_INCLUDED__
#define __MAINFRAME_H_INCLUDED__

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/dataview.h>

class SettingsManager;
class File2CheckPanel;
class FilterPanel;
class File2CheckModel;

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
		void OnFilesDropped(wxCommandEvent &event);
		// Controls vars
		wxNotebook *m_nBook;
		File2CheckPanel *m_pnlFile[FILESPANEL_COUNT];
		FilterPanel *m_pnlFilter[3]; // One per tab
		wxDataViewCtrl *m_dvcFiles;
		// Misc vars
		SettingsManager& m_settings;
		wxObjectDataPtr<File2CheckModel> m_f2cModel;
};

#endif // __MAINFRAME_H_INCLUDED__
