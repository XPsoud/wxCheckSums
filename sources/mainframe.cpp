#include "mainframe.h"

#include "main.h"
#include "dlgabout.h"
#include "appversion.h"
#include "dlgoptions.h"
#include "filterpanel.h"
#include "settingsmanager.h"
#include "file2checkpanel.h"

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
#endif // __WXDEBUG__

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
#endif // __WXDEBUG__
}

void MainFrame::CreateControls()
{
	// Status bar (2 fields)
	wxStatusBar* stb=CreateStatusBar(2);
	// String to display in the second field
	wxString sTxt=_T(" ") + wxGetApp().GetBuildInfos();
	// Calculation of the needed width for this text
	int widths[2];
#ifndef __WXMSW__
	wxStaticText *tmpLabel=new wxStaticText(this, wxID_STATIC, sTxt);
	tmpLabel->GetSize(&widths[1], &widths[0]);
	delete tmpLabel;
#else
	wxClientDC dc(stb);
	dc.GetTextExtent(sTxt, &widths[1], &widths[0]);
#endif
	widths[0]=-1;
	stb->SetStatusWidths(2, widths);

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
	m_nBook=new wxNotebook(this, -1);
	wxPanel *page;
	wxBoxSizer *szr, *szrMain;

	szrMain=new wxBoxSizer(wxVERTICAL);

	// "1 - 2 files" tab
	page=new wxPanel(m_nBook, -1);
	szr=new wxBoxSizer(wxVERTICAL);
		m_pnlFilter[0]=new FilterPanel(page);
		szr->Add(m_pnlFilter[0], 0, wxALL|wxEXPAND, 0);
		for (int i=0; i<FILESPANEL_COUNT; ++i)
		{
			m_pnlFile[i]=new File2CheckPanel(page, wxString::Format(_("File #%d"), i+1));
			szr->Add(m_pnlFile[i], 0, wxALL|wxEXPAND, 0);
		}
	page->SetSizer(szr);
	m_nBook->AddPage(page, _("1-2 files"));

	// "Multiple files" tab
	page=new wxPanel(m_nBook, -1);
	szr=new wxBoxSizer(wxVERTICAL);
		m_pnlFilter[1]=new FilterPanel(page);
		szr->Add(m_pnlFilter[1], 0, wxALL|wxEXPAND, 0);
		m_dvcFiles=new wxDataViewCtrl(page, -1);
			wxDataViewTextRenderer *tr=new wxDataViewTextRenderer();
            wxDataViewColumn *col0=new wxDataViewColumn(_("File"), tr, 0, wxDVC_DEFAULT_WIDTH, wxALIGN_LEFT);
            m_dvcFiles->AppendColumn(col0);
			tr=new wxDataViewTextRenderer();
            wxDataViewColumn *col1=new wxDataViewColumn(_("Status"), tr, 1, 200, wxALIGN_LEFT);
            m_dvcFiles->AppendColumn(col1);
		szr->Add(m_dvcFiles, 1, wxALL|wxEXPAND, 0);
	page->SetSizer(szr);
	m_nBook->AddPage(page, _("Multiple files"));

	// "Simple text" tab
	page=new wxPanel(m_nBook, -1);
	szr=new wxBoxSizer(wxVERTICAL);
		m_pnlFilter[2]=new FilterPanel(page);
		szr->Add(m_pnlFilter[2], 0, wxALL|wxEXPAND, 0);
	page->SetSizer(szr);
	m_nBook->AddPage(page, _("Simple text"));

	szrMain->Add(m_nBook, 1, wxALL|wxEXPAND, 0);

	SetSizer(szrMain);
	szrMain->SetSizeHints(this);
}

