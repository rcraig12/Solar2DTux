#include "Rtt_LinuxConsoleApp.h"

bool Rtt_LinuxConsoleApp::OnInit()
{
	wxInitAllImageHandlers();
	Solar2DTuxConsole = new Rtt_LinuxConsole(NULL, wxID_ANY, wxEmptyString);
	SetTopWindow(Solar2DTuxConsole);
	Solar2DTuxConsole->Show();

	return true;
<<<<<<< HEAD
=======
}

void Rtt_LinuxConsoleApp::ClearLog()
{
	Solar2DTuxConsole->ClearLog();
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
}

void Rtt_LinuxConsoleApp::UpdateLog(wxString message)
{
<<<<<<< HEAD

	Solar2DTuxConsole->UpdateLog(message);

=======
	Solar2DTuxConsole->UpdateLog(message);
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
}

void Rtt_LinuxConsoleApp::UpdateLog(wxString message, int messageType)
{
<<<<<<< HEAD

	if (color == 0 )
	{

		Solar2DTuxConsole->UpdateLog(message);

	}

	if (color == 1 )
	{

		Solar2DTuxConsole->UpdateLogWarning(message);

	}

	if (color == 2 )
	{

		Solar2DTuxConsole->UpdateLogError(message);

	}

=======
	switch(messageType)
	{
		case MessageType::Warning:
			Solar2DTuxConsole->UpdateLogWarning(message);
			break;

		case MessageType::Error:
			Solar2DTuxConsole->UpdateLogError(message);
			break;

		default:
			Solar2DTuxConsole->UpdateLog(message);
			break;
	}
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
}

IMPLEMENT_APP(Rtt_LinuxConsoleApp);
