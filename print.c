#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char key[1000];
    char value[1000];
} s_ngram;

//Ini kekurangannya masih belom bisa kalo 2 value, trus kalo usernya mau jumlah katanya
//lebih dripada yang tersedia, kata terakhir bakal ngulang

void PrintnGrams(int n, int in, s_ngram ngram[1000]){
	
	int i, j, a, found, arrlength, indeks;
	char cari[100];
	int ifound;
	
	//Cari panjang array
	i = 0;
	while(ngram[i].key[0] != 0){
		arrlength = i;
		i = i+1;
	}
	
	printf("%d\n", arrlength);
	
	i = 0; j = 0; a = 1; found = 0;
	
	indeks = (rand() % (arrlength - 0 + 1)) + 0;
	
	strcpy(cari, ngram[0].key);
	printf("...%s ", cari);
	
	while ((a <= (in-n)) && (cari != NULL)){	
		for (i=0;i<=arrlength;i++){
			if ((strcmp(cari,(ngram[i].key))) == 0){
				printf("%s ", ngram[i].value);
			}
		}
		indeks = indeks+1;
		if (indeks > arrlength){
			indeks = 0;
		}
		strcpy(cari, ngram[indeks].key);
		a = a+1;
	}
	
	printf("...");
	
}

int main(){
	
	int in;
	int n = 3;
	
	s_ngram ngram[1000];
	
	//Ceritanya ini tabel referensi
	strcpy(ngram[0].key, "hmm bon cos");
	strcpy(ngram[0].value, "bgt");
	strcpy(ngram[1].key, "bon cos bgt");
	strcpy(ngram[1].value, "sih");
	strcpy(ngram[2].key, "cos bgt sih");
	strcpy(ngram[2].value, "lu");
	strcpy(ngram[3].key, "bgt sih lu");
	strcpy(ngram[3].value, "mon");
	strcpy(ngram[4].key, "sih lu mon");
	strcpy(ngram[4].value, "hiya");
	strcpy(ngram[5].key, "lu mon hiya");
	strcpy(ngram[5].value, "haha");
	strcpy(ngram[6].key, "mon hiya haha");
	strcpy(ngram[6].value, "tawa");
	strcpy(ngram[7].key, "hiya haha tawa");
	strcpy(ngram[7].value, "lu");
	
	printf("Mo brp kata? "); //Maks baru bisa 10 karena referensinya pendek

	scanf("%d", &in);

	PrintnGrams(n, in, ngram);
	
	return 0;
	
}
