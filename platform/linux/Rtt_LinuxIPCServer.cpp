#include <wx/wx.h>
#include "Rtt_LinuxIPCConnectionBase.h"
#include "Rtt_LinuxIPCConnection.h"
#include "Rtt_LinuxIPCServer.h"


Rtt_LinuxIPCServer::Rtt_LinuxIPCServer()
{
    m_connection = NULL;
}

Rtt_LinuxIPCServer::~Rtt_LinuxIPCServer()
{
    Disconnect();
}

wxConnectionBase *Rtt_LinuxIPCServer::OnAcceptConnection(const wxString& topic)
{
	
    //wxLogMessage("OnAcceptConnection(\"%s\")", topic);

    if ( topic == IPC_TOPIC )
    {
        m_connection = new Rtt_LinuxIPCConnection();
    }
    else // unknown topic
    {
        //wxLogMessage("Unknown topic");
        return NULL;
    }

    //wxLogMessage("Connection accepted");
	return m_connection;
}

void Rtt_LinuxIPCServer::Disconnect()
{
    if ( m_connection )
    {
        m_connection->Disconnect();
        wxDELETE(m_connection);
        //wxLogMessage("Disconnected client");
    }
}
