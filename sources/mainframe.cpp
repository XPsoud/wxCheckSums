#include "mainframe.h"

#include "main.h"
#include "dlgabout.h"
#include "appversion.h"
#include "dlgoptions.h"
#include "filterpanel.h"
#include "filehashthread.h"
#include "buttonsicons.h"
#include "settingsmanager.h"
#include "file2checkpanel.h"
#include "file2checkmodel.h"
#include "filedroptargets.h"

#include <wx/display.h>
#include <wx/filedlg.h>
#include <wx/artprov.h>
#include <wx/xml/xml.h>
#include <wx/tokenzr.h>
#include <wx/clipbrd.h>
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

	m_thread = NULL;
	m_pCurCalc = NULL;

	SetIcon(wxICON(appIcon)); // Defining app icon

	m_arsResults.Clear();

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
#ifndef __WXMAC__
		fileMenu->AppendSeparator();
#endif // __WXMAC__
		fileMenu->Append(wxID_EXIT, wxGetStockLabel(wxID_EXIT, wxSTOCK_WITH_MNEMONIC|wxSTOCK_WITH_ACCELERATOR), wxGetStockHelpString(wxID_EXIT));

	menuBar->Append(fileMenu, wxGetStockLabel(wxID_FILE));

	wxMenu* helpMenu = new wxMenu();

		helpMenu->Append(wxID_ABOUT, wxGetStockLabel(wxID_ABOUT, wxSTOCK_WITH_MNEMONIC|wxSTOCK_WITH_ACCELERATOR), wxGetStockHelpString(wxID_ABOUT));

		menuBar->Append(helpMenu, wxGetStockLabel(wxID_HELP));

	SetMenuBar(menuBar);
#ifdef __WXMAC__
	// Remove and delete the empty Help menu
	menuBar->Remove(1);
	delete helpMenu;
	// Remove and delete then empty File menu
	menuBar->Remove(0);
	delete fileMenu;
#endif // __WXMAC__

	// Controls
	m_nBook=new wxNotebook(this, -1);
	wxPanel *page;
	wxBoxSizer *szr, *szrMain;

	szrMain=new wxBoxSizer(wxVERTICAL);

	int iPnlFilter=0;

	// "1 - 2 files" tab
	page=new wxPanel(m_nBook, -1);
	szr=new wxBoxSizer(wxVERTICAL);
		m_pnlFilter[iPnlFilter]=new FilterPanel(page);
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
		iPnlFilter++;
		m_pnlFilter[iPnlFilter]=new FilterPanel(page);
		szr->Add(m_pnlFilter[iPnlFilter], 0, wxALL|wxEXPAND, 0);
		m_dvcFiles=new wxDataViewCtrl(page, -1);
			m_f2cModel=new File2CheckModel();
			m_dvcFiles->AssociateModel(m_f2cModel.get());
			wxDataViewTextRenderer *tr=new wxDataViewTextRenderer();
            wxDataViewColumn *col0=new wxDataViewColumn(_("File"), tr, 0, wxDVC_DEFAULT_WIDTH, wxALIGN_LEFT);
            m_dvcFiles->AppendColumn(col0);
			tr=new wxDataViewTextRenderer();
            wxDataViewColumn *col1=new wxDataViewColumn(_("Status"), tr, 1, 200, wxALIGN_LEFT);
            m_dvcFiles->AppendColumn(col1);
		szr->Add(m_dvcFiles, 1, wxALL|wxEXPAND, 0);
	page->SetSizer(szr);
	m_nBook->AddPage(page, _("Multiple files"));

	// Accept files dropped from file manager
	m_dvcFiles->SetDropTarget(new MultiFilesDropTarget(this));

	// "Simple text" tab
	page=new wxPanel(m_nBook, -1);
	szr=new wxBoxSizer(wxVERTICAL);
		iPnlFilter++;
		m_pnlFilter[iPnlFilter]=new FilterPanel(page);
		szr->Add(m_pnlFilter[iPnlFilter], 0, wxALL|wxEXPAND, 0);

		m_txtText2Hash=new wxTextCtrl(page, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL);
		szr->Add(m_txtText2Hash, 1, wxALL|wxEXPAND, 5);

		wxBoxSizer *lnszr=new wxBoxSizer(wxHORIZONTAL);
			m_cmbHashType=new wxChoice(page, -1);
				UpdateEnabledHashTypes();
				m_cmbHashType->SetSelection(0);
			lnszr->Add(m_cmbHashType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0);
			m_txtResult=new wxTextCtrl(page, -1, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
				m_txtResult->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE));
				lnszr->Add(m_txtResult, 1, wxLEFT, 5);
				m_btnCopy=new wxBitmapButton(page, wxID_COPY, wxGet_copy_png_Bitmap());
					m_btnCopy->SetToolTip(_("Copy displayed value to clipboard"));
				lnszr->Add(m_btnCopy, 0, wxLEFT, 5);
				m_btnCopyAll=new wxBitmapButton(page, wxID_PASTE, wxGet_copyall_png_Bitmap());
					m_btnCopyAll->SetToolTip(_("Copy all values to clipboard"));
				lnszr->Add(m_btnCopyAll, 0, wxLEFT, 5);
		szr->Add(lnszr, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
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

	Bind(wxEVT_FILES_DROPPED, &MainFrame::OnFilesDropped, this);
	Bind(wxEVT_THREAD_WORKING, &MainFrame::OnThreadEvent, this);
	Bind(wxEVT_THREAD_ENDED, &MainFrame::OnThreadEvent, this);

	m_txtText2Hash->Bind(wxEVT_TEXT, &MainFrame::OnText2HashChanged, this);
	m_cmbHashType->Bind(wxEVT_CHOICE, &MainFrame::OnCmbHashTypeChanged, this);
	m_btnCopy->Bind(wxEVT_UPDATE_UI, &MainFrame::OnUpdateUI_BtnCopy, this);
	m_btnCopy->Bind(wxEVT_BUTTON, &MainFrame::OnBtnCopyclicked, this);
	m_btnCopyAll->Bind(wxEVT_UPDATE_UI, &MainFrame::OnUpdateUI_BtnCopyAll, this);
	m_btnCopyAll->Bind(wxEVT_BUTTON, &MainFrame::OnBtnCopyAllClicked, this);

	// Menus events handlers
	Bind(wxEVT_MENU, &MainFrame::OnPreferencesClicked, this, wxID_PREFERENCES);
	Bind(wxEVT_MENU, &MainFrame::OnExitClicked, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnAboutClicked, this, wxID_ABOUT);
}

