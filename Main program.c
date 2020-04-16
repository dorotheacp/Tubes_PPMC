
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char key[1000];
    char value[1000];
} s_ngram;

typedef struct{
    char c[100];
} word;

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


//Ini kekurangannya masih belom bisa kalo 2 value, trus kalo usernya mau jumlah katanya
//lebih dripada yang tersedia, kata terakhir bakal ngulang

void PrintnGrams(int n, int in, s_ngram ngram[1000]){

	int i, j, a, found, arrlength, indeks;
	char cari[100];
	int ifound[10];
	int icont;

	//Cari panjang array
	i = 0;
	while(ngram[i].key[0] != 0){
		arrlength = i;
		i = i+1;
	}

//	printf("%d\n", arrlength); //ini ngecek aja

	i = 0; j = 0; a = 1;

	indeks = (rand() % (arrlength - 0 + 1)) + 0;

	strcpy(cari, ngram[indeks].key);

	if (indeks != 0){
		printf("...");
	}

	printf("%s ", cari);

	while ((a <= (in-n)) && (cari != NULL)){
		found = 0;
		j = 0;
		for (i=0;i<=arrlength;i++){
			if ((strcmp(cari,(ngram[i].key))) == 0){

				found = found+1;
				ifound[j] = i;
				j = j+1;
			}
		}

		if (found > 1){
			icont = (rand() % (found-1 - 0 + 1)) + 0;
			printf("%s ", ngram[(ifound[icont])].value);
		}
		else {//found == 1
			icont = 0;
			printf("%s ", ngram[(ifound[icont])].value);
		}

		indeks = ((ifound[icont])+1);
		if (indeks > arrlength){
			indeks = 0;
			icont = 0;
		}
		strcpy(cari, ngram[indeks].key);
		a = a+1;
	}

	printf("...");
}

int main(){

	int in;
	int n;

	s_ngram ngram[1000];
	word text[100] = {"nol", "satu", "dua", "tiga", "empat", "lima,",
                    "nol", "satu", "lagi","Faiq","Thea","Amel","Tasmon","Thea","Amel","jatuh","bangun","suatu","hari","aku","bangun","lalu","tidur",
                    "lalu","bangun","lagi","abistu","makan","nasi","abistu","makan","telor","ketika","makan","saya","dipanggil","oleh","ibu.","ibu","berkata:",
                    "nak","tolong","ambilkan","lontong","di","rumah","ibu","karena","hari","ini","bapak","ulang","tahun"};


    printf("Input ngram yang dimau:");
    scanf("%d", &n);

    determine_key(text, n, 53, ngram);
    determine_value(text, n, 53, ngram);

	printf("Mo brp kata? "); //Maks baru bisa 10 karena referensinya pendek

	scanf("%d", &in);

	PrintnGrams(n, in, ngram);

	return 0;

}
