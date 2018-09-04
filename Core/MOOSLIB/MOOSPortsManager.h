#include <pthread.h>

#ifndef MOOSPORTS_MANAGER_H
#define MOOSPORTS_MANAGER_H

class CMOOSPortsManager{
	private:
		pthread_cond_t condition;
		pthread_mutex_t mutex;
		int num_ports;
		bool* ports;
		int min_port;
		int free_ports;
	public:
		/* Create a new PortsManager, managing num_ports starting from min_port*/
		CMOOSPortsManager(int num_ports, int min_port);
		CMOOSPortsManager();
		/* Request for a port. 
		   Return the number of allocated port. 
		   -1 if no port is allocated.
		   It is blocking if all the ports are busy.
		*/
		int request();
		/* Release the allocated port. */
		void release(int port);
		~CMOOSPortsManager();
};

#endif
