#ifndef __FILEHASHTHREAD_H_INCLUDED__
#define __FILEHASHTHREAD_H_INCLUDED__

#include <wx/wx.h>

#include "checksums.h"

wxDECLARE_EVENT(wxEVT_THREAD_WORKING, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_THREAD_ENDED, wxThreadEvent);

class FileHashThread : public wxThread
{
	public:
		FileHashThread(wxEvtHandler* handler);
		virtual ~FileHashThread();
		bool SetFile2Hash(const wxString& filename);
		void SetHashingFilter(int mask);
		const wxString& GetLastError() { return m_sLastError; }
		wxString GetHexDigest(HashType type);
	protected:
		virtual ExitCode Entry();
	private:
		wxEvtHandler* m_handler;
		wxString m_sFileName, m_sLastError;
		CheckSums m_csHash;
};

#endif // __FILEHASHTHREAD_H_INCLUDED__
