#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 255
#define column_size 8

typedef struct penduduk {
    int nik;
    char nama[MAX_LEN];
    char tempat_lahir[MAX_LEN];
    char tanggal_lahir[MAX_LEN];
    int umur;
    char gender[MAX_LEN];
    char goldar[MAX_LEN];
    char status[MAX_LEN];
    char pekerjaan[MAX_LEN];
} penduduk;

//Mencetak Menu saat Program Dibuka
void menu_utama(FILE * fp, penduduk * data_ktp, int jumlah_data);


//parsing data
void parsing(FILE * fp, penduduk * data, int jumlah_data){
    char line [MAX_LEN];
    char *token;
    for (int i= 0; i < jumlah_data; i++){
        fgets(line,MAX_LEN,fp);
        token = strtok(line,",");
        data[i].nik = atoi(token);

        for (int j = 0; j < column_size-1; j++){
            token = strtok(NULL,",");
            if (j == 0) {
                strcpy(data[i].nama,token);
            } 
            else if (j == 1){
                char temp[MAX_LEN];
                strcpy(temp,token);
                token = strtok(NULL,",");
                strcat(temp,", ");
                strcat(temp, token);
                strcpy(data[i].tempat_lahir,temp);
            } 
            else if (j == 2) {
                strcpy(data[i].tanggal_lahir,token);
            } 
            else if (j == 3) {
                data[i].umur = atoi(token);
            } 
            else if (j == 4) {
                strcpy(data[i].gender,token);
            }
            else if (j == 5) {
                strcpy(data[i].goldar,token);
            } 
            else if (j == 6) {
                strcpy(data[i].status,token);
            }
            else if (j == 7) {
                strcpy(data[i].pekerjaan,token);
            }
        }
    }
}

//menyimpan data
void save_data(FILE *fp, penduduk * data_penduduk, int jumlah_data){
    FILE * ftemp;

    ftemp = fopen("temp.txt","w");

    for (int i=0; i < jumlah_data; i++){
        fprintf(ftemp,"%d,%s,%s,%s,%d,%s,%s,%s,%s\n",
        data_penduduk[i].nik, data_penduduk[i].nama, data_penduduk[i].tempat_lahir,
        data_penduduk[i].tanggal_lahir, data_penduduk[i].umur, data_penduduk[i].gender,
        data_penduduk[i].goldar, data_penduduk[i].status, data_penduduk[i].pekerjaan
        );

    }
    fclose(ftemp);
    rename("temp.txt","data.txt");
}

//Mencari data berdasarkan NIK/Nama/Umur
void cari_data (FILE * fp, penduduk * data_penduduk, int jumlah_data){
//input preferensi pencarian
    int menu;
    char line[MAX_LEN];
    printf("\nMenu Pencarian Data: \n");
    printf("1. Cari NIK\n");
    printf("2. Cari Nama\n");
    printf("3. Cari Umur\n");    
    printf("\nData yang akan dicari: ");
    scanf("%d", &menu);

    //validasi input
    while (menu != 1 && menu != 2 && menu != 3){
        printf("Masukkan tidak valid\n");
        printf("\nPilihan: ");
        scanf("%d", &menu);
    }

    //input pencarian
    if (menu == 1) {
        printf("\nMasukkan NIK: ");
    } 
    else if (menu == 2) {
        printf("\nMasukkan Nama: ");
    }
    else { // menu==3
        printf("\nMasukkan Umur: ");
    }
    scanf("%s",line);


    //pencarian
    int found = 0;
    int i = 0;
    int id = 0;

    while (found == 0 && i < jumlah_data){
        if(menu == 1){
            if (data_penduduk[i].nik == atoi(line)){
                found = 1;
                id = i;
            }
        } 
        else if (menu == 2) {
            if (strstr(data_penduduk[i].nama,line)){
                found = 1;
                id = i;
            }
        }
        else { //menu == 3}
            if (data_penduduk[i].umur == atoi(line)){
                found = 1;
                id = i;
            }
        }
        i++;
    }
    
    //cetak hasil pencarian
    printf("\nHasil Pencarian\n");
    printf("NIK : %d\n", data_penduduk[id].nik);
    printf("Nama : %s\n", data_penduduk[id].nama);
    printf("Tempat Lahir : %s\n", data_penduduk[id].tempat_lahir);
    printf("Tanggal Lahir : %s\n", data_penduduk[id].tanggal_lahir);
    printf("Umur : %d\n", data_penduduk[id].umur);
    printf("Jenis Kelamin : %s\n", data_penduduk[id].gender);
    printf("Golongan Darah : %s\n", data_penduduk[id].goldar);
    printf("Status : %s\n", data_penduduk[id].status);
    printf("Pekerjaan : %s\n", data_penduduk[id].pekerjaan);

    char op;
    printf("\n Kembali ke menu utama?(y/n)");
    scanf("%c",&op);

    while ((&op != "y"||&op != "Y") && (&op != "n"||&op != "N")) {
        printf("\ninput tidak valid.");
        printf("\n Kembali ke menu utama?(y/n)");
        scanf("%c",&op);
    }

    if (&op == "yes" || &op == "Y") {
        menu_utama(fp,data_penduduk,jumlah_data);
    } 
    else {
        cari_data(fp, data_penduduk,jumlah_data);
    }
}


