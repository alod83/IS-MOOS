#include <cstring>



#include "MOOSSecurity.h"

#define ENCRYPT 0
#define DECRYPT 1



using namespace std;

void CMOOSSecurity::printbyte(char b) {
	char c;
	c = b;
	c = c >> 4;
	c = c & 15;
	printf("%X", c);
	c = b;
	c = c & 15;
	printf("%X:", c);
}

void CMOOSSecurity::select_random_key(unsigned char *k, int b) {
	RAND_bytes( (unsigned char*)k, b);
	k[b-1] = '\0';
	
}

void CMOOSSecurity::initSecurity(CMOOSFileReader& m_MissionReader)
{
	
	string key, algo;
	m_bEnableIntegrity = false;
	m_bEnableDigestTruncation = false;
	m_MissionReader.GetValue("ENABLE_INTEGRITY", m_bEnableIntegrity);
	
	if(m_bEnableIntegrity){
		if(!m_MissionReader.GetValue("INTEGRITY_KEY", key)){
			m_bEnableIntegrity = false;
		}else{ 
			if(!m_MissionReader.GetValue("INTEGRITY_ALG", algo)){
				m_bEnableIntegrity = false;
			}else{
				if(!m_MissionReader.GetValue("DIGEST_TRUNCATION", m_bEnableDigestTruncation)){
					m_bEnableDigestTruncation = false;
				}else{
					if(!m_MissionReader.GetValue("DIGEST_LENGTH", m_iDigestTruncationLength)){
						m_iDigestTruncationLength = 8;
						MOOSTrace("%sWARNING - Missing digest length assuming  '%d' bits%s\n",red, m_iDigestTruncationLength,none);
					}
					
				}
			}
		}
	}
	if(m_bEnableIntegrity){
		strcpy((char*)m_sIntegrityKey, key.c_str());
		strcpy((char*)m_sIntegrityAlg, algo.c_str());		
		if(strcmp(m_sIntegrityAlg,"MD5") == 0)
			m_iDigestLength = 16;
		else if(strcmp(m_sIntegrityAlg,"SHA1") == 0)
			m_iDigestLength = 20;
	}
	key.clear();
	algo.clear();
	
	m_bEnableEncryption = false;
	m_MissionReader.GetValue("ENABLE_ENCRYPTION", m_bEnableEncryption);
			
    	if(m_bEnableEncryption){
    		if(!m_MissionReader.GetValue("ENCRYTPION_KEY", key)){
			m_bEnableEncryption = false;
		}else{
			if(!m_MissionReader.GetValue("ENCRYPTION_ALG", algo)){
				m_bEnableEncryption = false;
			}
		}
	}
	if(m_bEnableEncryption){
		strcpy((char*)m_sEncryptionKey, key.c_str());
		strcpy((char*)m_sEncryptionAlg, algo.c_str());
		
	}
	key.clear();
	algo.clear();

	m_bEnableAuthentication = false;
	m_MissionReader.GetValue("ENABLE_AUTHENTICATION", m_bEnableAuthentication);
		
}


CMOOSSecurity::CMOOSSecurity()
{

}

void CMOOSSecurity::initIntegrityContext(HMAC_CTX& ctx)
{
	int key_len = EVP_MAX_KEY_LENGTH;
	if(strcmp(m_sIntegrityAlg,"MD5") == 0)
	{
		HMAC_Init(&ctx, m_sIntegrityKey, key_len, EVP_md5());
	}
	else if(strcmp(m_sIntegrityAlg,"SHA1") == 0)
	{	
		HMAC_Init(&ctx, m_sIntegrityKey, key_len, EVP_sha1());
	}
	else{
		m_bEnableIntegrity = false;
	}
}	
void CMOOSSecurity::hashPkt(const unsigned char* pkt, unsigned char*& digest)
{
	if(!m_bEnableIntegrity)return;

	int           i;
	HMAC_CTX      ctx;
	unsigned int  len;
	unsigned char myDigest[m_iDigestLength];
	initIntegrityContext(ctx);
	
	HMAC_Update(&ctx, pkt, 8);
	HMAC_Final(&ctx, &myDigest[0], &len);
	int digestLen = (m_bEnableDigestTruncation)? m_iDigestTruncationLength : m_iDigestLength; 
	for(int i = 0; i < digestLen; i++)
		digest[i] = myDigest[i];
	
}


