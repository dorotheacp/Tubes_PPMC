//INI MASIH MAU DISELESAIKAN

#include <stdio.h>
#include <string.h>

//Input : namaFileEksternal.txt
//Output : struct of array kata dan jumlah kata

typedef struct {
	char c[100];
} word;

//Prosedur untuk mengubah file eksternal yang berisi teks menjadi array of string
void textFile (char new[100])
{
}

//Prosedur untuk menghitung jumlah kata pada file
void hitungKata(char new[100]){
	int kata, huruf;
	FILE * document;
	char ch;
	
	document = fopen(new, "r");
	
	if (document == NULL){
		kata = 0;
	}
	
	else{
		kata = 0;
		while((ch = fgetc(document)) != EOF){
			huruf++;
			
			if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
				kata++;
		}
		if (huruf>0){
			kata++;
		}
	}
	fclose(document);
	
}

/* Tes fungsi
int main()
{
	char doc[100];
	scanf("%s", doc);
	hitungKata(doc);
	printf("jumlah kata: %d", kata);
}
*/
