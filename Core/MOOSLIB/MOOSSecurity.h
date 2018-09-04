
#if !defined(AFX_MOOSSECURITY_H__88A30007_9205_4FDA_B938_915FBE43027D__INCLUDED_)
#define AFX_MOOSSECURITY_H__88A30007_9205_4FDA_B938_915FBE43027D__INCLUDED_

#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>

#include <MOOSGenLib/MOOSGenLib.h>

#define ALG_LENGTH 10

//#define CLIENT_KEY_PAIR(c,k) pair<std::string,std::string>(c,k)

class CMOOSSecurity 
{
	
private:

	typedef std::map<std::string,unsigned char* > CLIENT_NAME_2_SESSION_KEY_MAP;
	CLIENT_NAME_2_SESSION_KEY_MAP m_SessionKey2ClientMap;


	unsigned  char m_sIntegrityKey[EVP_MAX_KEY_LENGTH + 1];
	unsigned char m_sEncryptionKey[EVP_MAX_KEY_LENGTH + 1];
	char m_sEncryptionAlg[ALG_LENGTH];
	char m_sIntegrityAlg[ALG_LENGTH];

	bool m_bEnableIntegrity;
	bool m_bEnableEncryption;
	bool m_bEnableAuthentication;
	bool m_bEnableDigestTruncation;
	int m_iDigestTruncationLength;

	int m_iDigestLength;
	
	void initEncryptContext(EVP_CIPHER_CTX& ctx, int type, unsigned char* k);
	void initIntegrityContext(HMAC_CTX& ctx);
	void select_random_key(unsigned char *k, int b);

public:
	void hashPkt(const unsigned char* pkt, unsigned char*& digest);
	/* check whether the hash is correct */
	bool checkPktIntegrity(const unsigned char* pkt,const unsigned char* digest);
	/* return true if packet has been encrypted*/	
	bool encryptPkt(unsigned const char*& msg, unsigned char*& ciphertext, int msg_len, unsigned char* k = 0);
	/* return true if packet has been decrypted*/	
	bool decryptPkt(unsigned char*& plaintext, const unsigned char*& ciphertext, int msg_len, unsigned char* k = 0);
	void printbyte(char b);
	CMOOSSecurity();
	void initSecurity(CMOOSFileReader& m_MissionReader);
	bool isEncryptionEnabled();
	bool isIntegrityEnabled();
	bool isAuthenticationEnabled();
	bool isDigestTruncationEnabled();
	const char* getEncryptionAlg();
	const unsigned char* getEncryptionKey();
	const char* getIntegrityAlg();
	const unsigned char* getIntegrityKey();
	int getDigestLength();
	const unsigned char* genSessionKey(std::string cName);
	const unsigned char* getSessionKey(std::string cName);
	void setSessionKey(std::string cName, unsigned char* k);
	
};

#endif
