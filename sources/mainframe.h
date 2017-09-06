#ifndef __MAINFRAME_H_INCLUDED__
#define __MAINFRAME_H_INCLUDED__

#include <wx/wx.h>

class SettingsManager;

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
		// Misc vars
		SettingsManager& m_settings;
};

#endif // __MAINFRAME_H_INCLUDED__
