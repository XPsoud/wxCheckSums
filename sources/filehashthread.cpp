#include "filehashthread.h"

#include <wx/file.h>

wxDEFINE_EVENT(wxEVT_THREAD_WORKING, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_THREAD_ENDED, wxThreadEvent);

FileHashThread::FileHashThread(wxEvtHandler* handler) : wxThread(wxTHREAD_JOINABLE)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"FileHashThread\" object\n"));
#endif // __WXDEBUG__
	m_handler=handler;
	m_sFileName=wxEmptyString;
	m_sLastError=wxEmptyString;
}

FileHashThread::~FileHashThread()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"SingleFileDropTarget\" object\n"));
#endif // __WXDEBUG__
}

bool FileHashThread::SetFile2Hash(const wxString& filename)
{
	// Don't do anything if the thread is already running
	if (IsRunning())
		return false;
	// Clear the file name var
	m_sFileName=wxEmptyString;
	// A valid file name must have been specified
	if (filename.IsEmpty())
		return false;
	// The file must exist
	if (!wxFileExists(filename))
		return false;
	// Store the file name
	m_sFileName=filename;

	// All was Ok
	return true;
}

void FileHashThread::SetHashingFilter(int mask)
{
	for (int i=0; i<HT_COUNT; ++i)
		m_csHash.EnableHashType((HashType)i, (mask & (1<<i)));
}

wxString FileHashThread::GetHexDigest(HashType type)
{
	return m_csHash.GetHexDigest(type);
}

wxThread::ExitCode FileHashThread::Entry()
{
	if (m_sFileName.IsEmpty())
	{
		m_sLastError=_("No valid file specified");
		return (ExitCode)-1;
	}

	// Open the file
	wxFile file(m_sFileName, wxFile::read);
	if (!file.IsOpened())
	{
		m_sLastError=_("Unable to open the file");
		return (ExitCode)-1;
	}

	wxStopWatch sw;

	wxFileOffset iFLen=file.Length(), iDone=0;
	int iLen;
	unsigned char buffer[512+5];
	bool bStopWanted=false;
	wxThreadEvent evt(wxEVT_THREAD_WORKING);

	do
	{
		iLen=file.Read(buffer, 512);
		iDone += iLen;

		if (sw.Time()>500)
		{
			int prct=iDone/(iFLen/1000);
			if (prct>1000) prct=1000;

			evt.SetInt(prct);
			wxQueueEvent(m_handler, evt.Clone());

			sw.Start();
		}

		if (TestDestroy())
			bStopWanted=true;

		if (iLen>0)
			m_csHash.Update(buffer, iLen);

	} while( (!file.Eof()) && (!bStopWanted) );

	if (bStopWanted)
	{
		evt.SetEventType(wxEVT_THREAD_ENDED);
		evt.SetInt(-1);
		wxQueueEvent(m_handler, evt.Clone());

		return (ExitCode)-1;
	}

	m_csHash.Finalize();

	evt.SetEventType(wxEVT_THREAD_ENDED);
	evt.SetInt(0);
	wxQueueEvent(m_handler, evt.Clone());

	return 0;
}
