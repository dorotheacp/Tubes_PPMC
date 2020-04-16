
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// Membuat struct yang diperlukan oleh fungsi dan prosedur
typedef struct{
    char key[100];
    char value[20];
} s_ngram;

typedef struct{
    char c[100];
} word;
// Menetapkan variabel global
int *arrsize;
char Pilihan;
int in;
int n;
char keluar;
int kk,lol=0;
word text[2000000];
s_ngram ngram[2000000];
char doc[100];


//Prosedur untuk mengubah file eksternal yang berisi teks menjadi array of string
void textFile (char new[100], word text[2000000])
{
	FILE * document;
    // Membuat variabel lokal untuk fungsi
	int kata = 0;
	int i,faiq=0;

	i=0; faiq = 0;

	document = fopen(new, "r"); // Menassign file ke variabel document

	if (document != NULL)//Melakukan validasi terhadap isi document
	{
		while (!feof(document))//Melakukan pembacaan isi document jika document tidak kosong
		{
		    //Pemindahan setiap kata pada dokumen ke dalam array of stirng text
			fscanf(document, "%s\n", text[kata].c);
			kata++; // Menambahkan jumlah kata pada array
		}

		fprintf(document, '\0');//Mengosongkan variabel document
	}
	else
    {
        // mencetak pada console jika tidak ditemukan nama file yang dimasukan oleh pengguna
        printf("File Tidak Ditemukan, Pastikan Alamat dan Nama File yang Anda Masukan Benar\n");
        arrsize = &faiq;//memasukan nilai variabel faiq kedalam pointer
        fclose(document);//menutup file yang digunakan
        return;//keluar dari fungsi
    }
    // Penentuan jumlah elemen pada array ini adalah rendundant pada sistem agar tidak terjadi kesalahan
	while (text[i].c[0] != 0){
		faiq = faiq+1;//penambahan variabel faiq yang akan digunakan sebagai jumlah elemen pada array
		i++;
	}
	arrsize = &faiq;//memasukkan nilai variabel faiq ke dalam pointe
	fclose(document);//penutup file yang digunakan
	return;//keluar dari fungsi
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
}

// Prosedur untuk mencetak tabel ngram
void PrintnGrams(int n, int in, s_ngram ngram[2000000]){

    //membuat variabel lokal pada prosedur
	int i, j, a, found, arrlength, indeks;
	char cari[100];
	int ifound[10];
	int icont;

	srand(time(NULL));//membuat sebuah bilangan random

	//Cari panjang array
	i = 0;
	while(ngram[i].key[0] != 0){
		arrlength = i;
		i = i+1;
	}

	i = 0; j = 0; a = 1;

	indeks = (rand() % (arrlength - 0 + 1)) + 0;//menentukan indeks pertama yang akan diprint secara random

	strcpy(cari, ngram[indeks].key);//memasukan elemen random pada ngram ke variabel cari

    //mencetak ... sebagai pembuka jika ditemukan indeks tidak 0
	if (indeks != 0){
		printf("\n...");
	}

	printf("%s ", cari); // mencetak kata-kata pertama

    //Mencetak kata kata selanjutnya sampai dengan n jumlah yang ditentukan oleh pengguna
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
        // Menentukan value mana yang harus di cetak jika terdapat banyak key yang ditemukan
		if (found > 1){
			icont = (rand() % (found-1 - 0 + 1)) + 0;//penentuan elemen pencetakan dilakukan secara random
			printf("%s ", ngram[(ifound[icont])].value);
		}
		else {//found == 1
			icont = 0;
			printf("%s ", ngram[(ifound[icont])].value);
		}

		indeks = ((ifound[icont])+1);
		//Mengulang lagi pembacaan indeks jika sudah melewati batas panjang array ngram
		if (indeks > arrlength){
			indeks = 0;
			icont = 0;
		}
		//membaca elemen selanjutnya
		strcpy(cari, ngram[indeks].key);
		//menambahkan ke jumlah kata yang telah dicetak
		a = a+1;
	}
    // menutuk pencetakan kata dengan .... dan enter
	printf("...\n");
}

