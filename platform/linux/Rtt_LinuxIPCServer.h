#ifndef LINUXIPCSERVER_H
#define LINUXIPCSERVER_H

#include <wx/wx.h>
#include <wx/ipc.h>

// the default service name
//#define IPC_SERVICE "4242"
#define IPC_SERVICE "/tmp/solar2d_logconsole"

// the hostname
#define IPC_HOST "localhost"

// the IPC topic
#define IPC_TOPIC "IPC Solar2DTux"

// the name of the item we're being advised about
#define IPC_ADVISE_NAME "Item"

class Rtt_LinuxConsole;

class Rtt_LinuxIPCServer : public wxServer
{
public:
	Rtt_LinuxIPCServer();
    virtual ~Rtt_LinuxIPCServer();
    void Disconnect();
    bool IsConnected() { return m_connection != NULL; }
    virtual wxConnectionBase *OnAcceptConnection(const wxString& topic) wxOVERRIDE;
protected:
    wxConnection *m_connection;
};

#endif //LINUXIPCSERVER_H