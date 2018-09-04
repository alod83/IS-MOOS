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
// MOOSCommObject.cpp: implementation of the CMOOSCommObject class.
//
//////////////////////////////////////////////////////////////////////
#ifdef _WIN32
    #pragma warning(disable : 4786)
    #pragma warning(disable : 4503)
#endif

#include <MOOSGenLib/MOOSGenLib.h>
#include "MOOSCommPkt.h"
#include "XPCSocket.h"
#include "MOOSCommObject.h"
#include "MOOSException.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMOOSCommObject::CMOOSCommObject()
{

}

CMOOSCommObject::~CMOOSCommObject()
{

}


bool CMOOSCommObject::ReadPkt(XPCSocket *pSocket, CMOOSCommPkt &PktRx, int nSecondsTimeout, unsigned char* key)
{
	#define CHUNK_READ 1024
    	unsigned char Buffer[CHUNK_READ];
    	unsigned char *pBuffer = Buffer;
	unsigned char* plaintext;
	int p_len;
	int pkt_len = 0;
	int nRxd;

	if(m_oSecurity.isAuthenticationEnabled())
	{
		if(key == 0){
			key = getSessionKey(pSocket);
		}else
			MOOSTrace("ReadPkt: using encryption key to distribute session key\n");
	}else
	{
		if(m_oSecurity.isEncryptionEnabled()){
			key = (unsigned char*)m_oSecurity.getEncryptionKey();
		}
	}
	if(m_oSecurity.isEncryptionEnabled())
	{
		if(nSecondsTimeout<0)
		{
			nRxd  = pSocket->iRecieveMessage((void*) &pkt_len,sizeof(int));
		}
		else
		{
			nRxd  = pSocket->iReadMessageWithTimeOut((void*) &pkt_len, sizeof(int),(double)nSecondsTimeout);
		}
		if(pkt_len == 0){
			MOOSTrace("CMOOSCommObject::ReadPkt() Bad pkt_len\n");
			throw CMOOSException("CMOOSCommObject::ReadPkt() Failed Rx - Bad Pkt_len");
	 
		}
		unsigned char myBuffer[pkt_len];

		if(nSecondsTimeout<0)
		{
			nRxd  = pSocket->iRecieveMessage(pBuffer,pkt_len);
		}
		else
		{
			nRxd  = pSocket->iReadMessageWithTimeOut(pBuffer, pkt_len,(double)nSecondsTimeout);
		}
		m_oSecurity.decryptPkt(plaintext, (const unsigned char*&)pBuffer, pkt_len,key);
		
		int block = sizeof(int);
		PktRx.Fill(plaintext,block);
		PktRx.Fill((unsigned char*)(plaintext + block), pkt_len-block);
		
	}
	else
	{  	int nData;
		if(nSecondsTimeout<0)
		{
			nRxd  = pSocket->iRecieveMessage((void*) &nData,sizeof(int));
		}
		else
		{
			nRxd  = pSocket->iReadMessageWithTimeOut((void*) &nData, sizeof(int),(double)nSecondsTimeout);
		}
		if(nData == 0){
			MOOSTrace("CMOOSCommObject::ReadPkt() Bad pkt_len\n");
			throw CMOOSException("CMOOSCommObject::ReadPkt() Failed Rx - Bad Pkt_len");
	 
		}  	
		PktRx.Fill((unsigned char*)&nData,sizeof(int));

		if(nSecondsTimeout<0)
		{
			nRxd  = pSocket->iRecieveMessage((void*) pBuffer,nData-sizeof(int));
		}
		else
		{
			nRxd  = pSocket->iReadMessageWithTimeOut((void*) pBuffer, nData-sizeof(int),(double)nSecondsTimeout);
		}
		if(nRxd == 0){
			MOOSTrace("CMOOSCommObject::ReadPkt()\n");
			throw CMOOSException("CMOOSCommObject::ReadPkt() Failed Rx");
	 
		}
		PktRx.Fill(pBuffer,nData-sizeof(int));
	    //now receive a message back..
// 	     int nRqd=0;
// 	     int nRxd;
// 	     while((nRqd=PktRx.GetBytesRequired())!=0)
// 	     {
// 	         nRxd = 0;
// 	         try
// 	         {
// 	         if(nRqd<CHUNK_READ)
// 	         {
// 	         //read in in chunks of 1k
// 	                 if(nSecondsTimeout<0)
// 	                 {
// 	                     nRxd  = pSocket->iRecieveMessage(pBuffer,nRqd);
// 	                 }
// 	                 else
// 	                 {
// 	                     nRxd  = pSocket->iReadMessageWithTimeOut(pBuffer,nRqd,(double)nSecondsTimeout);
// 	                 }
// 	         }
// 	         else
// 	         {
// 	         //read in in chunks of 1k
// 	                 if(nSecondsTimeout<0)
// 	                 {
// 	                     nRxd  = pSocket->iRecieveMessage(pBuffer,CHUNK_READ);
// 	                 }
// 	                 else
// 	                 {
// 	                     nRxd  = pSocket->iReadMessageWithTimeOut(pBuffer,CHUNK_READ,(double)nSecondsTimeout);
// 	                 }
// 	         }
// 	         }
// 	         catch(XPCException e)
// 	         {
// 	             MOOSTrace("Exception %s\n",e.sGetException());
// 	             throw CMOOSException("CMOOSCommObject::ReadPkt() Failed Rx");
// 	         }
// 	 	switch(nRxd)
// 	         {
// 	         case -1:
// 	             throw CMOOSException("Gross error....");
// 	             break;
// 	         case 0:
// 	             if(nSecondsTimeout>0)
// 	                 throw CMOOSException(MOOSFormat("remote side closed or lazy client ( waited more than %ds )",nSecondsTimeout));
// 	             else
// 	                 throw CMOOSException("remote side closed....");
// 	             break;
// 	         default:
// 			printf("nRxd: '%d'\n",nRxd);
// 	 	    PktRx.Fill(pBuffer,nRxd);
// 	             break;
// 	         }
//	     }
    	}
    
    	if(m_oSecurity.isIntegrityEnabled())
	{
		try
		{	
			int digestLen = m_oSecurity.getDigestLength();
			unsigned char digest[digestLen];
			if(nSecondsTimeout<0)
				nRxd  = pSocket->iRecieveMessage(digest,digestLen);
			else
				nRxd  = pSocket->iReadMessageWithTimeOut(digest,digestLen,(double)nSecondsTimeout);
			bool res = true;

			
			if(!m_oSecurity.checkPktIntegrity(PktRx.m_pStream, digest)){
				MOOSTrace("%sSECURITY WARNING: Integrity check FAILED%s\n",red,none);
				return false;
			}
		}
		catch(XPCException e)
		{
			MOOSTrace("Exception %s\n",e.sGetException());
			throw CMOOSException("CMOOSCommObject::ReadPkt() Failed Rx");
		}
	}	  
    	return true;
}

