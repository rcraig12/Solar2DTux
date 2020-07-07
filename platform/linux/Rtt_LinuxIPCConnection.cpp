#include "Rtt_LinuxIPCConnection.h"

bool Rtt_LinuxIPCConnection::OnExecute(const wxString& topic, const void *data, size_t size, wxIPCFormat format)
{
    wxGetApp().UpdateLog( "This is the execute function..... \n" , 0);
    return true;
}

bool Rtt_LinuxIPCConnection::OnPoke(const wxString& topic, const wxString& item, const void *data, size_t size, wxIPCFormat format)
{
	string test(static_cast<const char *>(data), size);
	wxString msg;
	msg.append(test.c_str());
	msg.append("test\n");
	
    wxGetApp().UpdateLog( msg.c_str() , 1 );
    return wxConnection::OnPoke(topic, item, data, size, format);
}

const void *Rtt_LinuxIPCConnection::OnRequest(const wxString& topic, const wxString& item, size_t *size, wxIPCFormat format)
{
	//wxString s;
    //m_requestData = s.mb_str();
    //const void * const data = m_requestData;
	wxGetApp().UpdateLog( "This is the request function..... \n" , 2);
   // return data;
}

bool Rtt_LinuxIPCConnection::OnStartAdvise(const wxString& topic, const wxString& item)
{
    //wxLogMessage("OnStartAdvise(\"%s\",\"%s\")", topic, item);
    //wxLogMessage("Returning true");
    m_sAdvise = item;
    Start(3000); // schedule our Notify() to be called in 3 seconds
    return true;
}

bool Rtt_LinuxIPCConnection::OnStopAdvise(const wxString& topic, const wxString& item)
{
    //wxLogMessage("OnStopAdvise(\"%s\",\"%s\")", topic, item);
    //wxLogMessage("Returning true");
    m_sAdvise.clear();
    Stop();
    return true;
}

void Rtt_LinuxIPCConnection::Notify()
{
    if (!m_sAdvise.empty())
    {
        wxString s = wxDateTime::Now().Format();
        Advise(m_sAdvise, s);
        s = wxDateTime::Now().FormatTime() + " "
                + wxDateTime::Now().FormatDate();
 
       Advise(m_sAdvise, s.mb_str(), s.length() + 1);

#if wxUSE_DDE_FOR_IPC
        wxLogMessage("DDE Advise type argument cannot be wxIPC_PRIVATE. "
                     "The client will receive it as wxIPC_TEXT, "
                     "and receive the correct no of bytes, "
                     "but not print a correct log entry.");
#endif // DDE

        char bytes[3];
        bytes[0] = '1'; bytes[1] = '2'; bytes[2] = '3';
        Advise(m_sAdvise, bytes, 3, wxIPC_PRIVATE);
        // this works, but the log treats it as a string now
//        m_connection->Advise(m_connection->m_sAdvise, bytes, 3, wxIPC_TEXT );
    }
}

bool Rtt_LinuxIPCConnection::DoAdvise(const wxString& item, const void *data, size_t size, wxIPCFormat format)
{
    Log("Advise", "", item, data, size, format);
	
    return wxConnection::DoAdvise(item, data, size, format);
}

bool Rtt_LinuxIPCConnection::OnDisconnect()
{
    //wxLogMessage("OnDisconnect()");
    return true;
}

