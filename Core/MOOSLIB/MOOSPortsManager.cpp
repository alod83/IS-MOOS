#include "MOOSPortsManager.h"
#include <MOOSGenLib/MOOSGenLib.h>
#include <iostream>

using namespace std;

CMOOSPortsManager::CMOOSPortsManager()
{
	num_ports = 0;
	min_port = 0;
}

CMOOSPortsManager::CMOOSPortsManager(int num_ports, int min_port){
		this->num_ports = num_ports;
		this->min_port = min_port;
		ports = new bool[num_ports];
		pthread_mutex_init(&mutex, 0);
		pthread_cond_init(&condition, 0);
		free_ports = num_ports;
		for(int i=0; i < this->num_ports; i++)
			ports[i] = true;
}

int CMOOSPortsManager::request(){
	int port = -1;
	//sem_wait(&condition);
	pthread_mutex_lock(&mutex);
	//check condition
	if(free_ports == 0)
	{
		MOOSTrace("%sCMOOSPortsManager - Waiting: there are no free ports%s\n",red,none);
		pthread_cond_wait(&condition,&mutex);
	}
	//update resource
	free_ports--;
	for(int i = 0; i < num_ports; i++)
		if(ports[i] == true){
			port = min_port + i + 1;
			ports[i] = false;
			break;
		}
	pthread_mutex_unlock(&mutex);
	return port;
}

void CMOOSPortsManager::release(int port){
	if(port < min_port || port > (min_port + num_ports))return;
	pthread_mutex_lock(&mutex);
	free_ports++;
	ports[port-min_port-1] = true;
	
	MOOSTrace("%sCMOOSPortsManager - Freed port '%d'%s\n",green,port,none);
	pthread_cond_signal(&condition);
	pthread_mutex_unlock(&mutex);
	
	
}

CMOOSPortsManager::~CMOOSPortsManager(){
	delete ports;
}
