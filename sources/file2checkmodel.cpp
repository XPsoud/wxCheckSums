#include "file2checkmodel.h"

File2CheckModel::File2CheckModel()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"File2CheckModel\" object\n"));
#endif // __WXDEBUG__
	m_rootItem=NULL;
}

File2CheckModel::~File2CheckModel()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"File2CheckModel\" object\n"));
#endif // __WXDEBUG__

	Clear();
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
	if (!item.IsOk())
		return;
	wxXmlNode *node=(wxXmlNode*)item.GetID();
	if (node->GetName()==_T("F2Chk")) // First level entry ?
	{
		switch(col)
		{
			case 0:
				variant=node->GetAttribute(_T("Path"));
				break;
			case 1:
				variant=wxEmptyString;
				break;
		}
	}
	else
	{
		switch(col)
		{
			case 0: // Hash name
				variant=wxGetTranslation(node->GetName());
				break;
			case 1: // Hash value
				variant=node->GetNodeContent();
				break;
		}
	}
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
	if (!item.IsOk()) // root item ?
	{
		if (m_rootItem==NULL)
			return false;
		else
			return (m_rootItem->GetChildren()!=NULL);
	}

	wxXmlNode *node=(wxXmlNode*)item.GetID();

	if (node->GetName()==_T("F2Chk"))
		return (node->GetChildren()!=NULL);
	else
		return false;
}

unsigned int File2CheckModel::GetChildren(const wxDataViewItem& parent, wxDataViewItemArray& array) const
{
	unsigned int iCount=0;
	if (!parent.IsOk()) // First level entries ?
	{
		if (m_rootItem==NULL)
			return 0;

		wxXmlNode *node=m_rootItem->GetChildren();
		while(node!=NULL)
		{
			array.Add(wxDataViewItem(node));
			iCount++;
			node=node->GetNext();
		}
		return iCount;
	}
	wxXmlNode *prntNode=(wxXmlNode*)parent.GetID();
	wxXmlNode *node=prntNode->GetChildren();
	while(node!=NULL)
	{
		array.Add(wxDataViewItem(node));
		iCount++;
		node=node->GetNext();
	}
	return iCount;
}

const wxXmlNode* File2CheckModel::AddFile2Check(const wxString& filename)
{
	if (filename.IsEmpty())
		return NULL;
	if (!wxFileExists(filename))
		return NULL;

	if (m_rootItem==NULL)
		m_rootItem=new wxXmlNode(wxXML_ELEMENT_NODE, _T("Root"));
	wxXmlNode *node=new wxXmlNode(wxXML_ELEMENT_NODE, _T("F2Chk"));
		node->AddAttribute(_T("Path"), filename);
	m_rootItem->AddChild(node);

	return node;
}

bool File2CheckModel::SetItemChecksum(const wxXmlNode* item, HashType type, const wxString& value)
{
	if (item==NULL)
		return false;
	if ((type<=HT_UNKNOWN)||(type>=HT_COUNT))
		return false;
	if (value.IsEmpty())
		return false;
	if (m_rootItem==NULL)
		return false;
	wxXmlNode *node=m_rootItem->GetChildren();
	while(node!=NULL)
	{
		if (node==item)
		{
			wxXmlNode *subNode=node->GetChildren();
			while(subNode!=NULL)
			{
				if (subNode->GetName()==szHashNames[type])
				{
					// Replace the actual value
					wxXmlNode *tmpNode=subNode->GetChildren();
					subNode->RemoveChild(tmpNode);
					delete tmpNode;
					subNode->AddChild(new wxXmlNode(wxXML_TEXT_NODE, _T(""), value));
					return true;
				}
				subNode=subNode->GetNext();
			}
			subNode=new wxXmlNode(wxXML_ELEMENT_NODE, szHashNames[type]);
			subNode->AddChild(new wxXmlNode(wxXML_TEXT_NODE, _T(""), value));
			node->AddChild(subNode);
			return true;
		}
		node=node->GetNext();
	}
	return false;

}

void File2CheckModel::Clear()
{
	delete m_rootItem;
	m_rootItem=NULL;
}
