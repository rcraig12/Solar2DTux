#ifndef LINUXIPCCLIENTCONNECTION_H
#define LINUXIPCCLIENTCONNECTION_H

#include <wx/wx.h>
#include <string.h>
#include "Rtt_LinuxIPCConnectionBase.h"

class Rtt_LinuxIPCClientConnection: public Rtt_LinuxIPCConnectionBase, public wxTimer
{
public:
    virtual bool DoExecute(const void *data, size_t size, wxIPCFormat format) wxOVERRIDE;
    virtual const void *Request(const wxString& item, size_t *size = NULL, wxIPCFormat format = wxIPC_TEXT) wxOVERRIDE;
    virtual bool DoPoke(const wxString& item, const void* data, size_t size, wxIPCFormat format) wxOVERRIDE;
    virtual bool OnAdvise(const wxString& topic, const wxString& item, const void *data, size_t size, wxIPCFormat format) wxOVERRIDE;
    virtual bool OnDisconnect() wxOVERRIDE;
};

#endif //LINUXIPCCLIENTCONNECTION_H