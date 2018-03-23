#include "file2checkmodel.h"

const wxChar* szStatus[F2CS_COUNT] = {
	_("Unknown"),
	_("Waiting"),
	_("Calculating"),
	_("Ready")
};

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
	wxString sValue;
	long lValue;
	if (node->GetName()==_T("F2Chk")) // First level entry ?
	{
		switch(col)
		{
			case 0:
				variant=node->GetAttribute(_T("Path"));
				break;
			case 1:
				sValue = node->GetAttribute(_T("Status"));
				if (sValue == szStatus[F2CS_CALCULATING])
				{
					node->GetAttribute(_T("Percent"), _T("0")).ToLong(&lValue);
					variant = wxGetTranslation(sValue) + _T(" : ") + wxString::Format(_("(%d%% done)"), lValue);
				}
				else
				{
					variant = wxGetTranslation(sValue);
				}
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
	if (!item.IsOk()) // root item has no parent
		return wxDataViewItem(0);

	wxXmlNode* node = (wxXmlNode*)item.GetID();
	if (node->GetName() == _T("F2Chk"))
	{
		return wxDataViewItem(0);
	}
	else
	{
		return wxDataViewItem(node->GetParent());
	}
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

void File2CheckModel::Clear()
{
	delete m_rootItem;
	m_rootItem=NULL;
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
		node->AddAttribute(_T("Status"), szStatus[F2CS_WAITING]);
	m_rootItem->AddChild(node);

	wxDataViewItem parent(0);
	wxDataViewItem child(node);
	ItemAdded(parent, child);

	return node;
}

const wxXmlNode* File2CheckModel::GetFirstItem(const int status)
{
	if (m_rootItem==NULL)
		return NULL;
	if ((status<F2CS_UNKNOWN)||(status>=F2CS_COUNT))
		return NULL;
	wxXmlNode *node = m_rootItem->GetChildren();

	while(node!=NULL)
	{
		if ((status == F2CS_UNKNOWN) || (node->GetAttribute(_T("Status")) == szStatus[status]))
			return node;
		node = node->GetNext();
	}
	// Not found ?
	return NULL;
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
			if (SetChecksum(node, type, value))
			{
				ItemChanged(wxDataViewItem(node));
				return true;
			}
			else
			{
				return false;
			}
		}
		node=node->GetNext();
	}
	return false;

}

bool File2CheckModel::SetItemChecksums(const wxXmlNode* item, const wxArrayInt& types, const wxArrayString& values)
{
	if (item == NULL)
		return false;
	if (types.GetCount()!=values.GetCount())
		return false;

	for (size_t i=0; i<types.GetCount(); ++i)
	{
		if (!SetChecksum(item, (HashType)types[i], values[i]))
			return false;
	}
	ItemChanged(wxDataViewItem((void*)item));
	return true;
}

int File2CheckModel::GetItemStatus(const wxXmlNode* item)
{
	if (item==NULL)
		return F2CS_UNKNOWN;
	if (m_rootItem==NULL)
		return F2CS_UNKNOWN;
	wxXmlNode *node=m_rootItem->GetChildren();
	while(node!=NULL)
	{
		if (node==item)
		{
			wxString sStatus = node->GetAttribute(_T("Status"), szStatus[F2CS_UNKNOWN]);
			for (int i=0; i<F2CS_COUNT; ++i)
			{
				if (sStatus == szStatus[i])
					return i;
			}
			return F2CS_UNKNOWN;
		}
		node=node->GetNext();
	}
	return F2CS_UNKNOWN;
}

bool File2CheckModel::SetItemStatus(const wxXmlNode* item, int status, int percent)
{
	if (item == NULL)
		return false;
	if (m_rootItem == NULL)
		return false;
	if ((status <= F2CS_UNKNOWN)||(status >= F2CS_COUNT))
		return false;
	wxXmlNode *node=m_rootItem->GetChildren();
	while(node!=NULL)
	{
		if (node == item)
		{
			if (node->HasAttribute(_T("Status")))
				node->DeleteAttribute(_T("Status"));
			node->AddAttribute(_T("Status"), szStatus[status]);
			if (status == F2CS_CALCULATING)
			{
				if (node->HasAttribute(_T("Percent")))
					node->DeleteAttribute(_T("Percent"));
				node->AddAttribute(_T("Percent"), wxString::Format(_T("%d"), percent));
			}
			ItemChanged(wxDataViewItem(node));
			return true;
		}
		node = node->GetNext();
	}

	return false;
}

bool File2CheckModel::SetChecksum(const wxXmlNode* node, HashType type, const wxString& value)
{
	if (node==NULL)
		return false;
	if ((type<=HT_UNKNOWN)||(type>=HT_COUNT))
		return false;
	if (value.IsEmpty())
		return false;
	if (m_rootItem==NULL)
		return false;
	if (node->GetName()!=_T("F2Chk"))
		return false;

	wxXmlNode *itmNode = m_rootItem->GetChildren();
	while(itmNode!=NULL)
	{
		if (itmNode == node)
			break;
		itmNode = itmNode->GetNext();
	}
	if (itmNode==NULL)
		return false;
	wxXmlNode *subNode=itmNode->GetChildren();
	while(subNode!=NULL)
	{
		if (subNode->GetName()==szHashNames[type])
		{
			// Replace the actual value
			wxXmlNode *tmpNode=subNode->GetChildren();
			subNode->RemoveChild(tmpNode);
			delete tmpNode;
			subNode->AddChild(new wxXmlNode(wxXML_TEXT_NODE, _T(""), value));
			ItemChanged(wxDataViewItem(subNode));
			return true;
		}
		subNode=subNode->GetNext();
	}
	subNode=new wxXmlNode(wxXML_ELEMENT_NODE, szHashNames[type]);
	subNode->AddChild(new wxXmlNode(wxXML_TEXT_NODE, _T(""), value));
	itmNode->AddChild(subNode);
	ItemAdded(wxDataViewItem(itmNode), wxDataViewItem(subNode));
	return true;
}
