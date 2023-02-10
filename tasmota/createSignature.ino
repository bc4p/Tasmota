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

char* getTimeAndDateOutOfJson(){
    size_t beginTimeJson=9;
    size_t endTimeJson=28;
    char msg[endTimeJson-beginTimeJson];
    //size_t length = (TasmotaGlobal.mqtt_data).copy(msg,endTimeJson-beginTimeJson,beginTimeJson);
    for(int i=0;i<endTimeJson-beginTimeJson;i++){
        msg[i]=TasmotaGlobal.mqtt_data[i+beginTimeJson];
        ResponseAppend_P(PSTR("%c"),msg[i]);
    }
    return msg;
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

uint8_t* CreateSignatureForString(char* stringPointer){
    //Generating keys
    if(!keypairGenerated){
        Ed25519::generatePrivateKey(privateKey);
        Ed25519::derivePublicKey(publicKey, privateKey);
        keypairGenerated=true;
    }

    //Getting timestamp
    size_t beginTimeJson=9;
    size_t endTimeJson=28;
    size_t lengthTimestamp=endTimeJson-beginTimeJson;
    char msg[lengthTimestamp];
    //size_t length = (TasmotaGlobal.mqtt_data).copy(msg,endTimeJson-beginTimeJson,beginTimeJson);
    for(int i=0;i<lengthTimestamp;i++){
        msg[i]=TasmotaGlobal.mqtt_data[i+beginTimeJson];
        //ResponseAppend_P(PSTR("%c"),msg[i]);
    }

    //Creating the message
    size_t N=lengthTimestamp+strlen(stringPointer)+1; //Timestamp and value seperated by "," (=>+1)
    uint8_t message[N];

    for(int i=0;i<lengthTimestamp;i++){
        message[i]=msg[i];
    }
    message[lengthTimestamp]=',';
    for(int i=lengthTimestamp+1;i<N;i++){
        message[i]=stringPointer[i-lengthTimestamp-1];
    }
    //Printing message on which signature is calculated (debug purposes)
    ResponseAppend_P(PSTR(", \"Calculating signature on\": \""));
    for(int i=0;i<N;i++){
        ResponseAppend_P(PSTR("%c"),message[i]);
    }
    ResponseAppend_P(PSTR("\""));



    Ed25519::sign(signature, privateKey, publicKey, message, N);
    return signature;
}

String CreateSignatureString(float floatNumber){
    uint8_t* pointerSignature=CreateSignatureForFloat(floatNumber);
    String signatureString=convertToString(pointerSignature, 64);
    return signatureString;
}

void printSignatureFromPointer(uint8_t* signaturePointer){
    ResponseAppend_P(PSTR(",\"Signature\": {"));
    for(int i=0;i<64;i++){
        ResponseAppend_P(PSTR("%02x"),signaturePointer[i]);
    }
    ResponseAppend_P(PSTR("}"));

}