void MainFrame::StartNextCalculationThread()
{
	if (m_thread != NULL)
		return;
	const wxXmlNode* item = m_f2cModel.get()->GetFirstItem(F2CS_WAITING);
	if (item == NULL)
		return;
	m_pCurCalc = (wxXmlNode*)item;
	m_thread = new FileHashThread(this);
	if (!m_thread->SetFile2Hash(item->GetAttribute(_T("Path"))))
	{
		delete m_thread;
		m_thread = NULL;
		return;
	}
	m_thread->SetHashingFilter(m_pnlFilter[1]->GetFilterMask());
	m_thread->Run();
}

void MainFrame::UpdateEnabledHashTypes(int mask)
{
	int iMask=mask;
	// If the mask correspond to an invalid value (<=0 or >HT_ALL)
	// we get its value from the settings manager
	if ((iMask<=0)||(iMask>HT_ALL))
	{
		iMask=0;
		for (int i=0; i<HT_COUNT; ++i)
		{
			if (m_settings.GetHashMethodEnabled((HashType)i))
				iMask |= 1<<i;
		}
	}
	// Get actual selection if any
	int iItem=m_cmbHashType->GetSelection();
	HashType iType=HT_UNKNOWN;
	if (iItem!=wxNOT_FOUND)
		iType=GetSelectedHashType();
	m_cmbHashType->Freeze();
	m_cmbHashType->Clear();
	for (int i=0; i<HT_COUNT; ++i)
	{
		if (iMask & (1<<i))
		{
			iItem=m_cmbHashType->Append(wxGetTranslation(szHashNames[i]), (void*)wxUIntPtr(i));
			if (i==iType)
				m_cmbHashType->SetSelection(iItem);
		}
	}
	if (m_cmbHashType->GetSelection()==wxNOT_FOUND)
		m_cmbHashType->SetSelection(0);
	m_cmbHashType->Thaw();
}

HashType MainFrame::GetSelectedHashType()
{
	int iSel=m_cmbHashType->GetSelection();
	if (iSel!=wxNOT_FOUND)
	{
		size_t iType=(size_t)m_cmbHashType->GetClientData(iSel);
		return (HashType)iType;
	}
	return HT_UNKNOWN;
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
			for (size_t i=0; i<WXSIZEOF(m_pnlFilter); ++i)
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
	for (size_t i=0; i<WXSIZEOF(m_pnlFilter); ++i)
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
/*
		case 1: // Multiple files tab
			break;
*/
		case 1: // Simple text tab
			UpdateEnabledHashTypes(event.GetInt());
			break;
	}
}

