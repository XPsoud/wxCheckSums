#include "file2checkpanel.h"

#include "buttonsicons.h"
#include "filehashthread.h"
#include "filedroptargets.h"
#include "settingsmanager.h"

#include <wx/clipbrd.h>

wxDEFINE_EVENT(wxEVT_CHECKSUM_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_FILEPANEL_STARTED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_FILEPANEL_STOPPED, wxCommandEvent);

File2CheckPanel::File2CheckPanel(wxWindow* parent, const wxString& title)
	: wxPanel(parent, -1)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"File2CheckPanel\" object\n"));
#endif // __WXDEBUG__

	m_thread=NULL;

	for (int i=0; i<HT_COUNT; ++i)
		m_sHash[i]=wxEmptyString;

	SetMinSize(wxSize(450,-1));

	CreateControls(title);
	ConnectControls();
}
File2CheckPanel::~File2CheckPanel()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"File2CheckPanel\" object\n"));
#endif // __WXDEBUG__
}

bool File2CheckPanel::HasResult()
{
	for (int i=0; i<HT_COUNT; ++i)
	{
		if (!m_sHash[i].IsEmpty())
			return true;
	}
	return false;
}

bool File2CheckPanel::IsRunning()
{
	if (m_thread==NULL)
		return false;

	return m_thread->IsRunning();
}

wxString File2CheckPanel::GetResult(HashType type)
{
	if ((type<=HT_UNKNOWN)||(type>+HT_COUNT))
		return wxEmptyString;

	return m_sHash[type];
}

