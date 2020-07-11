#include "Rtt_LinuxIPCCient.h"

Rtt_LinuxIPCClient::Rtt_LinuxIPCClient()
{
	m_connection = NULL;
}

Rtt_LinuxIPCClient::~Rtt_LinuxIPCClient()
{
    Disconnect();
}

bool Rtt_LinuxIPCClient::Connect( const wxString& sHost, const wxString& sService, const wxString& sTopic )
{
	// suppress the log messages from MakeConnection()
    wxLogNull nolog;

    m_connection = (Rtt_LinuxIPCClientConnection*)MakeConnection(sHost, sService, sTopic);
    return m_connection    != NULL;
}

wxConnectionBase *Rtt_LinuxIPCClient::OnMakeConnection()
{
    return new Rtt_LinuxIPCClientConnection();
}

void Rtt_LinuxIPCClient::Disconnect()
{
    if ( m_connection )
    {
        m_connection->Disconnect();
        wxDELETE(m_connection);
        //wxLogMessage("Disconnected client");
    }
}

