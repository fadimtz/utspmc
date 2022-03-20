#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LEN 255

int main(){
    //Kecepatan Cahaya (*10^8)
    float c = 2.9979;
    //Muatan Elektron (*10^-30)
    float e = 16.02;
    //Massa Diam (*10^-18)
    float m0 = 0.9109;
    
    //Array untuk Massa Relatif
    float massa_relatif[MAX_LEN];
    //Array untuk Kecepatan
    float v[MAX_LEN];

    char filename[MAX_LEN];
    printf("Masukkan file external: ");
    scanf("%s", filename);

    //open file
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp==NULL){
        printf("File tidak ditemukan.");

    }
    else{
        float token[MAX_LEN];
        float tegangan[MAX_LEN];

        //input data ke array
        int line = 0;
        while(fgets(token, MAX_LEN, fp)){
            tegangan[line] = atof(token);
            line++;
        }

        //hitung massa relativistik dan kecepatan elektron
        float massa;
        float kecepatan;
        for(int i=0; i<line; i++){
            //Menghitung Massa (*10^-30)
            massa = (tegangan[i]*e/pow(c, 2)) + m0;
            massa_relatif[i] = massa;

            //Menghitung Kecepatan (10^8)
            kecepatan = sqrt((pow(c,2))-(pow((m0*c/massa_relatif[i]),2)));
            v[i] = kecepatan;
        }

        for(int i=0; i<line; i++){
            printf("Tegangan %f memiliki massa relatif %f x 10^-30 dan kecepatan %f x10^8.\n", tegangan[i], massa_relatif[i], v[i]);
        }

        return 0;
    }
}