void File2CheckPanel::UpdateEnabledHashTypes(int mask)
{
	int iMask=mask;
	// If the mask correspond to an invalid value (<=0 or >HT_ALL)
	// we get its value from the settings manager
	if ((iMask<=0)||(iMask>HT_ALL))
	{
		iMask=0;
		SettingsManager& options=SettingsManager::Get();
		for (int i=0; i<HT_COUNT; ++i)
		{
			if (options.GetHashMethodEnabled((HashType)i))
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

HashType File2CheckPanel::GetSelectedHashType()
{
	int iSel=m_cmbHashType->GetSelection();
	if (iSel!=wxNOT_FOUND)
	{
		size_t iType=(size_t)m_cmbHashType->GetClientData(iSel);
		return (HashType)iType;
	}
	return HT_UNKNOWN;
}

void File2CheckPanel::CreateControls(const wxString& title)
{
	wxBoxSizer* mainsizer=new wxBoxSizer(wxVERTICAL);

		wxStaticBoxSizer* box=new wxStaticBoxSizer(wxVERTICAL, this, title);

			wxBoxSizer* line1=new wxBoxSizer(wxHORIZONTAL);
				m_txtFileName=new wxTextCtrl(this, -1, wxEmptyString);
				line1->Add(m_txtFileName, 1, wxALL|wxALIGN_CENTER_VERTICAL, 0);
				m_btnBrowse=new wxButton(this, -1, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
					m_btnBrowse->SetToolTip(_("Open the file selection dialog box"));
				line1->Add(m_btnBrowse, 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
			box->Add(line1, 0, wxALL|wxEXPAND, 5);

			m_szrLine2=new wxBoxSizer(wxHORIZONTAL);
				m_cmbHashType=new wxChoice(this, -1);
					UpdateEnabledHashTypes();
					m_cmbHashType->SetSelection(0);
				m_szrLine2->Add(m_cmbHashType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0);
				m_txtResult=new wxTextCtrl(this, -1, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
				m_txtResult->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE));
				m_szrLine2->Add(m_txtResult, 1, wxLEFT, 5);
				m_btnCopy=new wxBitmapButton(this, wxID_COPY, wxGet_copy_png_Bitmap());
					m_btnCopy->SetToolTip(_("Copy displayed value to clipboard"));
				m_szrLine2->Add(m_btnCopy, 0, wxLEFT, 5);
				m_btnCopyAll=new wxBitmapButton(this, wxID_PASTE, wxGet_copyall_png_Bitmap());
					m_btnCopyAll->SetToolTip(_("Copy all values to clipboard"));
				m_szrLine2->Add(m_btnCopyAll, 0, wxLEFT, 5);
				m_pgbProgress=new wxGauge(this, -1, 1000);
				m_szrLine2->Add(m_pgbProgress, 1, wxALL|wxEXPAND, 0);
				m_btnCancel=new wxButton(this, wxID_CANCEL, wxGetStockLabel(wxID_CANCEL, wxSTOCK_FOR_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
				m_szrLine2->Add(m_btnCancel, 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
			box->Add(m_szrLine2, 0, wxALL|wxEXPAND, 5);

		mainsizer->Add(box, 1, wxALL|wxEXPAND, 5);

		m_pgbProgress->Hide();
		m_btnCancel->Hide();

	SetSizer(mainsizer);

	// Accept file dropped from file manager
	m_txtFileName->SetDropTarget(new SingleFileDropTarget(this));
}

void File2CheckPanel::ConnectControls()
{
	m_btnBrowse->Bind(wxEVT_BUTTON, &File2CheckPanel::OnButtonBrowseClicked, this);
	m_txtFileName->Bind(wxEVT_TEXT, &File2CheckPanel::OnFilenameChanged, this);
	m_txtResult->Bind(wxEVT_TEXT, &File2CheckPanel::OnResultChanged, this);
	Bind(wxEVT_FILES_DROPPED, &File2CheckPanel::OnFileDropped, this);
	m_btnCancel->Bind(wxEVT_BUTTON, &File2CheckPanel::OnBtnCancelClicked, this);
	Bind(wxEVT_THREAD_WORKING, &File2CheckPanel::OnThreadEvent, this);
	Bind(wxEVT_THREAD_ENDED, &File2CheckPanel::OnThreadEvent, this);
	m_cmbHashType->Bind(wxEVT_CHOICE, &File2CheckPanel::OnCmbHashTypeChanged, this);
	m_btnCopy->Bind(wxEVT_UPDATE_UI, &File2CheckPanel::OnUpdateUI_BtnCopy, this);
	m_btnCopy->Bind(wxEVT_BUTTON, &File2CheckPanel::OnBtnCopyclicked, this);
	m_btnCopyAll->Bind(wxEVT_UPDATE_UI, &File2CheckPanel::OnUpdateUI_BtnCopyAll, this);
	m_btnCopyAll->Bind(wxEVT_BUTTON, &File2CheckPanel::OnBtnCopyAllclicked, this);
}

void File2CheckPanel::OnButtonBrowseClicked(wxCommandEvent& event)
{
	wxString sMsg=wxFileSelectorPromptStr;
	wxString sDefPath=_T("");
	wxString sDefName=_T("");
	wxString sFilter=wxFileSelectorDefaultWildcardStr;
	int iStyle=wxFD_OPEN | wxFD_FILE_MUST_EXIST;

	wxFileDialog fdlg(this, sMsg, sDefPath, sDefName, sFilter, iStyle);
	if (fdlg.ShowModal()==wxID_CANCEL) return;

	m_txtFileName->SetValue(fdlg.GetPath());
}

void File2CheckPanel::OnFileDropped(wxCommandEvent& event)
{
	m_txtFileName->SetValue(event.GetString());
}

void File2CheckPanel::OnFilenameChanged(wxCommandEvent& event)
{
	wxString sFName=m_txtFileName->GetValue();
	if (sFName.IsEmpty())
		return;
	if (!wxFileExists(sFName))
	{
		m_txtFileName->SetForegroundColour(*wxRED);
		m_txtFileName->Refresh();
		return;
	}
	else
	{
		m_txtFileName->SetForegroundColour(wxNullColour);
		m_txtFileName->Refresh();
	}

	m_thread=new FileHashThread(this);
	if (!m_thread->SetFile2Hash(m_txtFileName->GetValue()))
	{
		delete m_thread;
		m_thread=NULL;
		return;
	}
	// Create the enabled hash methods mask from the client datas of the combobox
	int iMask=0, iCount=m_cmbHashType->GetCount();
	for (int i=0; i<iCount; ++i)
	{
		size_t iType=(size_t)m_cmbHashType->GetClientData(i);
		iMask |= 1<<iType;
	}
	m_thread->SetHashingFilter(iMask);
	m_txtFileName->Disable();
	m_btnBrowse->Disable();
	m_thread->Run();
#ifdef __WXDEBUG__
	m_dtStart=wxDateTime::UNow();
	wxPrintf(_T("File2CheckPanel(Id=%d) : Started calculation on %s\n"), GetId(), m_dtStart.Format(_T("%c,%l")));
#endif // __WXDEBUG__

	wxCommandEvent evt(wxEVT_FILEPANEL_STARTED, GetId());
	AddPendingEvent(evt);
}

void File2CheckPanel::OnResultChanged(wxCommandEvent& event)
{
	wxCommandEvent evt(wxEVT_CHECKSUM_CHANGED, GetId());
	AddPendingEvent(evt);
}

void File2CheckPanel::OnBtnCancelClicked(wxCommandEvent& event)
{
	if (m_thread->IsRunning())
	{
		if (wxMessageBox(_("Stop calculation ?"), _("Confirmation"), wxICON_QUESTION|wxYES_NO|wxCENTER)!=wxYES)
			return;
		m_thread->Delete();
		wxCommandEvent evt(wxEVT_FILEPANEL_STOPPED, GetId());
		AddPendingEvent(evt);
	}
	else
	{
		m_cmbHashType->Show();
		m_txtResult->Show();
		m_btnCopy->Show();
		m_btnCopyAll->Show();
		m_pgbProgress->Hide();
		m_btnCancel->Hide();
		m_txtFileName->Enable();
		m_btnBrowse->Enable();
		m_szrLine2->Layout();
	}
}

void File2CheckPanel::OnThreadEvent(wxThreadEvent& event)
{
	if (event.GetEventType()==wxEVT_THREAD_ENDED)
	{
#ifdef __WXDEBUG__
		wxDateTime dtEnd=wxDateTime::UNow();
		wxTimeSpan duration=dtEnd-m_dtStart;
		wxPrintf(_T("File2CheckPanel(Id=%d) : Calculation ended on %s\n"), GetId(), dtEnd.Format(_T("%c,%l")));
		wxPrintf(_T("\tDuration : %s\n"), duration.Format(_T("%H:%M:%S,%l")));
#endif // __wxDEBUG__
		if (m_pgbProgress->IsShown())
		{
			m_cmbHashType->Show();
			m_txtResult->Show();
			m_btnCopy->Show();
			m_btnCopyAll->Show();
			m_pgbProgress->Hide();
			m_btnCancel->Hide();
			m_szrLine2->Layout();
		}
		m_txtFileName->Enable();
		m_btnBrowse->Enable();
		if (m_thread==NULL)
			return;
		if (event.GetInt()!=-1)
		{
			for (int i=0; i<HT_COUNT; ++i)
				m_sHash[i]=m_thread->GetHexDigest((HashType)i);
		}
		else
		{
			for (int i=0; i<HT_COUNT; ++i)
				m_sHash[i]=wxEmptyString;
		}

		wxCommandEvent evt(wxEVT_CHOICE, m_cmbHashType->GetId());
		OnCmbHashTypeChanged(evt);

		delete m_thread;
		m_thread=NULL;

		evt.SetEventType(wxEVT_FILEPANEL_STOPPED);
		evt.SetId(GetId());
		AddPendingEvent(evt);

		return;
	}
	if (event.GetEventType()==wxEVT_THREAD_WORKING)
	{
		if (!m_pgbProgress->IsShown())
		{
			m_cmbHashType->Hide();
			m_txtResult->Hide();
			m_btnCopy->Hide();
			m_btnCopyAll->Hide();
			m_pgbProgress->Show();
			m_btnCancel->Show();
			m_szrLine2->Layout();
		}
		m_pgbProgress->SetValue(event.GetInt());

		return;
	}
}

void File2CheckPanel::OnCmbHashTypeChanged(wxCommandEvent& event)
{
	SettingsManager& options=SettingsManager::Get();
	HashType iType=GetSelectedHashType();
	if (iType==HT_UNKNOWN)
		return;
	if (options.GetAlwaysUCase())
		m_txtResult->SetValue(m_sHash[iType].Upper());
	else
		m_txtResult->SetValue(m_sHash[iType]);
}

void File2CheckPanel::OnUpdateUI_BtnCopy(wxUpdateUIEvent& event)
{
	event.Enable(m_txtResult->IsEmpty()==false);
}

void File2CheckPanel::OnBtnCopyclicked(wxCommandEvent& event)
{
	if (!wxTheClipboard->Open())
	{
		wxMessageBox(_("Unable to open the clipboard!"), _("Error"), wxICON_EXCLAMATION|wxOK|wxCENTER);
		return;
	}
	wxTheClipboard->SetData(new wxTextDataObject(m_txtResult->GetValue()));
	wxTheClipboard->Close();
}

void File2CheckPanel::OnUpdateUI_BtnCopyAll(wxUpdateUIEvent& event)
{
	event.Enable(HasResult());
}

void File2CheckPanel::OnBtnCopyAllclicked(wxCommandEvent& event)
{
	if (!wxTheClipboard->Open())
	{
		wxMessageBox(_("Unable to open the clipboard!"), _("Error"), wxICON_EXCLAMATION|wxOK|wxCENTER);
		return;
	}
	wxString sData=wxEmptyString;
	for (int i=0; i<HT_COUNT; ++i)
	{
		if (!m_sHash[i].IsEmpty())
		{
			if (!sData.IsEmpty())
				sData << _T("\n");
			sData << m_sHash[i];
		}
	}
	wxTheClipboard->SetData(new wxTextDataObject(sData));
	wxTheClipboard->Close();
}
