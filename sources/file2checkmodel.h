#ifndef __FILE2CHECKMODEL_H_INCLUDED__
#define __FILE2CHECKMODEL_H_INCLUDED__

#include <wx/wx.h>
#include <wx/dataview.h>

class File2CheckModel : public wxDataViewModel
{
	public:
		File2CheckModel();
		virtual ~File2CheckModel();
		virtual unsigned int GetColumnCount() const { return 2; }
		virtual wxString GetColumnType( unsigned int col ) const;
		virtual void GetValue( wxVariant &variant, const wxDataViewItem &item, unsigned int col ) const;
		virtual bool SetValue( const wxVariant &variant, const wxDataViewItem &item, unsigned int col );
		virtual wxDataViewItem GetParent( const wxDataViewItem &item ) const;
		virtual bool IsContainer( const wxDataViewItem &item ) const;
		virtual unsigned int GetChildren( const wxDataViewItem &parent, wxDataViewItemArray &array ) const;
	protected:
	private:
};

#endif // __FILE2CHECKMODEL_H_INCLUDED__
