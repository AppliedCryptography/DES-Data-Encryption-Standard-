#include "DES.h"
void print(unsigned char str[], size_t lenght) {
    for (int i = 0; i < lenght; i++)
        printf("%02x ", str[i]);
    cout << endl;
}

void CBC(unsigned char plain_text[], size_t length,unsigned char key[], unsigned char cipher_text[] , unsigned char initialization_vector[]) {
    // block 0
    // xor
    unsigned char Xor[8];
    for (size_t i = 0; i < 8; i++) {
        Xor[i] = plain_text[i] ^ initialization_vector[i];
    }
    des(Xor, key, cipher_text);
  
    // extant blocks 
    for (int i = 8; i < length; i+=8) {
        // xor 
        for (size_t j = 0; j < 8; j++) {
            Xor[j] = plain_text[i+j] ^ cipher_text[i - (8 - j)];
        }
        des(Xor, key, cipher_text + i);
    }
}

unsigned int main() {
    unsigned char m[24]; memcpy(m, "duong quang binh12345678", sizeof(m));    
    unsigned char key[8]; memcpy(key, "12345678", 8);
    unsigned char c[24]; memset(c, 0, sizeof(c));
    unsigned char iv[8]; memset(iv, 0, sizeof(iv));

    CBC(m, 24, key, c, iv);
        
    cout << "Enscrypt_text : ";
    print(c, 24);


    //unsigned char d[8];
    //memset(d, 0, 8);
    //des(c, key, d, 1);
    //cout << "Descipt_text : ";
    //for (int o = 0; o < 8; o++) {
    //    for (int w = 7; w >= 0; w--) {
    //        cout << ((d[o] >> w) & 1);
    //    }
    //}
    //cout << endl;
    return 0;
}
