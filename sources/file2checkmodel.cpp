#include "file2checkmodel.h"

File2CheckModel::File2CheckModel()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"File2CheckModel\" object\n"));
#endif // __WXDEBUG__
}

File2CheckModel::~File2CheckModel()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"File2CheckModel\" object\n"));
#endif // __WXDEBUG__
}

wxString File2CheckModel::GetColumnType(unsigned int col) const
{
#ifdef __WXDEBUG__
	wxPrintf(_T("\tFile2CheckModel::GetColumnType(%d)\n"), col);
#endif // __WXDEBUG__
	return _T("string");
}

void File2CheckModel::GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const
{
#ifdef __WXDEBUG__
	wxPrintf(_T("\tFile2CheckModel::GetValue(??, %d)\n"), col);
#endif // __WXDEBUG__
}

bool File2CheckModel::SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col)
{
	return true;
}

wxDataViewItem File2CheckModel::GetParent(const wxDataViewItem& item) const
{
	return wxDataViewItem(0);
}

bool File2CheckModel::IsContainer(const wxDataViewItem& item) const
{
	return false;
}

unsigned int File2CheckModel::GetChildren(const wxDataViewItem& parent, wxDataViewItemArray& array) const
{
	return 0;
}