int main(){
    text[2000000].c[0] = 0;

    printf("\t Selamat datang di Program N-gram \t\t\n");
    printf("\t    program ini dibuat oleh: \t\t\n");
    printf("\t    Rombongan D Kelompok 4 \t\t\n");
    printf("\t   Amelia Khoirurrahma  (18318003) \t\t\n");
    printf("\t   Dorothea Claresta P. (18318007) \t\t\n");
    printf("\t   Tasya Monika Saphira (18318018) \t\t\n");
    printf("\t   Muhammad Azhar Faiq (18318025) \t\t\n\n\n");
    printf("Dengan  Program  Anda  Memiliki  Kemampuan Untuk  Memilih File Teks \t\n");
    printf("Dan  Akan Menghasilkan Teks yang Mirip dengan Penulisan  File  yang \t\n");
    printf("Anda Pilih.  Pertama  Anda  Harus Memastikan Bahwa File  Teks  yang \t\n");
    printf("Akan Anda Gunakan Terdapat Pada Folder yang Sama Dengan Progam ini. \t\n");
    printf("Jika  Anda Belum Melakukan Itu Jangan Khawatir, Hanya Pastikan saja \t\n");
    printf("Bahwa Saat Anda Diperintahkan Memasukan File, Anda Masukan berserta \t\n");
    printf("Dengan  Alamat  Dimana File  Tersebut Diletakan  Di  Komputer  Anda \t\n\n");
    printf("\t Apakah Anda Siap Untuk Melanjutkan?  \t\n");
    printf("  Jika Siap Silahkan Tekan Y Jika tidak tekan yang Lain \t\n");
    scanf("%c",&Pilihan);

    while (Pilihan != 'Y'){
        scanf("%c",&Pilihan);
    }
    while(Pilihan != 'K'){
    system("cls");
    kk =0;
    printf("Silahkan Memasukan Nama File yang Ingin Anda Baca: \n");
    scanf("%s", doc);
    system("cls");
    textFile(doc, text);
    kk = *arrsize;
    while(kk == 0)
    {
        if(lol <=3)
        {
            printf("Silahkan Memasukan Kembali Nama File yang Ingin Anda Baca: \n");
            printf("Anda Memiliki %d Perobaan Tersisa\n",(3-lol));
            scanf("%s", doc);
            system("cls");
            textFile(doc, text);
            kk = *arrsize;
            lol = lol+1;
        }
        else if(lol == 3)
        {
            printf("Serius lah!Masukkan Nama File dan  \n");
            printf("Anda Memiliki %d Perobaan Tersisa\n",(3-lol));
            scanf("%s", doc);
            system("cls");
            textFile(doc, text);
            kk = *arrsize;
            lol = lol+1;
        }
        else if (lol >3)
        {
            system("cls");
            printf("Udahlah Filenya Gaada\n");
            printf("Silahkan Tekan Apa Aja Untuk Keluar\n");
            scanf("%c",&Pilihan);
            scanf("%c",&Pilihan);
            return 0;
        }

    }
    Pilihan = 'Y';
    printf("Sangat Disanrankan Untuk Menggunakan Nilai N Diantara 1 - 10 \n");
    printf("Untuk Mendapatkan Hasil yang Maksimum.\n");
    printf("Program Ini Hanya akan Menerima Masukan N Dibawah Nilai 10. Demi Keberjalanan Program. \n");
    printf("Silahkan Masukkan Jumlah N pada N-gram yang ingin anda gunakan:\n");
    scanf("%d", &n);
    while(n >=10)
    {
        printf("Program Ini Hanya akan Menerima Masukan N Dibawah Nilai 10. Demi Keberjalanan Program. \n");
        printf("Silahkan Masukkan Jumlah N pada N-gram yang ingin anda gunakan:\n");
        scanf("%d", &n);
    }
    determine_key(text, n, kk, ngram);
    determine_value(text, n, kk, ngram);
    system("cls");
     while(Pilihan == 'Y' || Pilihan == 'y')
    {
       	printf("Silahkan Memasukan Jumlah Kata yang Ingin Anda Tampilkan: ");
        scanf("%d", &in);
        PrintnGrams(n, in, ngram);
        printf("\n\n Apakah Anda Ingin Memasukan Jumlah Kata Kembali ?\n");
        printf("Tekan Y untuk jika ya, Tekan T Jika Tidak\n");
        scanf("%c",&Pilihan);
        scanf("%c",&Pilihan);
        system("cls");
    }
        printf("Apakah Anda Ingin Memasukan File Baru ?\n");
        printf("Tekan Y untuk jika ya, Tekan K Jika Anda Ingin Keluar\n");
        scanf("%c",&Pilihan);
        scanf("%c",&Pilihan);
        system("cls");
    }
    return 0;
}
