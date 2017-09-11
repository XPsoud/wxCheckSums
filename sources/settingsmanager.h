#ifndef __SETTINGSMANAGER_H_INCLUDED__
#define __SETTINGSMANAGER_H_INCLUDED__

#include <wx/wx.h>

extern const wxChar* szStdXmlFileHeader;
extern const int iStdXmlHeaderSize;
#include "checksums.h"

class SettingsManager
{
	public:
		static SettingsManager& Get();
		bool ReadSettings();
		bool SaveSettings();
		// Accessors
		bool IsModified();
		wxString GetAppPath() { return m_sAppPath; }
		wxString GetSettingsPath() { return m_sSettingsPath; }
		// Datas and settings compression
		bool GetCompressSettings() { return m_bCompSettings; }
		void SetCompressSettings(bool value=true);
		bool GetCompressDatas() { return m_bCompDatas; }
		void SetCompressDatas(bool value=true);
		// Position of the main window at application startup
		int GetMainWndStartupPos() { return m_iStartPos; }
		void SetMainWndStartupPos(int value);
		void GetMainWndStartupPos(wxPoint& pos) { pos=m_ptStartPos; }
		const wxSize& GetMainWndStartupSize() { return m_szStartSize; }
		void SetLastWindowRect(const wxPoint& pos, const wxSize& size);
		// Multiple instances
		bool GetMultipleInstancesAllowed() { return (m_bSingleInstance==false); }
		void SetMultipleInstancesAllowed(bool value);
		// Prohibit translations and transaltions related stuff
		bool GetProhibitI18N() { return m_bProhibI18N; }
		void SetProhibitI18N(bool value);
		// Always display results with uppercase chars
		bool GetAlwaysUCase() { return m_bUCaseHashes; }
		void SetAlwaysUCase(bool value);
		// Checksums types enable/disable
		bool GetHashMethodEnabled(HashType type);
		bool SetHashMethodEnabled(HashType type, bool enable=true);
	protected:
	private:
		SettingsManager();
		virtual ~SettingsManager();
		void Initialize();
		const wxString StartupPos2String(int iValue);
		int StartupString2Pos(const wxString& sValue);
		// Unique instance of the singleton
		static SettingsManager m_instance;
		// Misc vars
		bool m_bInitialized, m_bModified;
		wxString m_sAppPath, m_sSettingsPath;
		static const wxChar* m_szSettingsFName;
		// Settings vars
		bool m_bCompSettings, m_bCompDatas;
		int m_iStartPos;
		wxPoint m_ptStartPos;
		wxSize m_szStartSize;
		bool m_bSingleInstance, m_bProhibI18N;
		bool m_bUCaseHashes, m_bHashEnabled[HT_COUNT];
};

#endif // __SETTINGSMANAGER_H_INCLUDED__
