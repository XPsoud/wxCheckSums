#ifndef __MAINFRAME_H_INCLUDED__
#define __MAINFRAME_H_INCLUDED__

#include <wx/wx.h>
#include <wx/notebook.h>

class SettingsManager;
class File2CheckPanel;

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
		// Controls vars
		wxNotebook *m_nBook;
		File2CheckPanel *m_pnlFile[FILESPANEL_COUNT];
		// Misc vars
		SettingsManager& m_settings;
};

#endif // __MAINFRAME_H_INCLUDED__
