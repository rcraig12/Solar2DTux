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
<<<<<<< HEAD
=======
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
}

void Rtt_LinuxConsoleApp::ClearLog()
{
<<<<<<< HEAD

	Solar2DTuxConsole->UpdateLog(message);

=======
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
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
}

void Rtt_LinuxConsoleApp::UpdateLog(wxString message, int messageType)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645

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

<<<<<<< HEAD
	}

=======
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
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
}

IMPLEMENT_APP(Rtt_LinuxConsoleApp);
