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
//   This file is part of a  MOOS Core Component. 
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
//////////////////////////    END_GPL    //////////////////////////////////

/*
 *  XPCUdpSocket.cpp
 *  MOOS
 *
 *  Created by pnewman on 13/05/2009.
 *  Copyright 2009 Oxford University. All rights reserved.
 *
 */

#include "XPCUdpSocket.h"
#include <MOOSGenLib/MOOSGenLib.h>
#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <MOOSGenLib/MOOSThread.h>

using namespace std;


#define BUFLEN 1024


XPCUdpSocket::XPCUdpSocket(long int iPort,int numPorts, int minPort, int iReadTimeout): XPCSocket("udp", iPort)
{
	m_PortsManager = new CMOOSPortsManager(numPorts, minPort);
	m_iReadTimeout = iReadTimeout;  
}    

XPCUdpSocket::XPCUdpSocket(long int iPort, int iReadTimeout,short int iUDPWaitTime): XPCSocket("udp", 0)
{
	//invoked by a client
	m_otherAddress.sin_family = AF_INET;
	m_otherAddress.sin_port = htons(iPort);
	m_iReadTimeout = iReadTimeout;
	m_iUDPWaitTime = iUDPWaitTime;
}

XPCUdpSocket::XPCUdpSocket(long int _iPort, struct sockaddr_in* _cl_addr,CMOOSPortsManager* p) : XPCSocket("udp", _iPort){

	m_PortsManager = p;
 	m_otherAddress.sin_family = _cl_addr->sin_family;
	m_otherAddress.sin_port = _cl_addr->sin_port;
	m_otherAddress.sin_addr.s_addr = _cl_addr->sin_addr.s_addr;
	vSetReuseAddr(1);
	vBindSocket();

}

XPCUdpSocket::~XPCUdpSocket()
{
}

// Constructor.  Called when a client connects and a new file descriptor has
// be created as a result.	
XPCUdpSocket::XPCUdpSocket(short int _iSocketFd, int numPorts, int minPort) : XPCSocket(_iSocketFd) { 
	m_PortsManager = new CMOOSPortsManager(numPorts, minPort);
}

bool XPCUdpSocket::GetAddress(long int nPort,const std::string & sHost,sockaddr_in & Address)
{

    std::map< std::pair< long int , std::string  >, sockaddr_in >::iterator q;
    
    std::pair< long int , std::string  > PP(nPort,sHost);
    
    q = m_KnownAdresses.find(PP);
    
    if(q!=m_KnownAdresses.end())
    {
        Address = q->second;
        return true;
    }
    else
    {
        
	Address.sin_family = AF_INET;
    	Address.sin_port = htons(nPort);
        
        hostType HostType;
        if(sHost.find_first_not_of("0123456789. ")!=std::string::npos)
        {
            HostType = NAME;
            XPCGetHostInfo getHostInfo(sHost.c_str(), HostType);
            
            // Store the IP address and socket port number
            Address.sin_addr.s_addr =inet_addr(getHostInfo.sGetHostAddress());
            
        }
        else
        {
            HostType = ADDRESS;
            // Store the IP address and socket port number
            Address.sin_addr.s_addr =inet_addr(sHost.c_str());
        }        
        
        //save it
        m_KnownAdresses[PP] = Address;
        
        return true;
    }
    
}

int XPCUdpSocket::iBroadCastMessage(void *_vMessage, int _iMessageSize,long int nPort)
{
	return iSendMessageTo(_vMessage, _iMessageSize,nPort,"255.255.255.255");
}

// Sends a message to a connected host. The number of bytes sent is returned
int XPCUdpSocket::iSendMessageTo(void *_vMessage, int _iMessageSize,long int nPort,const std::string & sHost)
{
    
    sockaddr_in  Address;
    
    if(!GetAddress(nPort,sHost,Address))
    {
        throw XPCException("::iSendMessageTo failed to get destination address\n");
    }
    
    int iNumBytes=sendto(iSocket, (const char*)_vMessage, _iMessageSize,0,
             (struct sockaddr *) &Address, sizeof(Address) );
    
    
    // Sends the message to the connected host
    if (iNumBytes == -1)
    {
        char sMsg[512];        
        sprintf(sMsg, "Error sending socket message: %s", sGetError());
        throw XPCException(sMsg);
        return 0;
    }
    return iNumBytes;
    
}

int XPCUdpSocket::iSendMessage(void *_vMessage, int _iMessageSize)
{
	int iNumBytes;  // Stores the number of bytes sent
    	socklen_t slen=sizeof(m_otherAddress);

	if ((iNumBytes = sendto(iSocket, (char *)_vMessage, _iMessageSize,0,(struct sockaddr *) &m_otherAddress, slen)) == -1)
	{
		char sMsg[512];
		
		sprintf(sMsg, "Error sending socket message: %s", sGetError());
		XPCException socketExcept(sMsg);
		throw socketExcept;
		return 0;
	}
		
	return iNumBytes;
}

