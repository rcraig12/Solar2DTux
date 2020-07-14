#include "Rtt_LinuxIPCServerConnection.h"

bool Rtt_LinuxIPCServerConnection::OnExecute(const wxString &topic, const void *data, size_t size, wxIPCFormat format)
{
	string logMsg(static_cast<const char *>(data), size);
	wxString msg;
	msg.append(logMsg.c_str());
<<<<<<< HEAD
	wxGetApp().UpdateLog( msg.c_str(), 0);
=======
<<<<<<< HEAD
	wxGetApp().UpdateLog( msg.c_str(), 0);
=======
	wxGetApp().UpdateLog(msg.c_str(), 0);
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
	return true;
}

bool Rtt_LinuxIPCServerConnection::OnPoke(const wxString &topic, const wxString &item, const void *data, size_t size, wxIPCFormat format)
{
	int logType = 0;
	string input(static_cast<const char *>(data), size);
	wxString msg;
<<<<<<< HEAD
	msg.append(test.c_str());
	//msg.append("\n");

	if ( item == "information" )
	{

		logType = 0;

	};

	if ( item == "warning" )
	{

		logType = 1;

	};

	if ( item == "error" )
	{

		logType = 2;

	};

	wxGetApp().UpdateLog( msg.c_str(), logType );
<<<<<<< HEAD
=======
=======
	msg.append(input.c_str());

	if (strcmp(item, "warning") == 0)
	{
		logType = 1;
	}
	else if (strcmp(item, "error") == 0)
	{
		logType = 2;
	}
	else if (strcmp(item, "clear") == 0)
	{
		wxGetApp().ClearLog();
		return true;
	}

	wxGetApp().UpdateLog(msg.c_str(), logType);
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
	return wxConnection::OnPoke(topic, item, data, size, format);
}

const void *Rtt_LinuxIPCServerConnection::OnRequest(const wxString &topic, const wxString &item, size_t *size, wxIPCFormat format)
{
<<<<<<< HEAD
	wxGetApp().UpdateLog( "This is the request function..... \n", 2);
=======
<<<<<<< HEAD
	wxGetApp().UpdateLog( "This is the request function..... \n", 2);
=======
	wxGetApp().UpdateLog("This is the request function..... \n", 2);
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
}

bool Rtt_LinuxIPCServerConnection::OnStartAdvise(const wxString &topic, const wxString &item)
{
	//wxLogMessage("OnStartAdvise(\"%s\",\"%s\")", topic, item);
	//wxLogMessage("Returning true");
	m_sAdvise = item;
	Start(3000); // schedule our Notify() to be called in 3 seconds
	return true;
}

bool Rtt_LinuxIPCServerConnection::OnStopAdvise(const wxString &topic, const wxString &item)
{
	//wxLogMessage("OnStopAdvise(\"%s\",\"%s\")", topic, item);
	//wxLogMessage("Returning true");
	m_sAdvise.clear();
	Stop();
	return true;
}

void Rtt_LinuxIPCServerConnection::Notify()
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
		bytes[0] = '1';
		bytes[1] = '2';
		bytes[2] = '3';
		Advise(m_sAdvise, bytes, 3, wxIPC_PRIVATE);
		// this works, but the log treats it as a string now
<<<<<<< HEAD
//        m_connection->Advise(m_connection->m_sAdvise, bytes, 3, wxIPC_TEXT );
=======
<<<<<<< HEAD
//        m_connection->Advise(m_connection->m_sAdvise, bytes, 3, wxIPC_TEXT );
=======
		// mConnection->Advise(mConnection->m_sAdvise, bytes, 3, wxIPC_TEXT );
>>>>>>> ef73d8d4403a6389b5954cb6516aad24ba107efc
>>>>>>> 94749fe2d8a72005408f3b967e515f4b843cb645
	}
}

bool Rtt_LinuxIPCServerConnection::DoAdvise(const wxString &item, const void *data, size_t size, wxIPCFormat format)
{
	Log("Advise", "", item, data, size, format);

	return wxConnection::DoAdvise(item, data, size, format);
}

bool Rtt_LinuxIPCServerConnection::OnDisconnect()
{
	//wxLogMessage("OnDisconnect()");
	return true;
}
