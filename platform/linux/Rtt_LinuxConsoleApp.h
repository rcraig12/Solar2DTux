#ifndef LINUXCONSOLEAPP_H
#define LINUXCONSOLEAPP_H

#include <wx/app.h>
#include "Rtt_LinuxConsole.h"

class Rtt_LinuxConsoleApp: public wxApp
{
public:
	bool OnInit();
	void UpdateLog( wxString message);
	void UpdateLog( wxString message, int colour);
	Rtt_LinuxConsole* Solar2DTuxConsole;
};

DECLARE_APP(Rtt_LinuxConsoleApp);

#endif //LINUXCONSOLEAPP_H
