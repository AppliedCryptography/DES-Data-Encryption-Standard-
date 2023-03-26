#include "generate_key.h"
short unsigned int pc1[7][8] = {
	57,49,41,33,25,17,9,1,
	58,50,42,34,26,18,10,2,
	59,51,43,35,27,19,11,3,
	60,52,44,36,63,55,47,39,
	31,23,15,7,62,54,46,38,
	30,22,14,6,61,53,45,37,
	29,21,13,5,28,20,12,4
};
short unsigned int pc2[6][8] = {
	14,17,11,24,1,5,3,28,
	15,6,21,10,23,19,12,4,
	26,8,16,7,27,20,13,2,
	41,52,31,37,47,55,30,40,
	51,45,33,48,44,49,39,56,
	34,53,46,42,50,36,29,32
};

void PC1_function(unsigned char key[], unsigned char PC1[]) {
	for ( int i = 0; i < 7; i++) {
		for ( int j = 0; j < 8; j++) {
			if ((key[(pc1[i][j] - 1) / 8] & (unsigned int)(128 / pow(2, (pc1[i][j] - 1) % 8))) == 0)
				PC1[i] = (PC1[i] << 1);
			else PC1[i] = ((PC1[i] << 1) | 1);
		}
	}
}

void PC2_function(unsigned unsigned int head, unsigned int tail, unsigned char sub_k[]) {
	size_t index = 0;
	for (size_t i = 0; i < 6; i++){
		for (size_t j = 0; j < 8; j++) {
			unsigned int buf;
			if (pc2[i][j] > 28)
				buf = tail;
			else buf = head;

			if ((buf & (unsigned int)(pow(2, 27) / pow(2, ((pc2[i][j] - 1) % 28)))) == 0) {
				sub_k[i] = (sub_k[i] << 1);
			}
			else sub_k[i] = ((sub_k[i] << 1) | 1);
			index++;
		}
	}
}

void generate_key(unsigned char key[], unsigned char round_keys[][6]) {
	unsigned char PC1[7];
	memset(PC1, 0, sizeof(PC1));
	PC1_function(key, PC1);

	unsigned int head = 0;
	head = ((((((((head << 8) | PC1[0]) << 8) | PC1[1]) << 8) | PC1[2]) << 4) | (PC1[3] >> 4));
	unsigned int tail = 0;
	tail = ((((((((tail << 4) | (PC1[3] & 15)) << 8) | PC1[4]) << 8) | PC1[5]) << 8) | PC1[6]);

	for (size_t i = 0; i < 16; i++) {
		if (i == 0 || i == 1 || i == 8 || i == 15) {
			head = ((head >> 27) & 1) | (head << 1);
			tail = ((tail >> 27) & 1) | (tail << 1);
		}
		else {
			head = ((head >> 27) & 1) | (head << 1);
			tail = ((tail >> 27) & 1) | (tail << 1);
			head = ((head >> 27) & 1) | (head << 1);
			tail = ((tail >> 27) & 1) | (tail << 1);
		}
		PC2_function(head, tail, round_keys[i]);
	}
}