/* check whether the hash is correct */
bool CMOOSSecurity::checkPktIntegrity(const unsigned char* pkt, const unsigned char* digest)
{
	if(!m_bEnableIntegrity)return true;
	int len = m_iDigestLength;
	if(m_bEnableDigestTruncation)
		len = m_iDigestTruncationLength;
	unsigned char myDigest[len];
	unsigned char* p = &myDigest[0];
	int i;
	hashPkt(pkt, p);
	bool ret = false;

	if(strncmp((const char*) digest, (char*) p,len) == 0){
		ret = true;
	}
	
	
	return ret;
	
	
}

void CMOOSSecurity::initEncryptContext(EVP_CIPHER_CTX& ctx, int type, unsigned char* k){
	EVP_CIPHER_CTX_init(&ctx);
	if(strcmp(m_sEncryptionAlg,"AES") == 0) {
		if(type == ENCRYPT)
			EVP_EncryptInit(&ctx,EVP_aes_128_ecb(),k,NULL);
		else	
			EVP_DecryptInit(&ctx,EVP_aes_128_ecb(),k,NULL);
	}
	else if(strcmp(m_sEncryptionAlg,"BLOWFISH") == 0) {
		if(type == ENCRYPT)
			EVP_EncryptInit(&ctx,EVP_bf_ecb(),k,NULL);
		else
			EVP_DecryptInit(&ctx,EVP_bf_ecb(),k,NULL);
	
	}
	else if(strcmp(m_sEncryptionAlg,"CAST5") == 0) {
		if(type == ENCRYPT)
			EVP_EncryptInit(&ctx,EVP_cast5_ecb(),k,NULL);
		else
			EVP_DecryptInit(&ctx,EVP_cast5_ecb(),k,NULL);
	
	}
	
	else if(strcmp(m_sEncryptionAlg,"RC2") == 0) {
		if(type == ENCRYPT)
			EVP_EncryptInit(&ctx,EVP_rc2_ecb(),k,NULL);
		else
			EVP_DecryptInit(&ctx,EVP_rc2_ecb(),k,NULL);

	}
	else{
		m_bEnableEncryption = false;
	}
	
}


bool CMOOSSecurity::encryptPkt(unsigned const char*& msg, unsigned char*& ciphertext, int msg_len, unsigned char* k){
	if(!m_bEnableEncryption){
		ciphertext = 0;
		return false;
	}
	if(k == 0)
		k = m_sEncryptionKey;

	EVP_CIPHER_CTX ctx;
	initEncryptContext(ctx,ENCRYPT,k);
	ciphertext = (unsigned char *)malloc(msg_len);
	if(ciphertext == 0){
		MOOSTrace("Unable to allocate space for ciphertext\n");
		return false;
	}

	int blockSize = EVP_CIPHER_CTX_block_size(&ctx);
	int restOfBytes = msg_len % blockSize;  
	int nc = blockSize;
	for (int i = 0; i < msg_len - restOfBytes; i+=blockSize) {
		EVP_EncryptUpdate(&ctx, &ciphertext[i], &nc,&msg[i], blockSize);
	}
	
	// CTS
	if ( restOfBytes ) {
		
		int n = msg_len - restOfBytes;
		int nM1 =  msg_len - restOfBytes - blockSize;

		unsigned char* PnM1 = (unsigned char*) &msg[nM1];
		unsigned char* Pn = (unsigned char*) &msg[n];

		unsigned char EnM1[blockSize];
		nc = 0;
		initEncryptContext(ctx,ENCRYPT,k);
		EVP_EncryptUpdate(&ctx,&EnM1[0],&nc,&PnM1[0],blockSize);

		for(int j = 0; j < restOfBytes; j++)
		{
			ciphertext[n + j] = EnM1[j];
		}
		
		unsigned char Dn[blockSize];
		for(int j = 0; j < restOfBytes; j++){
			Dn[j] = msg[n + j];
			
		}
		for(int j = restOfBytes; j < blockSize; j++)
		{
			Dn[j] = EnM1[j]; 
			
 		}
		memcpy((char*)Dn,(char*)Pn, restOfBytes);
		nc = 0;
		initEncryptContext(ctx,ENCRYPT,k);
		EVP_EncryptUpdate(&ctx,&ciphertext[nM1],&nc,&Dn[0],blockSize);
	}
	return true;
}

