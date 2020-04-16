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

//Prosedur untuk mengubah file eksternal yang berisi teks menjadi array of string
void textFile (char new[100])
{
	FILE * document;
	word text[3000];
	int kata = 0;
	
	document = fopen(new, "r");
	
	if (document != NULL)
	{
		while (!feof(document))
		{
			fscanf(document, "%s\n", text[kata].c);
			//printf("%s\n", text[kata].c); (untuk testing)
			kata++;
		}
	}
	//printf("%d",kata); (untuk testing)
	fclose(document);
}

/* Tes fungsi
int main()
{
	char doc[100];
	scanf("%s", doc);
	textFile(doc);
}
*/
