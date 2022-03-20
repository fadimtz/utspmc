#include <stdio.h>
void bin(short int n)
{
    unsigned short int i;
    for (i = 1 << 7; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
    printf("\n");
}

int main() {
    int NIM = 18320009;
    NIM = ((NIM / 100000) % 100) * 1000 + NIM % 1000;
    short int A = NIM & 1;
    printf ("Nilai A yaitu: %d \n", A);

    short int y = 0b11101111;
    short int x = 0b10100101;
    short int hasil = (A & y) ^ x;

    // printf
    printf("Binary : ");
    bin(hasil);

    printf("Hex : %x\n", hasil);
    printf("Unsigned : %u\n", hasil);
    printf("Signed 2C : %d\n", hasil);
    printf("\n");

    y = 0b11110011;
    x = 0b11011011;
    hasil = (A & y) ^ x;

    printf("Binary : ");
    bin(hasil);

    printf("Hex : %x\n", hasil);
    printf("Unsigned : %u\n", hasil);
    printf("Signed 2C : %d\n", hasil);
    printf(" \n");

    y = 0b10100101;
    x = 0b00101111;
    hasil = (A & y) ^ x;

    printf("Binary : ");
    bin(hasil);

    printf("Hex : %x\n", hasil);
    printf("Unsigned : %u\n", hasil);
    printf("Signed 2C : %d\n", hasil);

    return 0 ;
}