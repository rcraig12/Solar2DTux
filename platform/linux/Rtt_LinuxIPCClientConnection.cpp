#include "Rtt_LinuxIPCClientConnection.h"

bool Rtt_LinuxIPCClientConnection::OnAdvise(const wxString& topic, const wxString& item, const void *data,
    size_t size, wxIPCFormat format)
{
    Log("OnAdvise", topic, item, data, size, format);
    return true;
}

bool Rtt_LinuxIPCClientConnection::OnDisconnect()
{
    wxLogMessage("OnDisconnect()");
    //wxGetApp().GetFrame()->Disconnect();
    return true;
}

bool Rtt_LinuxIPCClientConnection::DoExecute(const void *data, size_t size, wxIPCFormat format)
{
    Log("Execute", wxEmptyString, wxEmptyString, data, size, format);
    bool retval = wxConnection::DoExecute(data, size, format);
    if (!retval)
    {
        wxLogMessage("Execute failed!");
    }
    return retval;
}

const void *Rtt_LinuxIPCClientConnection::Request(const wxString& item, size_t *size, wxIPCFormat format)
{
    const void *data =  wxConnection::Request(item, size, format);
    Log("Request", wxEmptyString, item, data, size ? *size : wxNO_LEN, format);
    return data;
}

bool Rtt_LinuxIPCClientConnection::DoPoke(const wxString& item, const void *data, size_t size, wxIPCFormat format)
{
    Log("Poke", wxEmptyString, item, data, size, format);
    return wxConnection::DoPoke(item, data, size, format);
}