bool CMOOSSecurity::decryptPkt(unsigned char*& plaintext, const unsigned char*& ciphertext, int msg_len, unsigned char* k){
	if(!m_bEnableEncryption){
		plaintext = 0;
		return false;
	}
	if(k == 0)
		k = m_sEncryptionKey;
 	EVP_CIPHER_CTX ctx;
 	initEncryptContext(ctx,DECRYPT,k);
 	plaintext = (unsigned char *)malloc(msg_len);
 	bzero(plaintext, msg_len);
 	int nc = 0;

	int blockSize = EVP_CIPHER_CTX_block_size(&ctx);
	int numOfBlock = (msg_len)/blockSize; // get the numOfBlocks 
	int restOfBytes = msg_len % blockSize;

 	EVP_DecryptUpdate(&ctx, &plaintext[0],&nc, &ciphertext[0], msg_len - restOfBytes);

	// CTS
	if ( restOfBytes ) {

		int n = msg_len - restOfBytes;
		int nM1 =  msg_len - restOfBytes - blockSize;

		unsigned char Dn[blockSize];
		nc=0;
		initEncryptContext(ctx,DECRYPT,k);
		EVP_DecryptUpdate(&ctx, &Dn[0],&nc,&ciphertext[nM1] , blockSize); 
		unsigned char* Cn = (unsigned char*) &ciphertext[n];
		
		unsigned char EnM1[blockSize];
		memcpy((char*)&EnM1[0], (char*) &Cn[0], restOfBytes);
		memcpy((char*)&EnM1[restOfBytes], (char*) &Dn[restOfBytes], blockSize - restOfBytes);
		
		nc = 0;
		unsigned char PnM1[blockSize];
		initEncryptContext(ctx,DECRYPT,k);
		EVP_DecryptUpdate(&ctx, &PnM1[0],&nc, &EnM1[0], blockSize);
		
		for(int j = 0; j < blockSize; j++)
			plaintext[nM1 + j] = PnM1[j];

		for(int j = 0; j < restOfBytes; j++)
			plaintext[n + j] = Dn[j];
	}	
	return true;
}

bool CMOOSSecurity::isEncryptionEnabled()
{
	return m_bEnableEncryption;
}

bool CMOOSSecurity::isIntegrityEnabled()
{
	return m_bEnableIntegrity;
}

const char* CMOOSSecurity::getEncryptionAlg()
{
	return m_sEncryptionAlg;
}

const unsigned char* CMOOSSecurity::getEncryptionKey()
{
	return (const unsigned char*) m_sEncryptionKey;
}

const char* CMOOSSecurity::getIntegrityAlg()
{
	return (const char*) m_sIntegrityAlg;
}

const unsigned char* CMOOSSecurity::getIntegrityKey()
{
	return (const unsigned char*) m_sIntegrityKey;
}

int CMOOSSecurity::getDigestLength()
{
	if(m_bEnableDigestTruncation)
		return m_iDigestTruncationLength;
	return m_iDigestLength;	

}

const unsigned char* CMOOSSecurity::genSessionKey(std::string cName)
{
	unsigned char* k = (unsigned char*) malloc(EVP_MAX_KEY_LENGTH);
	select_random_key(k, EVP_MAX_KEY_LENGTH);
	return k;
}

const unsigned char* CMOOSSecurity::getSessionKey(std::string cName)
{
	return m_SessionKey2ClientMap[cName];
	
}

void CMOOSSecurity::setSessionKey(std::string cName, unsigned char* k)
{
	m_SessionKey2ClientMap[cName] = k;
	
}

bool CMOOSSecurity::isAuthenticationEnabled()
{
	return m_bEnableAuthentication;
}

bool CMOOSSecurity::isDigestTruncationEnabled()
{
	return m_bEnableDigestTruncation;
}


