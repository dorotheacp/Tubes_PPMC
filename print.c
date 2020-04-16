#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char key[1000];
    char value[1000];
} s_ngram;

//udah bener amin

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
	strcpy(ngram[7].value, "sih");
	strcpy(ngram[8].key, "haha tawa sih");
	strcpy(ngram[8].value, "lu");
	strcpy(ngram[9].key, "tawa sih lu");
	strcpy(ngram[9].value, "mon");
	strcpy(ngram[10].key, "sih lu mon");
	strcpy(ngram[10].value, "wkwk");
	strcpy(ngram[11].key, "lu mon wkwk");
	strcpy(ngram[11].value, "hmm");
	strcpy(ngram[12].key, "mon wkwk hmm");
	strcpy(ngram[12].value, "bon");
	strcpy(ngram[13].key, "wkwk hmm bon");
	strcpy(ngram[13].value, "cos");	
	
	printf("Mo brp kata? ");

	scanf("%d", &in);
	
	PrintnGrams(3, in, ngram);
	
	return 0;
	
}
