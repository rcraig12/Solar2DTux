#ifndef LINUXCONSOLE_H
#define LINUXCONSOLE_H

#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/icon.h>
#include "Rtt_LinuxIPCServer.h"
#include "Rtt_LinuxIPCServerConnection.h"

using namespace std;

#define TIMER_ID 1000

class Rtt_LinuxConsole: public wxFrame
{
public:
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
	Rtt_LinuxConsole(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE);
private:
=======
	Rtt_LinuxConsole(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE);
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc

private:
	static const int intTimerInterval = 250;
	void SetProperties();
	void DoLayout();

protected:
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645

	wxStatusBar* statusbar;
	wxBitmapButton* bitmapBtnSave;
	wxBitmapButton* bitmapBtnCopy;
	wxBitmapButton* bitmapBtnErase;
	wxTextCtrl* txtFind;
	wxBitmapButton* bitmapBtnFindLeft;
	wxBitmapButton* bitmapBtnFindRight;
	wxBitmapButton* bitmapBtnMatchCase;
	wxBitmapButton* bitmapBtnLoopingSearch;
	wxBitmapButton* bitmapBtnMenu;
	wxPanel* panelToolBar;
	wxTextCtrl* txtLog;
	wxTimer* timer;
	Rtt_LinuxIPCServer* linuxIPCServer;
=======
	wxStatusBar *statusbar;
	wxBitmapButton *bitmapBtnSave;
	wxBitmapButton *bitmapBtnCopy;
	wxBitmapButton *bitmapBtnErase;
	wxTextCtrl *txtFind;
	wxBitmapButton *bitmapBtnFindLeft;
	wxBitmapButton *bitmapBtnFindRight;
	wxBitmapButton *bitmapBtnMatchCase;
	wxBitmapButton *bitmapBtnLoopingSearch;
	wxBitmapButton *bitmapBtnMenu;
	wxPanel *panelToolBar;
	wxTextCtrl *txtLog;
	wxTimer *timer;
	Rtt_LinuxIPCServer *linuxIPCServer;
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc

	DECLARE_EVENT_TABLE();

public:
	void OnBtnSaveClick(wxCommandEvent &event);
	void OnBtnCopyClick(wxCommandEvent &event);
	void OnBtnEraseClick(wxCommandEvent &event);
	void OnBtnFindLeftClick(wxCommandEvent &event);
	void OnBtnFindRightClick(wxCommandEvent &event);
	void OnBtnMatchCaseClick(wxCommandEvent &event);
	void OnBtnLoopingSearchClick(wxCommandEvent &event);
	void OnProgressTimer(wxTimerEvent &event);
<<<<<<< HEAD
	void UpdateLog( wxString message);
	void UpdateLogWarning( wxString message);
	void UpdateLogError( wxString message);

<<<<<<< HEAD
=======
=======
	void ClearLog();
	void UpdateLog(wxString message);
	void UpdateLogWarning(wxString message);
	void UpdateLogError(wxString message);
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
};

#endif // LINUXCONSOLE_H
