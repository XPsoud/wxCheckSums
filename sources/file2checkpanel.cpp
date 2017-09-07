#include "file2checkpanel.h"

#include "filedroptargets.h"

wxDEFINE_EVENT(wxEVT_CHECKSUM_CHANGED, wxCommandEvent);

File2CheckPanel::File2CheckPanel(wxWindow* parent, const wxString& title)
	: wxPanel(parent, -1)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"File2CheckPanel\" object\n"));
#endif // __WXDEBUG__
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
				m_lblHashType=new wxStaticText(this, wxID_STATIC, _("MD5:"));
				m_szrLine2->Add(m_lblHashType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0);
				m_txtResult=new wxTextCtrl(this, -1, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
				m_txtResult->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE));
				m_szrLine2->Add(m_txtResult, 1, wxLEFT, 5);
				m_pgbProgress=new wxGauge(this, -1, 100);
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
	m_lblHashType->Hide();
	m_txtResult->Hide();
	m_pgbProgress->Show();
	m_btnCancel->Show();
	m_szrLine2->Layout();
}

void File2CheckPanel::OnFilenameChanged(wxCommandEvent& event)
{
	// TODO (Xaviou#1#): To be written
}

void File2CheckPanel::OnResultChanged(wxCommandEvent& event)
{
	wxCommandEvent evt(wxEVT_CHECKSUM_CHANGED, GetId());
	AddPendingEvent(evt);
}

void File2CheckPanel::OnBtnCancelClicked(wxCommandEvent& event)
{
	m_lblHashType->Show();
	m_txtResult->Show();
	m_pgbProgress->Hide();
	m_btnCancel->Hide();
	m_szrLine2->Layout();
}