// Receives a message 
int XPCUdpSocket::iRecieveMessage(void *_vMessage, int _iMessageSize, int _iOption)
{
	int iNumBytes = 0;      // The number of bytes received
    
    	socklen_t slen=sizeof(m_otherAddress); 
	iNumBytes = recvfrom(iSocket, (char *)_vMessage,_iMessageSize,0, (struct sockaddr *) &m_otherAddress, &slen);

        if (iNumBytes == -1)
        {
            	char sMsg[512];
            
            	sprintf(sMsg, "Error receiving on socket: %s", sGetError());
		XPCException socketExcept(sMsg);
		throw socketExcept;
		return iNumBytes;
        }
        
	return iNumBytes;
}

// Binds the socket to an address and port number
void XPCUdpSocket::vBindSocket()
{
    // Bind the socket to the given address and port number
    if (bind(iSocket, (struct sockaddr *)&m_myAddress,sizeof(m_myAddress)) == -1)
    {
        char sMsg[512];
        sprintf(sMsg, "Error binding to socket: %s", sGetError());
        XPCException socketExcept(sMsg);
        throw socketExcept;
        return;
    }
}

    // Accepts a connecting client.  The address of the connected client is stored in the parameter
XPCSocket *XPCUdpSocket::Accept(char *_sHost)
{

	char buf[BUFLEN]; 
	
	if(iRecieveMessage(buf, BUFLEN) == 0)
	{
		char sMsg[512];
        
		sprintf(sMsg, "Unable to read CONNECTION_REQUEST.\0");
		XPCException socketExcept(sMsg);
		throw socketExcept;
		return NULL;
	}
	MOOSTrace("\n%sUDP ACCEPT\n", brown);
	MOOSTrace("Begin udp handshake for client on port '%d'\n", ntohs(m_otherAddress.sin_port));

	if(strncmp(buf, "CONNECTION_REQUEST",18) != 0){
		char sMsg[512];
        
		sprintf(sMsg, "Error in receiving CONNECTION_REQUEST.\0");
		XPCException socketExcept(sMsg);
		throw socketExcept;
		return NULL;
	}
	MOOSTrace("1. Received from client a CONNECTION_REQUEST%s\n",none);
	
	int port = m_PortsManager->request();
	
	bzero(buf, BUFLEN);
	sprintf(buf, "CONNECTION_REPLY:%d",port);
	if(iSendMessage(buf, BUFLEN) == 0)
	{
		char sMsg[512];
		sprintf(sMsg, "Unable to send CONNECTION_REPLY.\0");
		XPCException socketExcept(sMsg);
		throw socketExcept;
		return NULL;
	}
	
	MOOSTrace("%s2. Sent to client CONNECTION_REPLY containing the assigned port '%d'\n",brown, port);
	MOOSTrace("3. Waiting the the CONNECTION_CONFIRMATION from the client%s\n",none);
	
	bzero(buf, BUFLEN);
	if(iReadMessageWithTimeOut(buf, BUFLEN, m_iReadTimeout) == 0)
	{
		char sMsg[512];
		sprintf(sMsg, "Unable to read CONNECTION_CONFIRMATION.\0");
		XPCException socketExcept(sMsg);
		throw socketExcept;
		return NULL;
	}

	MOOSTrace("%sDone udp handshake%s\n",brown, none);
	

	// If the host name is requested
    	if (_sHost != NULL)
    	{
		// Get the ascii representation of the address
		char *sAddress = inet_ntoa((struct in_addr)m_otherAddress.sin_addr);
		
		// Get the host name given the address
		try
		{
		XPCGetHostInfo getHostInfo(sAddress, ADDRESS);
		// Store the host name
		strcpy(_sHost, getHostInfo.sGetHostName());
		}
		catch(XPCException e)
		{
		strcpy(_sHost, sAddress);
		printf("INFO: %s using numeric address %s\n",e.sGetException(),_sHost);
		}
		
    	}
        // Stores the connected clients info
	// Create and return the new XPCUdpSocket object
	XPCUdpSocket *newSocket = new XPCUdpSocket(port,&m_otherAddress,m_PortsManager);
	//m_AcceptLock.UnLock();
	return newSocket;
}

// Listens to connecting clients
void XPCUdpSocket::vListen(int _iNumPorts){}

