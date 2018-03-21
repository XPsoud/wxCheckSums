#ifndef __FILE2CHECKMODEL_H_INCLUDED__
#define __FILE2CHECKMODEL_H_INCLUDED__

#include <wx/wx.h>
#include <wx/xml/xml.h>
#include <wx/dataview.h>

#include "checksums.h"

enum File2CheckStatus
{
	F2CS_UNKNOWN = 0,
	F2CS_WAITING,
	F2CS_CALCULATING,
	F2CS_READY,

	F2CS_COUNT
};

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
		virtual bool HasContainerColumns(const wxDataViewItem &item) const { return true; }
		virtual unsigned int GetChildren( const wxDataViewItem &parent, wxDataViewItemArray &array ) const;
		// Datas management
		void Clear();
		const wxXmlNode* AddFile2Check(const wxString& filename);
		bool SetItemChecksum(const wxXmlNode* item, HashType type, const wxString& value);
		bool SetItemChecksums(const wxXmlNode* item, const wxArrayInt& types, const wxArrayString& values);
		int GetItemStatus(const wxXmlNode* item);
		bool SetItemStatus(const wxXmlNode* item, int status);
	protected:
	private:
		bool SetChecksum(const wxXmlNode* node, HashType type, const wxString& value);
		wxXmlNode *m_rootItem;
};

#endif // __FILE2CHECKMODEL_H_INCLUDED__