//Update Data
void update_data (FILE * fp, penduduk * data_penduduk, int jumlah_data) {
    int n_data;
    printf("\nMenu Rekam Data\n");
    printf("Jumlah data yang akan direkam: ");
    scanf("%d", &n_data);
    data_penduduk = (penduduk*) realloc(data_penduduk,(jumlah_data+n_data)*sizeof(penduduk));

    //perekaman data masing-masing komponen
    printf("\nPerekaman Data");
    for (int i = 0; i < n_data; i++){
        printf("\nInput data ke-%d", i+1);
        printf("\nNIK: ");
        scanf("%d", &data_penduduk[jumlah_data+i].nik);
        fflush(stdin);

        printf("Nama: ");
        scanf("%[^\n]%*c",data_penduduk[jumlah_data+i].nama);
        fflush(stdin);

        printf("Tempat Lahir: ");
        scanf("%[^\n]%*c",data_penduduk[jumlah_data+i].tempat_lahir);
        fflush(stdin);

        printf("Tanggal Lahir: ");
        scanf("%[^\n]%*c",data_penduduk[jumlah_data+i].tanggal_lahir);
        fflush(stdin);

        printf("Umur: ");
        scanf("%*d",data_penduduk[jumlah_data+i].umur);
        fflush(stdin);

        printf("Jenis Kelamin: ");
        scanf("%[^\n]%*c",data_penduduk[jumlah_data+i].gender);
        fflush(stdin);

        printf("Golongan Darah: ");
        scanf("%[^\n]%*c",data_penduduk[jumlah_data+i].goldar);
        fflush(stdin);

        printf("Status: ");
        scanf("%[^\n]%*c",data_penduduk[jumlah_data+i].status);
        fflush(stdin);

        printf("Pekerjaan: ");
        scanf("%[^\n]%*c",data_penduduk[jumlah_data+i].pekerjaan);
        fflush(stdin);
    }

    jumlah_data = jumlah_data + n_data;
    printf("\nPerekaman data selesai. Program akan kembali ke menu utama.\n");
    menu_utama(fp, data_penduduk,jumlah_data);
}

//Menghapus Data
void hapus_data(FILE * fp, penduduk * data_penduduk, int jumlah_data) {
    //pengaturan ulang ukuran array
    int n_data;
    printf("\nMenu Penghapusan Data\n");
    printf("Jumlah data yang ingin dihapus: ");
    scanf("%d", &n_data);
    fflush(stdin);

    for (int i = 0; i < n_data; i++){
        //input pencarian
        char line[MAX_LEN];
        printf("\nMasukkan NIK: ");
        scanf("%s",line);

        //pencarian
        int found = 0;
        int j = 0;
        int id = 0;

        while (found == 0 && j < jumlah_data){
            (data_penduduk[j].nik = atoi(line));
            found = 1;
            id = j;
            j++;
        }

        //penghapusan data
        penduduk *temp;
        temp = data_penduduk;
        data_penduduk = (penduduk*) realloc(data_penduduk,(jumlah_data-1)*sizeof(penduduk));
        for(int k = 0; k < (jumlah_data-1); k++){
            if (k >= id){
                data_penduduk[k].nik = temp[k+1].nik;
                strcpy(data_penduduk[k].nama, temp[k+1].nama);
                strcpy(data_penduduk[k].tempat_lahir, temp[k+1].tempat_lahir);
                strcpy(data_penduduk[k].tanggal_lahir, temp[k+1].tanggal_lahir);
                data_penduduk[k].umur = temp[k+1].umur;
                strcpy(data_penduduk[k].gender, temp[k+1].gender);
                strcpy(data_penduduk[k].goldar, temp[k+1].goldar);
                strcpy(data_penduduk[k].status, temp[k+1].status);
                strcpy(data_penduduk[k].pekerjaan, temp[k+1].pekerjaan);
            }
        }
    }
    jumlah_data = jumlah_data - n_data;
    printf("\nPenghapusan data selesai. Program akan kembali ke menu utama.\n");
    menu_utama(fp, data_penduduk, jumlah_data);
}

//Menampilkan menu utama
void menu_utama(FILE * fp, penduduk * data_penduduk, int jumlah_data){
    int menu;
    printf("\nMenu Pencatatan Data Kependudukan: \n");
    printf("1. Cari Data\n");
    printf("2. Update Data\n");
    printf("3. Hapus Data\n");
    printf("0. Keluar\n");
    printf("\nYang akan dilakukan: ");
    scanf("%d", &menu);

    //validasi input
    while (menu != 1 && menu!= 2 && menu!= 3 && menu!= 0){
        printf("Masukkan tidak valid\n");
        printf("\nPilihan: ");
        scanf("%d", &menu);
    }

    if (menu == 1){
        cari_data(fp, data_penduduk, jumlah_data);
    } 
    else if (menu == 2) {
        update_data(fp, data_penduduk, jumlah_data);
    } 
    else if (menu == 3) {
        hapus_data(fp, data_penduduk, jumlah_data);
    } 
    else {
        save_data(fp, data_penduduk, jumlah_data);
    }
}

int main(){
    //membuka file
    char filename[MAX_LEN];
    printf("Masukkan nama file: ");
    scanf("%s", filename);
    FILE * fp = fopen(filename, "r");
    
    //file tidak ditemukan
    while (!fp) {
        printf("File tidak ditemukan!\n\n");
        printf("Masukkan nama file: ");
        scanf("%s", filename);
        fp = fopen(filename,"r");
    }

    char line[MAX_LEN];
    fgets(line,MAX_LEN,fp);
    char rt[MAX_LEN];
    strcpy(rt,line);
    printf("\n");
    printf("Sistem Pencatatan Data Kependudukan %s\n",rt);

    //inisialisasi array
    fgets(line,MAX_LEN, fp);
    int jumlah_data = atoi(line);
    penduduk * data_penduduk = (penduduk*) malloc(jumlah_data*sizeof(penduduk));

    //pengisian array
    parsing(fp, data_penduduk, jumlah_data);
    menu_utama(fp, data_penduduk, jumlah_data);
    fclose(fp);
    free(data_penduduk);
    return 0;
}