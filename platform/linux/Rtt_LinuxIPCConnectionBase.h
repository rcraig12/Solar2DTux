#ifndef LINUXIPCCONNECTIONBASE_H
#define LINUXIPCCONNECTIONBASE_H

#include <wx/wx.h>
#include <wx/ipc.h>

class Rtt_LinuxIPCConnectionBase : public wxConnection
{

protected:
	void Log(const wxString& command, const wxString& topic, const wxString& item, const void *data, size_t size, wxIPCFormat format);
};

#endif //LINUXIPCCONNECTIONBASE_H
