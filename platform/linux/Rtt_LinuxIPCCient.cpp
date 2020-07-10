#include "Rtt_LinuxIPCCient.h"

Rtt_LinuxIPCClient::Rtt_LinuxIPCClient()
{
	
	bool isConnected = Connect( IPC_HOST, IPC_SERVICE, IPC_TOPIC);
	
}