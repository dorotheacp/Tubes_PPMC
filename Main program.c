
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    char key[100];
    char value[20];
} s_ngram;

typedef struct{
    char c[100];
} word;

int *arrsize;
int in;
int n;
char keluar;
int kk;
word text[2000000];
s_ngram ngram[2000000];
char doc[100];


//Prosedur untuk mengubah file eksternal yang berisi teks menjadi array of string
void textFile (char new[100], word text[2000000])
{
	FILE * document;
//	word text[3000];
	int kata = 0;
	int i,faiq=0;

	i=0; faiq = 0;

	document = fopen(new, "r");

	if (document != NULL)
	{
		while (!feof(document))
		{
			fscanf(document, "%s\n", text[kata].c);
//			printf("%s ", text[kata].c); //(untuk testing)
//			printf("%d\n", kata);
			kata++;
		}

		fprintf(document, '\0');
	}

	while (text[i].c[0] != 0){
		faiq = faiq+1;;
		i++;
	}
	arrsize = &faiq;

//	printf("%d", arrsize); //ini buat ngecek , hasilnya bener

	fclose(document);
}

// Fungsi untuk menentukan key
void determine_key(word text[2000000], int n, int jml_kata, s_ngram ngram[2000000]){
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
void determine_value(word text[2000000], int n, int jml_kata, s_ngram ngram[2000000]){
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

void PrintnGrams(int n, int in, s_ngram ngram[2000000]){

	int i, j, a, found, arrlength, indeks;
	char cari[100];
	int ifound[10];
	int icont;

	srand(time(NULL));

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
		printf("\n...");
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

	printf("...\n");
}

int main(){
    text[2000000].c[0] = 0;

    scanf("%s", doc);
    printf("Input ngram yang dimau:");
    scanf("%d", &n);

    textFile(doc, text);
    kk = *arrsize;

    determine_key(text, n, kk, ngram);
    determine_value(text, n, kk, ngram);

	printf("Mo brp kata? "); 

	scanf("%d", &in);

	PrintnGrams(n, in, ngram);
    printf("Masukkan K jika ingin keluar:\n");
    scanf("%c",&keluar);
    scanf("%c",&keluar);
    while(keluar != 'K')
    {
        printf("masukkan salah tekan K wey!\n");
        scanf("%c",&keluar);
        scanf("%c",&keluar);
    }
	return 0;

}
