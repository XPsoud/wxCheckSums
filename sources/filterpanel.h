#ifndef __FILTERPANEL_H_INCLUDED__
#define __FILTERPANEL_H_INCLUDED__

#include <wx/wx.h>

wxDECLARE_EVENT(wxEVT_FILTER_CHANGED, wxCommandEvent);

#include "checksums.h"

class FilterPanel : public wxPanel
{
	public:
		FilterPanel(wxWindow* parent);
		virtual ~FilterPanel();
		void UpdateFromSettings();
	private:
		// Misc functions
		void CreateControls();
		void ConnectControls();
		// Events handlers
		void OnFilterChanged(wxCommandEvent& event);
		// Controls vars
		wxCheckBox *m_chkHashType[HT_COUNT];
		// Misc vars
};

#endif // __FILTERPANEL_H_INCLUDED__
