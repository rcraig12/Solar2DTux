#ifndef LINUXCONSOLEAPP_H
#define LINUXCONSOLEAPP_H

#include <wx/app.h>
#include "Rtt_LinuxConsole.h"

class Rtt_LinuxConsoleApp: public wxApp
{
public:
<<<<<<< HEAD
	bool OnInit();
	void UpdateLog( wxString message);
	void UpdateLog( wxString message, int colour);
	Rtt_LinuxConsole* Solar2DTuxConsole;
=======
	enum MessageType {Normal, Warning, Error};
	Rtt_LinuxConsole *Solar2DTuxConsole;
	bool OnInit();
	void ClearLog();
	void UpdateLog(wxString message);
	void UpdateLog(wxString message, int messageType);
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
};

DECLARE_APP(Rtt_LinuxConsoleApp);

#endif //LINUXCONSOLEAPP_H