// Connects to a client specified by a supplied host name
void XPCUdpSocket::vConnect(const char *_sHost)
{
	socklen_t slen=sizeof(m_otherAddress);

	// Resolve the IP address of the given host name
	std::string sHost(_sHost);
	hostType HostType;
	if(sHost.find_first_not_of("0123456789. ")!=std::string::npos)
	{
		HostType = NAME;
		XPCGetHostInfo getHostInfo(_sHost, HostType);
		
		// Store the IP address and socket port number
		m_otherAddress.sin_addr.s_addr =inet_addr(getHostInfo.sGetHostAddress());
		
	}
	else
	{
		HostType = ADDRESS;
		// Store the IP address and socket port number
		m_otherAddress.sin_addr.s_addr =inet_addr(_sHost);
	}        

	MOOSTrace("\n%sUDP CONNECT\n", brown);
	MOOSTrace("Begin udp handshake for client on port '%d'%s\n", ntohs(m_otherAddress.sin_port),none);
	char buf[BUFLEN];
	sprintf(buf, "CONNECTION_REQUEST");
	if(iSendMessage(buf,BUFLEN) == 0)
	{
 		char sMsg[512];
 		sprintf(sMsg, "Unable to send a CONNECTION_REQUEST.");
 		XPCException socketExcept(sMsg);
 		throw socketExcept;
 		return;
	}
 	MOOSTrace("%s1. Sent CONNECTION_REQUEST\n",brown);
 
	bzero(buf,BUFLEN);
 	MOOSTrace("2. Waiting CONNECTION_REPLY%s\n",none);
	if(iReadMessageWithTimeOut(buf, BUFLEN, m_iReadTimeout) == 0)
	{
		char sMsg[512];
		sprintf(sMsg, "Unable to read CONNECTION_REPLAY.\0");
		XPCException socketExcept(sMsg);
		throw socketExcept;
		return;
	}
	char* reply;
	reply = strtok (buf,":");
	if(strncmp(reply, "CONNECTION_REPLY",16) != 0){
		char sMsg[512];
		sprintf(sMsg, "Error: not received a CONNECTION_REPLY.");
		XPCException socketExcept(sMsg);
		throw socketExcept;
		return;
	}
	int port = atoi(strtok (NULL, ":"));
	//client invia alla vecchia porta
		
	MOOSTrace("%s3. Got CONNECTION_REPLY. Assigned port is '%d'\n",brown,port);
	
	MOOSTrace("4. Sending CONNECTION_CONFIRMATION%s\n",none);	
	bzero(buf, BUFLEN);
	sprintf(buf, "CONNECTION_CONFIRMATION");
	if(iSendMessage(buf,BUFLEN) == 0)
	{
 		char sMsg[512];
 		sprintf(sMsg, "Unable to send a CONNECTION_CONFIRMATION.");
 		XPCException socketExcept(sMsg);
 		throw socketExcept;
 		return;
	}
	m_otherAddress.sin_port = htons(port);
	MOOSTrace("%sDone udp handshake%s\n",brown,none);
	MOOSPause(m_iUDPWaitTime*1000);
	
}

    // allows a read with a timeout to prevent from blocking indefinitely
int XPCUdpSocket::iReadMessageWithTimeOut(void *_vMessage, int _iMessageSize, double dfTimeOut,int _iOption)
{
    int iNumBytes = 0;
    
    struct timeval timeout;        // The timeout value for the select system call
    fd_set fdset;                // Set of "watched" file descriptors
    
    
    // The socket file descriptor set is cleared and the socket file 
    // descriptor contained within tcpSocket is added to the file
    // descriptor set.
    FD_ZERO(&fdset);
    
    FD_SET((unsigned int)iGetSocketFd(), &fdset);
    
    
    // The select system call is set to timeout after 1 seconds with no data existing
    // on the socket. This has to be here, within the loop as Linux actually writes over
    // the timeout structure on completion of select (now that was a hard bug to find)
    
    if(dfTimeOut<1)
    {
        dfTimeOut=1.0;
    }
    
    timeout.tv_sec    = (int)dfTimeOut;
    timeout.tv_usec = 0;
    
    
    // A select is setup to return when data is available on the socket
    // for reading.  If data is not available after timeout seconds, select
    // returns with a value of 0.  If data is available on the socket,
    // the select returns and data can be retrieved off the socket.
    int iSelectRet = select(iGetSocketFd() + 1,
        &fdset,
        NULL,
        NULL,
        &timeout);
    
    // If select returns a -1, then it failed and the thread exits.
    switch(iSelectRet)
    {
    case -1:
        //                Trace("Select failed ");
	
        iNumBytes=-1;
        break;
        
    case 0:
        //timeout...nothing to read
	iNumBytes = 0;
        break;
        
    default:
        
        if (FD_ISSET(iGetSocketFd(), &fdset) != 0)
        {
            //something to do read:
            return iRecieveMessage(_vMessage,_iMessageSize,_iOption);
        }
        break;
    }
    
    //zero socket set..
    FD_ZERO(&fdset);
    
    return iNumBytes;
   
}
void XPCUdpSocket::vCloseSocket()
{
 	#ifdef    WINDOWS_NT
            closesocket(iSocket);
        #else
            close(iSocket);
        #endif
	printf("close socket\n");
	if(m_PortsManager)
		m_PortsManager->release(ntohs(m_myAddress.sin_port));
}

