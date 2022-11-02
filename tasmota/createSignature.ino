#include <Ed25519.h>

uint8_t privateKey[32];
uint8_t publicKey[32];
uint8_t signature[64];
bool keypairGenerated=false;



String convertToString(uint8_t* a, size_t len)
 {
    int i;
    String s = "";
    for (i = 0; i < len; i++) {
        s = s + a[i];
    }
    return s;
}

uint8_t* CreateSignatureForFloat(float floatNumber){
    size_t N=sizeof(floatNumber);
    uint8_t message[N];
    uint8_t *floatNumberArray;
    if(!keypairGenerated){
        Ed25519::generatePrivateKey(privateKey);
        Ed25519::derivePublicKey(publicKey, privateKey);
        keypairGenerated=true;
    }
    floatNumberArray = reinterpret_cast<uint8_t*>(&floatNumber); //0=end, 3=begin, so 3 2 1 0 forms binary representation
    for(int i=0;i<N;i++){
        message[i]=floatNumberArray[i];
    }
  Ed25519::sign(signature, privateKey, publicKey, message, N);
  return signature;
}

String CreateSignatureString(float floatNumber){
    uint8_t* pointerSignature=CreateSignatureForFloat(floatNumber);
    String signatureString=convertToString(pointerSignature, 64);
    return signatureString;
}

void printSignatureFromPointer(uint8_t* signaturePointer){
    ResponseAppend_P(PSTR("},\"Signature\": {"));
    for(int i=0;i<63;i++){
        ResponseAppend_P(PSTR("%02x "),signaturePointer[i]);
    }
    ResponseAppend_P(PSTR("%02x"),signaturePointer[63]);
}