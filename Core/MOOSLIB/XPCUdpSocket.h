///////////////////////////////////////////////////////////////////////////
//
//   MOOS - Mission Oriented Operating Suite 
//  
//   A suit of Applications and Libraries for Mobile Robotics Research 
//   Copyright (C) 2001-2005 Massachusetts Institute of Technology and 
//   Oxford University. 
//    
//   This software was written by Paul Newman at MIT 2001-2002 and Oxford 
//   University 2003-2005. email: pnewman@robots.ox.ac.uk. 
//      
//   This file is part of a  MOOS CORE Component. 
//        
//   This program is free software; you can redistribute it and/or 
//   modify it under the terms of the GNU General Public License as 
//   published by the Free Software Foundation; either version 2 of the 
//   License, or (at your option) any later version. 
//          
//   This program is distributed in the hope that it will be useful, 
//   but WITHOUT ANY WARRANTY; without even the implied warranty of 
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
//   General Public License for more details. 
//            
//   You should have received a copy of the GNU General Public License 
//   along with this program; if not, write to the Free Software 
//   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 
//   02111-1307, USA. 
//
//   The XPC classes in MOOS are modified versions of the source provided 
//   in "Making UNIX and Windows NT Talk" by Mark Nadelson and Thomas Haga 
//
//////////////////////////    END_GPL    //////////////////////////////////


#ifndef _XPCUdpSocket
#define _XPCUdpSocket

#include "XPCSocket.h"
#include "MOOSPortsManager.h"
#include <map>
#include <sys/time.h>



class XPCUdpSocket : public XPCSocket
    {
    public:
        
        // Constructor.  Used to create a new udp socket  - it will receive on _iPort
	XPCUdpSocket(long int _iPort, int iReadTimeout = 5, short int iUDPWaitTime = 5);
	XPCUdpSocket(long int _iPort,long int iServerPort) ;
	XPCUdpSocket(long int _iPort, int numPorts, int minPort,int iReadTimeout = 5) ;
	XPCUdpSocket(long int _iPort, struct sockaddr_in* _cl_addr,CMOOSPortsManager* p);
	XPCUdpSocket(short int _iSocketFd, int numPorts, int minPort);
	~XPCUdpSocket();
        
        // Sends a message to a specified host on a specified port. The number of bytes sent is returned
        int iSendMessageTo(void *_vMessage, int _iMessageSize,long int nPort,const std::string & sHost);
//         //send a telegram to all local network nodes on specified ports
         int iBroadCastMessage(void *_vMessage, int _iMessageSize,long int nPort);

         bool GetAddress(long int nPort,const std::string & sHost,sockaddr_in & Address);
// 
         std::map< std::pair< long int , std::string >, sockaddr_in >   m_KnownAdresses ;
     // Sends a message to a connected host. The number of bytes sent is returned
    virtual int iSendMessage(void *_vMessage, int _iMessageSize);

    // Receives a message 
    virtual int iRecieveMessage(void *_vMessage, int _iMessageSize, int _iOption = 0);

    // Binds the socket to an address and port number
    virtual void vBindSocket();

    // Accepts a connecting client.  The address of the connected client is stored in the parameter
    virtual XPCSocket *Accept(char *_sHost = NULL);

    // Listens to connecting clients
    virtual void vListen(int _iNumPorts = 5);

    // Connects to a client specified by a supplied host name
    virtual void vConnect(const char *_sHost);

    // allows a read with a timeout to prevent from blocking indefinitely
    virtual int iReadMessageWithTimeOut(void *_vMessage, int _iMessageSize, double dfTimeOut,int _iOption=0);
   virtual void vCloseSocket();
   
private:
    CMOOSPortsManager* m_PortsManager;
    struct sockaddr_in m_otherAddress;
    int m_iReadTimeout;
    short int m_iUDPWaitTime;
    
};

#endif
