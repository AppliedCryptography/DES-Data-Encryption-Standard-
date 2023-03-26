#include "DES.h"

unsigned int main() {
    unsigned char m[8];
    cout << "Plain_text : ";
    memcpy(m, "fithcmus", 8);
    for (int o = 0; o < 8; o++) {
        for (int w = 7; w >= 0; w--) {
            cout << ((m[o] >> w) & 1);
        }
    }
    cout << endl;
    unsigned char key[8];
    memcpy(key, "12345678", 8);

    unsigned char c[8];
    memset(c, 0, sizeof(c));

    des(m, key, c);
    cout << "Cipher_text : ";
    for (int o = 0; o < 8; o++) {
        for (int w = 7; w >= 0; w--) {
            cout << ((c[o] >> w) & 1);
        }
    }
    cout << endl;
    return 0;
}
