#include "mainframe.h"

#include "main.h"
#include "dlgabout.h"
#include "appversion.h"
#include "dlgoptions.h"
#include "settingsmanager.h"

#include <wx/display.h>
#include <wx/filedlg.h>
#include <wx/artprov.h>
#include <wx/xml/xml.h>
#include <wx/wfstream.h>

#ifndef __WXMSW__
#include "../graphx/wxwin32x32.xpm"
#endif // __WXMSW__


MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, -1, title),
	m_settings(SettingsManager::Get())
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"MainFrame\" object\n"));
#endif // DEBUG

	SetIcon(wxICON(appIcon)); // Defining app icon

	CreateControls();

	int iStartPos=m_settings.GetMainWndStartupPos();
	if (iStartPos==wxALIGN_NOT)
	{
		wxPoint pt;
		m_settings.GetMainWndStartupPos(pt);
		wxSize sz=m_settings.GetMainWndStartupSize();

		if (sz==wxDefaultSize)
		{
			if (pt==wxDefaultPosition)
				Maximize(true);
			else
				CenterOnScreen();
		}
		else
		{
			Move(pt);
			SetSize(sz);
		}
	}
	else
	{

		wxDisplay d;
		wxRect rcD=d.GetClientArea();
		int iWScr=rcD.GetWidth();
		int iHScr=rcD.GetHeight();
		wxSize sz=GetSize();
		wxPoint pt=wxDefaultPosition;
		pt.x=(((iStartPos&wxLEFT)==wxLEFT)?0:((iStartPos&wxRIGHT)==wxRIGHT)?iWScr-sz.GetWidth():(iWScr-sz.GetWidth())/2);
		pt.y=(((iStartPos&wxTOP)==wxTOP)?0:((iStartPos&wxBOTTOM)==wxBOTTOM)?iHScr-sz.GetHeight():(iHScr-sz.GetHeight())/2);
		Move(pt);
	}

	ConnectControls();
}

MainFrame::~MainFrame()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"MainFrame\" object\n"));
#endif // DEBUG
}

void MainFrame::CreateControls()
{
	// Status bar
	CreateStatusBar(2);
	wxString sTxt=wxGetApp().GetBuildInfos();
	SetStatusText(sTxt, 1);

	// Menu bar of the main window
	wxMenuBar *menuBar = new wxMenuBar();

	// File menu
	wxMenu *fileMenu = new wxMenu();

		fileMenu->Append(wxID_PREFERENCES, wxGetStockLabel(wxID_PREFERENCES, wxSTOCK_WITH_MNEMONIC|wxSTOCK_WITH_ACCELERATOR), _("Edit application settings"));

		fileMenu->AppendSeparator();

		fileMenu->Append(wxID_EXIT, wxGetStockLabel(wxID_EXIT, wxSTOCK_WITH_MNEMONIC|wxSTOCK_WITH_ACCELERATOR), wxGetStockHelpString(wxID_EXIT));

	menuBar->Append(fileMenu, wxGetStockLabel(wxID_FILE));

	wxMenu* helpMenu = new wxMenu();

		helpMenu->Append(wxID_ABOUT, wxGetStockLabel(wxID_ABOUT, wxSTOCK_WITH_MNEMONIC|wxSTOCK_WITH_ACCELERATOR), wxGetStockHelpString(wxID_ABOUT));

		menuBar->Append(helpMenu, wxGetStockLabel(wxID_HELP));

	SetMenuBar(menuBar);

	// Controls
	wxPanel *pnl=new wxPanel(this, -1);
}

void MainFrame::ConnectControls()
{
	// General events handlers
	Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
	Bind(wxEVT_MOVE, &MainFrame::OnMove, this);
	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

	// Menus events handlers
	Bind(wxEVT_MENU, &MainFrame::OnPreferencesClicked, this, wxID_PREFERENCES);
	Bind(wxEVT_MENU, &MainFrame::OnExitClicked, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnAboutClicked, this, wxID_ABOUT);
}


void MainFrame::OnSize(wxSizeEvent& event)
{
	if (!IsShown()) return;
	if (IsMaximized())
	{
		m_settings.SetLastWindowRect(wxDefaultPosition, wxDefaultSize);
	}
	else
	{
		m_settings.SetLastWindowRect(GetPosition(), GetSize());
	}
	event.Skip();
}

void MainFrame::OnMove(wxMoveEvent& event)
{
	if (!IsShown()) return;
	m_settings.SetLastWindowRect(GetPosition(), GetSize());
	event.Skip();
}

void MainFrame::OnClose(wxCloseEvent& event)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Closing the \"MainFrame\" object\n"));
#endif // DEBUG
	Destroy();
}

void MainFrame::OnPreferencesClicked(wxCommandEvent& event)
{
	// Save the "KeepLang" state
	bool bOldLng=m_settings.GetProhibitI18N();
	DlgOptions dlg(this);
	dlg.ShowModal();
	if (m_settings.GetProhibitI18N()!=bOldLng)
	{
		wxMessageBox(_("You changed the translation settings.\nYou must restart the application to see this in effect."), _("Restart needed"), wxICON_INFORMATION|wxCENTER|wxOK);
	}
}

void MainFrame::OnExitClicked(wxCommandEvent& event)
{
	Destroy();
}

void MainFrame::OnAboutClicked(wxCommandEvent& event)
{
	DlgAbout dlg(this);
	dlg.ShowModal();
}
