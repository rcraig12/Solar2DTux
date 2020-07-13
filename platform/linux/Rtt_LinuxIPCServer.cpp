#include <wx/wx.h>
#include "Rtt_LinuxIPCConnectionBase.h"
#include "Rtt_LinuxIPCServerConnection.h"
#include "Rtt_LinuxIPCServer.h"

Rtt_LinuxIPCServer::Rtt_LinuxIPCServer()
{
	mConnection = NULL;
}

Rtt_LinuxIPCServer::~Rtt_LinuxIPCServer()
{
	Disconnect();
}

wxConnectionBase *Rtt_LinuxIPCServer::OnAcceptConnection(const wxString &topic)
{
	//wxLogMessage("OnAcceptConnection(\"%s\")", topic);
	if (topic == IPC_TOPIC)
	{
		mConnection = new Rtt_LinuxIPCServerConnection();
	}
	else // unknown topic
	{
		//wxLogMessage("Unknown topic");
		return NULL;
	}

	//wxLogMessage("Connection accepted");
	return mConnection;
}

void Rtt_LinuxIPCServer::Disconnect()
{
	if (mConnection)
	{
		mConnection->Disconnect();
		wxDELETE(mConnection);
		//wxLogMessage("Disconnected client");
	}
}
