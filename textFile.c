/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
*  MODUL 8 – TUGAS BESAR
*  Kelompok         : 4
*  Hari/Tanggal     : Kamis, 16 April 2020
*  Asisten	    : Devi Tara Avalokita (18316024)
*  Nama File        : textFile.c
*  Deskripsi        : 
*  1. textFile untuk menginput kata dari file eksternal ke dalam array of words dan
*     menghitung jumlah kata yang ada di dalam file eksternal
*/

#include <stdio.h>
#include <string.h>

//Input : namaFileEksternal.txt
//Output : array of words dan jumlah kata

//Struct of word
typedef struct {
	char c[100];
} word;

//Prosedur untuk mengubah file eksternal yang berisi teks menjadi array of words
//dan menghitung jumlah kata
void textFile (char new[100], word text[5000])
{
	FILE * document;
	int kata, i, faiq = 0;
	
	document = fopen(new, "r");
	
	if (document != NULL)
	{
		while (!feof(document))
		{
			fscanf(document, "%s\n", text[kata].c);
			kata++;
		}
		fprintf(document, '\0');
	}
	
	while (text[i].c[0] != 0){
		faiq = faiq+1;
		i++;
	}
	arrsize = &faiq;

//	printf("%d", arrsize); //ini buat ngecek , hasilnya bener
	fclose(document);
}

/* Tes fungsi
int main()
{
	int jml_kata;
	word text[5000];

	text[5000].c[0] = 0;

	char doc[100];
	scanf("%s", doc);

	textFile(doc, text);
	jml_kata = *arrsize;

	printf("%d",jml_kata);
}
*/