void MainFrame::OnFilesDropped(wxCommandEvent& event)
{
	wxArrayString arsFiles = wxStringTokenize(event.GetString(), _T("\n"));
	for (size_t i=0; i<arsFiles.GetCount(); ++i)
	{
		m_f2cModel.get()->AddFile2Check(arsFiles[i]);
	}
	if (m_thread == NULL)
	{
		StartNextCalculationThread();
	}
}

void MainFrame::OnThreadEvent(wxThreadEvent& event)
{
	if (m_pCurCalc==NULL)
		return;

	if (event.GetEventType()==wxEVT_THREAD_ENDED)
	{
		if (event.GetInt()!=-1)
		{
			wxArrayInt ariTypes;
			wxArrayString arsHashes;
			wxString sHash;
			for (int i=0; i<HT_COUNT; ++i)
			{
				sHash = m_thread->GetHexDigest((HashType)i);
				if (!sHash.IsEmpty())
				{
					ariTypes.Add(i);
					arsHashes.Add(sHash);
				}
			}
			m_f2cModel.get()->SetItemChecksums(m_pCurCalc, ariTypes, arsHashes);
			m_f2cModel.get()->SetItemStatus(m_pCurCalc, F2CS_READY);
		}
		else
		{
			m_f2cModel.get()->SetItemStatus(m_pCurCalc, F2CS_WAITING);
		}
		delete m_thread;
		m_thread = NULL;
		StartNextCalculationThread();
		return;
	}
	if (event.GetEventType()==wxEVT_THREAD_WORKING)
	{
		m_f2cModel.get()->SetItemStatus(m_pCurCalc, F2CS_CALCULATING, event.GetInt()/10);
		return;
	}
}

void MainFrame::OnText2HashChanged(wxCommandEvent& event)
{
	m_arsResults.Clear();
	if (m_txtText2Hash->IsEmpty())
	{
		m_txtResult->Clear();
		return;
	}
	wxString sTxt=m_txtText2Hash->GetValue();
// TODO (Xaviou#1#): Convert newlines chars if needed
	CheckSums sum(sTxt, m_pnlFilter[WXSIZEOF(m_pnlFilter)-1]->GetFilterMask());;
	for (int i=0; i<HT_COUNT; ++i)
	{
		m_arsResults.Add(sum.GetHexDigest((HashType)i));
	}
	int iType=GetSelectedHashType();
	if (iType==HT_UNKNOWN)
		iType=0;
	if (m_settings.GetAlwaysUCase())
		m_txtResult->ChangeValue(m_arsResults[iType].Upper());
	else
		m_txtResult->ChangeValue(m_arsResults[iType]);
}

void MainFrame::OnCmbHashTypeChanged(wxCommandEvent& event)
{
	HashType iType=GetSelectedHashType();
	if (iType==HT_UNKNOWN)
		return;
	if (m_settings.GetAlwaysUCase())
		m_txtResult->ChangeValue(m_arsResults[iType].Upper());
	else
		m_txtResult->ChangeValue(m_arsResults[iType]);
}

void MainFrame::OnUpdateUI_BtnCopy(wxUpdateUIEvent& event)
{
	event.Enable(m_txtResult->IsEmpty()==false);
}

void MainFrame::OnBtnCopyclicked(wxCommandEvent& event)
{
	if (!wxTheClipboard->Open())
	{
		wxMessageBox(_("Unable to open the clipboard!"), _("Error"), wxICON_EXCLAMATION|wxOK|wxCENTER);
		return;
	}
	wxTheClipboard->SetData(new wxTextDataObject(m_txtResult->GetValue()));
	wxTheClipboard->Close();
}

void MainFrame::OnUpdateUI_BtnCopyAll(wxUpdateUIEvent& event)
{
	event.Enable(m_arsResults.IsEmpty()==false);
}

void MainFrame::OnBtnCopyAllClicked(wxCommandEvent& event)
{
	if (!wxTheClipboard->Open())
	{
		wxMessageBox(_("Unable to open the clipboard!"), _("Error"), wxICON_EXCLAMATION|wxOK|wxCENTER);
		return;
	}
	wxString sData=wxEmptyString;
	for (int i=0; i<HT_COUNT; ++i)
	{
		if (!m_arsResults[i].IsEmpty())
		{
			if (!sData.IsEmpty())
				sData << _T("\n");
			sData << m_arsResults[i];
		}
	}
	wxTheClipboard->SetData(new wxTextDataObject(sData));
	wxTheClipboard->Close();
}
