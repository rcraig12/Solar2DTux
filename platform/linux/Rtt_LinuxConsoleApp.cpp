#include "Rtt_LinuxConsoleApp.h"

//wxIMPLEMENT_APP(Rtt_LinuxConsoleApp);

bool Rtt_LinuxConsoleApp::OnInit()
{
    wxInitAllImageHandlers();
    Solar2DTuxConsole = new Rtt_LinuxConsole(NULL, wxID_ANY, wxEmptyString);
    SetTopWindow(Solar2DTuxConsole);
    Solar2DTuxConsole->Show();
	
    return true;
}

void Rtt_LinuxConsoleApp::UpdateLog( wxString message)
{
	
	Solar2DTuxConsole->UpdateLog(message);
	
}
void Rtt_LinuxConsoleApp::UpdateLog( wxString message, int color )
{
	
	if (color == 0 ){
		
		Solar2DTuxConsole->UpdateLog(message);
		
	}
	
	if (color == 1 ){
		
		Solar2DTuxConsole->UpdateLogWarning(message);
		
	}
	
	if (color == 2 ){
		
		Solar2DTuxConsole->UpdateLogError(message);
		
	}
	
}

IMPLEMENT_APP(Rtt_LinuxConsoleApp);