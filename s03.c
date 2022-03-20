#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main (){

    //Nilai Vin
    float vin = 5.0;
    //Niai Resistansi
    float r = 20*10^(3);
    //Nilai Kapasitor
    float c = 183009*(pow(10,-12));
    //Nilai V output
    float vo = 0;
    //Waktu
    float t = 0;
    //nilai e
    float e = 2.718;

    printf("Vo saat t = %f yaitu %f\n", t, vo);

 //Vo tunak saat Vo bernilai 0
    for (float t=0; vo<vin < 0.001; t += 0.0001){
        vo = vin*(1-pow(e, -t/(r*c)));
        printf("Nilai Vo saat t = %f sebesar %f\n", t, vo);
    }

    printf("Vo tunak saat pertama Vo sama dengan Vin yaitu saat nilainya %f\n", vo);
    printf("nilai konstanta waktu %f", (0.006)/(r*c));
    return 0;
}
