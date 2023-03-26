#include"DES.h"

void IP(unsigned char block_plaintext[]) {
    unsigned char c[8];
    memset(c, 0, sizeof(c));
    unsigned char temp = 0;
    short unsigned int part[8] = { 64,16,4,1,128,32,8,2 };
    for ( int i = 0; i < 8; i++) {
        for ( int j = 7; j >= 0; j--) {
            if ((block_plaintext[j] & part[i]) == 0)
                c[i] = (c[i] << 1);
            else c[i] = (c[i] << 1) | 1;
        }
    }
    memcpy(block_plaintext, c, 8);
}

void FP(unsigned char block_plaintext[]) {
    short unsigned int checkBit = 1;
    short unsigned int order[8] = { 4,0,5,1,6,2,7,3 };
    unsigned char c[8];
    memset(c, 0, sizeof(c));

    for ( int i = 0; i < 8; i++) {
        for ( int j = 0; j < 8; j++) {
            if ((block_plaintext[order[j]] & checkBit) == 0)
                c[i] = (c[i] << 1) | 0;
            else c[i] = (c[i] << 1) | 1;
        }
        checkBit = checkBit * 2;
    }

    for ( int i = 0; i < 8; i++) {
        block_plaintext[i] = c[i];
    }
}

void des(unsigned char block_plaintext[], unsigned char key[], unsigned char block_ciphertext[]) {
    IP(block_plaintext);

    unsigned char round_keys[16][6];
    memset(round_keys, 0, sizeof(round_keys));
    generate_key(key, round_keys);

    unsigned char L[4], R[4];
    memcpy(L, block_plaintext, 4);
    memcpy(R, (block_plaintext + 4), 4);

    unsigned char p[4];
    memset(p, 0, sizeof(p));
    
    for (int i = 0; i < 16; i++) {
        f_function(R, round_keys[i], p);
        for (size_t i = 0; i < 4; i++) {
            p[i] = p[i] ^ L[i];
        }
        memcpy(L, R, 4);
        memcpy(R, p, 4);
    }    

    memcpy(block_ciphertext, R, 4);
    memcpy((block_ciphertext + 4), L, 4);
   
    FP(block_ciphertext);
}