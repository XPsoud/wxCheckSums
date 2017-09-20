#include "filterpanel.h"

#include "settingsmanager.h"

wxDEFINE_EVENT(wxEVT_FILTER_CHANGED, wxCommandEvent);

FilterPanel::FilterPanel(wxWindow* parent)
	: wxPanel(parent, -1)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"FilterPanel\" object\n"));
#endif // __WXDEBUG__

	CreateControls();
	// Initialize with settings values
	for (int i=0; i<HT_COUNT; ++i)
		m_chkHashType[i]->SetValue(SettingsManager::Get().GetHashMethodEnabled((HashType)i));

	ConnectControls();
}
FilterPanel::~FilterPanel()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"FilterPanel\" object\n"));
#endif // __WXDEBUG__
}

void FilterPanel::UpdateFromSettings()
{
	for (int i=0; i<HT_COUNT; ++i)
		m_chkHashType[i]->SetValue(SettingsManager::Get().GetHashMethodEnabled((HashType)i));
}

void FilterPanel::CreateControls()
{
	wxBoxSizer* mainsizer=new wxBoxSizer(wxVERTICAL);

		wxStaticBoxSizer* box=new wxStaticBoxSizer(wxVERTICAL, this, _("Hashing methods filter:"));

			wxBoxSizer *hszr=new wxBoxSizer(wxHORIZONTAL);

				for (int i=0; i<HT_COUNT; ++i)
				{
					m_chkHashType[i]=new wxCheckBox(this, -1, wxGetTranslation(szHashNames[i]));
					if (i>0)
						hszr->AddSpacer(5);
					hszr->Add(m_chkHashType[i], 0, wxALL, 0);
				}

			box->Add(hszr, 0, wxALL|wxEXPAND, 5);

		mainsizer->Add(box, 1, wxALL|wxEXPAND, 5);

	SetSizer(mainsizer);
}

void FilterPanel::ConnectControls()
{
	Bind(wxEVT_CHECKBOX, &FilterPanel::OnFilterChanged, this);
}

void FilterPanel::OnFilterChanged(wxCommandEvent& event)
{
	// We must check that there is always at leat one value checked
	bool bOk=false;
	for (int i=0; i<HT_COUNT; ++i)
		bOk |= m_chkHashType[i]->IsChecked();
	if (!bOk)
	{
		int iLast=HT_UNKNOWN;
		for (int i=0; i<HT_COUNT; ++i)
		{
			if (m_chkHashType[i]->GetId()==event.GetId())
			{
				iLast=i;
				break;
			}
		}
		wxMessageBox(_("At least one element must remain checked!\nAborting..."), _("Forbidden"), wxICON_EXCLAMATION|wxCENTER|wxOK);
		m_chkHashType[iLast]->SetValue(true);
		return;
	}
	// All is Ok : we can inform the main frame the the filter has changed
	wxCommandEvent evt(wxEVT_FILTER_CHANGED, GetId());
	evt.SetEventObject(this);
	// Create a bitmask with values
	int iMask=0;
	for (int i=0; i<HT_COUNT; ++i)
		if (m_chkHashType[i]->IsChecked())
			iMask |= 1 << i;

	evt.SetInt(iMask);
	AddPendingEvent(evt);
}