void MainFrame::ConnectControls()
{
	// General events handlers
	Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
	Bind(wxEVT_MOVE, &MainFrame::OnMove, this);
	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

	Bind(wxEVT_CHECKSUM_CHANGED, &MainFrame::OnCheckSumsChanged, this);
	Bind(wxEVT_FILEPANEL_STARTED, &MainFrame::OnFilePanelEvent, this);
	Bind(wxEVT_FILEPANEL_STOPPED, &MainFrame::OnFilePanelEvent, this);
	Bind(wxEVT_FILTER_CHANGED, &MainFrame::OnFilterChanged, this);

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
	// Save the enabled methods state
	int iMask=0;
	for (int i=0; i<HT_COUNT; ++i)
		if (m_settings.GetHashMethodEnabled((HashType)i))
			iMask |= 1<<i;

	DlgOptions dlg(this);
	dlg.ShowModal();
	if (m_settings.GetProhibitI18N()!=bOldLng)
	{
		wxMessageBox(_("You changed the translation settings.\nYou must restart the application to see this in effect."), _("Restart needed"), wxICON_INFORMATION|wxCENTER|wxOK);
	}
	// Check if the enabled method state has changed
	int iMask2=0;
	for (int i=0; i<HT_COUNT; ++i)
		if (m_settings.GetHashMethodEnabled((HashType)i))
			iMask2 |= 1<<i;
	// If it has changed, ask the user if he want to update the filter panel
	if (iMask2!=iMask)
	{
		int iRes=wxMessageBox(_("You changed the enabled/disabled state of hashing methods.\nDo you want to update the temporary values ?"), _("Filter changed"), wxICON_QUESTION|wxYES_NO|wxCENTER);
		if (iRes==wxYES)
		{
			for (int i=0; i<3; ++i)
				m_pnlFilter[i]->UpdateFromSettings();
			for (int i=0; i<FILESPANEL_COUNT; ++i)
				m_pnlFile[i]->UpdateEnabledHashTypes(iMask2);
		}
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

void MainFrame::OnCheckSumsChanged(wxCommandEvent& event)
{
	for (int i=0; i<FILESPANEL_COUNT; ++i)
	{
		if (!m_pnlFile[i]->HasResult())
		{
			SetStatusText(wxEmptyString);
			return;
		}
	}
	bool bEqual=false, bDiff=false;
	wxString sHash;
	for (int j=0; j<HT_COUNT; ++j)
	{
		for (int i=0; i<FILESPANEL_COUNT; ++i)
		{
			if (i==0)
			{
				sHash=m_pnlFile[i]->GetResult((HashType)j);
			}
			else
			{
				if (m_pnlFile[i]->GetResult((HashType)j)!=sHash)
				{
					bDiff=true;
				}
				else
				{
					bEqual=true;
				}
			}
		}
	}
	if ((bDiff==false) && (bEqual==true))
	{
		SetStatusText(_("All checksums are identicals"));
	}
	else
	{
		if ((bDiff==true) && (bEqual==true))
		{
			SetStatusText(_("Some checksums are the same but not all"));
		}
		else
		{
			if ((bDiff==true) && (bEqual==false))
			{
				SetStatusText(_("All checksums are differents"));
			}
			else
			{
				// Should never arrives, but who knows...
				SetStatusText(_("An error occurred whith checksums"));
			}
		}
	}
}

void MainFrame::OnFilePanelEvent(wxCommandEvent& event)
{
	// Depending on the running state of the files panels
	// we can enable or disable the filter panel
	for (int i=0; i<FILESPANEL_COUNT; ++i)
	{
		if (m_pnlFile[i]->IsRunning())
		{
			m_pnlFilter[0]->Disable();
			return;
		}
	}
	// If we get here, no file panel is running
	m_pnlFilter[0]->Enable();
}

void MainFrame::OnFilterChanged(wxCommandEvent& event)
{
	// Witch filterpanel sent this event ?
	int iIndex=wxNOT_FOUND;
	for (int i=0; i<3; ++i)
	{
		if (event.GetId()==m_pnlFilter[i]->GetId())
		{
			iIndex=i;
			break;
		}
	}
	if (iIndex==wxNOT_FOUND)
		return;
	switch(iIndex)
	{
		case 0: // 1-2 files tab
			for (int i=0; i<FILESPANEL_COUNT; ++i)
			{
				m_pnlFile[i]->UpdateEnabledHashTypes(event.GetInt());
			}
			break;
		case 1: // Multiple files tab
			break;
		case 2: // Simple text tab
			break;
	}
}