bool CMOOSCommObject::SendPkt(XPCSocket *pSocket, CMOOSCommPkt &PktTx, unsigned char* key)
{
    	int nSent = 0;
	int i;
	unsigned char* ciphertext, *plaintext;
	int ct_len;
	bool DoneTx = false;

	int digestLen = 2;
	if(m_oSecurity.isIntegrityEnabled())
	{
		digestLen = m_oSecurity.getDigestLength();
	}
	unsigned char digest[digestLen];
	
	if(m_oSecurity.isAuthenticationEnabled())
	{
		if(key == 0){
			key = getSessionKey(pSocket);
		}else
			MOOSTrace("SendPkt: using encryption key to distribute session key\n");
	}else
	{
		if(m_oSecurity.isEncryptionEnabled()){
			key = (unsigned char*)m_oSecurity.getEncryptionKey();
		}
	}

	try
    	{
		if(m_oSecurity.isEncryptionEnabled())
		{
			
			m_oSecurity.encryptPkt((const unsigned char*&)PktTx.m_pStream, ciphertext, PktTx.GetStreamLength(),key);
			int pkt_len = PktTx.GetStreamLength();
			
			nSent = pSocket->iSendMessage((void*) &pkt_len,sizeof(int));
			nSent = pSocket->iSendMessage(ciphertext, PktTx.GetStreamLength());
			DoneTx = (nSent == (PktTx.GetStreamLength()));
			free(ciphertext);
    		}else{
			int len = PktTx.GetStreamLength();
			nSent = pSocket->iSendMessage((void*)&len,sizeof(int));
			PktTx.m_pStream+=sizeof(int);
			nSent = pSocket->iSendMessage(PktTx.m_pStream,PktTx.GetStreamLength()-sizeof(int));
			DoneTx = (nSent == (PktTx.GetStreamLength()-sizeof(int)));
			PktTx.m_pStream-=sizeof(int);	
		}

		if(m_oSecurity.isIntegrityEnabled()){
			unsigned char* p = digest;
			m_oSecurity.hashPkt(PktTx.m_pStream, p);
			nSent = pSocket->iSendMessage((unsigned char*&) p,digestLen);
		}
	}
    	catch(XPCException e)
    	{
        	MOOSTrace("MOOSCommObject::SendPkt Exception caught %s\n",e.sGetException());
        	throw CMOOSException("CMOOSCommObject::SendPkt() Failed Tx");
    	}
	if(!DoneTx)
      		throw CMOOSException("CMOOSCommObject::SendPkt() Failed Tx");

    	return true;
}

