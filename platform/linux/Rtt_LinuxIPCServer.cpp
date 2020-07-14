#include <wx/wx.h>
#include "Rtt_LinuxIPCConnectionBase.h"
#include "Rtt_LinuxIPCServerConnection.h"
#include "Rtt_LinuxIPCServer.h"

Rtt_LinuxIPCServer::Rtt_LinuxIPCServer()
{
<<<<<<< HEAD
	m_connection = NULL;
=======
<<<<<<< HEAD
	m_connection = NULL;
=======
	mConnection = NULL;
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
}

Rtt_LinuxIPCServer::~Rtt_LinuxIPCServer()
{
	Disconnect();
}

wxConnectionBase *Rtt_LinuxIPCServer::OnAcceptConnection(const wxString &topic)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645

	//wxLogMessage("OnAcceptConnection(\"%s\")", topic);

	if ( topic == IPC_TOPIC )
	{
		m_connection = new Rtt_LinuxIPCServerConnection;
<<<<<<< HEAD
=======
=======
	//wxLogMessage("OnAcceptConnection(\"%s\")", topic);
	if (topic == IPC_TOPIC)
	{
		mConnection = new Rtt_LinuxIPCServerConnection();
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
	}
	else // unknown topic
	{
		//wxLogMessage("Unknown topic");
		return NULL;
	}

	//wxLogMessage("Connection accepted");
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
	return m_connection;
=======
	return mConnection;
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
}

void Rtt_LinuxIPCServer::Disconnect()
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
	if ( m_connection )
	{
		m_connection->Disconnect();
		wxDELETE(m_connection);
<<<<<<< HEAD
=======
=======
	if (mConnection)
	{
		mConnection->Disconnect();
		wxDELETE(mConnection);
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
		//wxLogMessage("Disconnected client");
	}
}
