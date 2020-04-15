#include <stdio.h>
#include <string.h>

typedef struct{
    char key[1000];
    char value[1000];
} s_ngram;

//dapet tabel namanya ngram dari thea

//Fungsi yang misahin sentence jadi array of strings, outputnya si AoS
void separate(int n, char sentence[100], char AoS[100][100]){
	
	int i, j, k;
	
	for (i=0; i <= (strlen(sentence)); i++){
		if (sentence[i] == ' '||sentence[i] == '\0'){
			AoS[j][k] = '\0';
			j++;
			k = 0;
		}
		else{
			AoS[j][k] = sentence[i];
			k++;
		}
	}
	
	AoS[n][strlen(AoS[n])-1] = '\0';
}

//Fungsi yang gabungin array of strings jadi output sentence of n words
void combine(int n, char AoS[100][100], char sentence[100]){

	int i, j, k;
	k=0;
	
	for (i=0; i<n; i++){
		for (j=0; j<(strlen(AoS[i])); j++){
			sentence[k] = AoS[i][j];
			k++;
			sentence[k] = '\0';
		}
		if (k<=(n-1)){
		sentence[k] = ' ';
		k++;
		sentence[k] = '\0';
		}
	}
	sentence[k] = '\0';
}

//Fungsi yang nyari sentence di dalam tabel ngram trus ngeprint valuenya
void nGrams(int n, char sentence[100], s_ngram ngram[1000]){
	
	int i,j;
	char tempArr[n][100];
	
	//ini mungkin hrs diganti pke while nanti krn gatau uk arraynya
	for (i=0; i<=5; i++){ 
//		printf("strcmp = %d", strcmp(word,(Tabel[i].key)));

		separate(n, sentence, tempArr);
		
		if ((strcmp(sentence,(ngram[i].key)))== 0){
			printf("%s ", ngram[i].value);
			for (j=1; j<n; j++){
				strcpy(tempArr[j-1], tempArr[j]);
				printf("%s2", tempArr[i]);
			}
			strcpy(tempArr[n], ngram[i].value);
			printf("%s2", tempArr[n]);
			
		}
		
		combine(n, tempArr, sentence);
		printf("%s3", sentence);
	}
	
}

//Main function
int main(){
	
	char cari[100];
	s_ngram ngram[10];
	int n = 3;
	
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
	
	printf("Mo nyari apa? ");
	scanf("%[^\n]%*c", &cari);
	
	nGrams(n, cari, ngram);
	
	return 0;
}


