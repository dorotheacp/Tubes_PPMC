/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
*  MODUL 8 – TUGAS BESAR
*  Kelompok         : 4
*  Hari dan Tanggal : Rabu, 15 April 2020
*  Asisten (NIM)    : Devi Tara Avalokita (18316024)
*  Nama File        : keyvalue.c
*  Deskripsi        : 
*  1. Fungsi determine_key digunakan untuk membentuk array of key
*  2. Fungsi determine_value dugunakan untuk membentuk array of value
*/

#include <stdio.h>
#include <string.h>

typedef struct{
    char c[100];
} word;

typedef struct{
    char key[1000];
    char value[1000];
} s_ngram;

// Fungsi untuk menentukan key
void determine_key(word text[1000], int n, int jml_kata, s_ngram ngram[1000]){
    // input: array of word berisi text dari file eksternal, n yakni jumlah ngram, jml_kata yakni jumlah kata yang ada pada file eksternal
    // output: array of s_ngram untuk menyimpan key dan value

    int i, j;

    // iterasi sebanyak jumlah kata untuk menentukan key sampai kata terakhir
    for (i=0; i<jml_kata; i++){
        strcpy(ngram[i].key, text[i].c);
        for (j=0; j<n-1; j++){
            // jika belum sampai kata terakhir
            if (j+i+1<jml_kata){
                strcat(ngram[i].key, " ");
                strcat(ngram[i].key, text[i+j+1].c);
            }
        }
    }

    // iterasi untuk memasukkan kata dari awal lagi (setelah kata terakhir, ditambahkan kata pertama lagi dst)
    for (i=jml_kata-n+1; i<jml_kata; i++){
        for (j=0; j<i-(jml_kata-n+1)+1; j++){
            strcat(ngram[i].key, " ");
            strcat(ngram[i].key, text[j].c);
            
        }
    }

    // print key untuk ngetest fungsi
    /*
    for (i=0; i<jml_kata; i++){
        printf("%s\n", ngram[i].key);
    }
    */
}

// Fungsi untuk menentukan value
void determine_value(word text[1000], int n, int jml_kata, s_ngram ngram[1000]){
    // input: array of word berisi text dari file eksternal, n yakni jumlah ngram, jml_kata yakni jumlah kata yang ada pada file eksternal
    // output: array of s_ngram untuk menyimpan key dan value
    
    int i, j;

    for (i=0; i<jml_kata-n; i++){
        strcpy(ngram[i].value, text[i+n].c);
    }

    for (i=jml_kata-n; i<jml_kata; i++){
        strcpy(ngram[i].value, text[i-(jml_kata-n)].c);
    }

    // print value untuk ngetest fungsi
    /*for (i=0; i<jml_kata; i++){
        printf("%s\n", ngram[i].value);
    }
    */
}

// Program utama untuk ngetest kedua fungsi
/*int main(){
    int n, i;
    s_ngram ngram[1000];
    word text[13] = {"nol", "satu", "dua", "tiga", "empat", "lima,",
                    "nol", "satu", "lagi."};

    printf("Input ngram yang dimau:");
    scanf("%d", &n);

    determine_key(text, n, 9, ngram);
    determine_value(text, n, 9, ngram);

    printf("\n");
    for (i=0; i<9; i++){
        printf("%d \t %s \t %s\n", i, ngram[i].key, ngram[i].value);
    }
 
    return 0;
}
*/
