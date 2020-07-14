#ifndef LINUXIPCSERVER_H
#define LINUXIPCSERVER_H

#include <wx/ipc.h>

// the default service name
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
<<<<<<< HEAD
	bool IsConnected() { return m_connection != NULL; }
	virtual wxConnectionBase *OnAcceptConnection(const wxString& topic) wxOVERRIDE;
protected:
	wxConnection *m_connection;
=======
<<<<<<< HEAD
	bool IsConnected() { return m_connection != NULL; }
	virtual wxConnectionBase *OnAcceptConnection(const wxString& topic) wxOVERRIDE;
protected:
	wxConnection *m_connection;
=======
	bool IsConnected() { return mConnection != NULL; }
	virtual wxConnectionBase *OnAcceptConnection(const wxString &topic) wxOVERRIDE;
protected:
	wxConnection *mConnection;
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
};

#endif //LINUXIPCSERVER_H