bool CMOOSCommObject::SendMsg(XPCSocket *pSocket,CMOOSMsg &Msg, unsigned char* key)
{
    MOOSMSG_LIST MsgList;
    
    MsgList.push_front(Msg);

    CMOOSCommPkt Pkt;

    Pkt.Serialize(MsgList,true);

    return SendPkt(pSocket,Pkt, key);
}


bool CMOOSCommObject::ReadMsg(XPCSocket *pSocket,CMOOSMsg &Msg, int nSecondsTimeout, unsigned char* key)
{
    MOOSMSG_LIST MsgList;
    
    CMOOSCommPkt Pkt;

    if(ReadPkt(pSocket,Pkt,nSecondsTimeout, key))
    {

        Pkt.Serialize(MsgList,false);

        if(!MsgList.empty())
        {
            Msg = MsgList.front();
        }
        
    }


    return !MsgList.empty();
}

void CMOOSCommObject::InitSecurity(CMOOSFileReader& m_MissionReader)
{
	m_oSecurity.initSecurity(m_MissionReader);	
}


bool CMOOSCommObject::SocketsInit()
{

#ifdef _WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD( 2, 2 );
 
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */

        printf("failed socket init\n");
        return false;
    }
 
    /* Confirm that the WinSock DLL supports 2.2.*/
    /* Note that if the DLL supports versions greater    */
    /* than 2.2 in addition to 2.2, it will still return */
    /* 2.2 in wVersion since that is the version we      */
    /* requested.                                        */
 
    if ( LOBYTE( wsaData.wVersion ) != 2 ||
            HIBYTE( wsaData.wVersion ) != 2 ) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                     
        */

        printf("failed socket init\n");

        WSACleanup( );
        return false; 
    }
#endif
    return true;
}

void CMOOSCommObject::DoSecurityBanner()
{
	if(m_oSecurity.isEncryptionEnabled())
    {
	MOOSTrace("*       %sPacket Encryption %s ENABLED %s\n", magenta, green, none);
	MOOSTrace("*       %sEncryption/Decryption algorithm %s '%s' %s\n",magenta,blue, m_oSecurity.getEncryptionAlg(), none);
	MOOSTrace("*       %sEncryption/Decryption key %s'%s'%s\n", magenta,blue, m_oSecurity.getEncryptionKey(),none);
    }
    else
	MOOSTrace("*       %sEncryption %sDISABLED%s\n", magenta,red,none);
	
    if(m_oSecurity.isIntegrityEnabled())
    {
	MOOSTrace("*       %sPacket Integrity %sENABLED%s\n",magenta,green,none);
	MOOSTrace("*       %sHMAC algorithm %s'%s'%s\n", magenta,blue,m_oSecurity.getIntegrityAlg(),none);
	MOOSTrace("*       %sIntegrity key %s'%s'%s\n",magenta,blue, m_oSecurity.getIntegrityKey(),none);
	if(m_oSecurity.isDigestTruncationEnabled())
	{
		MOOSTrace("*       %sDigest Truncation %sENABLED%s\n",magenta,green,none);
		MOOSTrace("*       %sDigest Length %s'%d'%s\n",magenta,blue,m_oSecurity.getDigestLength(),none);
	}else
		MOOSTrace("*       %sDigest Truncation %sDISABLED%s\n",magenta,red,none);

    }
    else
	MOOSTrace("*       %sPacket Integrity %sDISABLED%s\n",magenta,red,none);
    if(m_oSecurity.isAuthenticationEnabled())
    {
	MOOSTrace("*       %sClient Authentication %sENABLED%s\n",magenta,green,none);
    }
    else
	MOOSTrace("*       %sClient Authentication %sDISABLED%s\n",magenta,red,none);

    MOOSTrace("*                    %sSecurity added by %sA.Lo Duca%s\n",magenta,cyan,none);
}

unsigned char* CMOOSCommObject::getSessionKey(XPCSocket *pSocket)
{
	MOOSTrace("WARNING invoking default\n");
	return 0;
}

