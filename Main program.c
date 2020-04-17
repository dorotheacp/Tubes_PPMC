
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
    //mengosongkan variabel pada array text
    text[2000000].c[0] = 0;
    //mencetak menu serta penjelasan tentang program ini
    printf("\t Selamat datang di Program N-gram \t\t\n");
    printf("\t    program ini dibuat oleh: \t\t\n");
    printf("\t    Rombongan D Kelompok 4 \t\t\n");
    printf("\t  Amelia Khoirurrahma  (18318003) \t\t\n");
    printf("\t  Dorothea Claresta P. (18318007) \t\t\n");
    printf("\t  Tasya Monika Saphira (18318018) \t\t\n");
    printf("\t  Muhammad Azhar Faiq  (18318025) \t\t\n\n\n");
    printf("Dengan  Program  Anda  Memiliki  Kemampuan Untuk  Memilih File Teks \t\n");
    printf("Dan  Akan Menghasilkan Teks yang Mirip dengan Penulisan  File  yang \t\n");
    printf("Anda Pilih.  Pertama  Anda  Harus Memastikan Bahwa File  Teks  yang \t\n");
    printf("Akan Anda Gunakan Terdapat Pada Folder yang Sama Dengan Progam ini. \t\n");
    printf("Jika  Anda Belum Melakukan Itu Jangan Khawatir, Hanya Pastikan saja \t\n");
    printf("Bahwa Saat Anda Diperintahkan Memasukan File, Anda Masukan berserta \t\n");
    printf("Dengan  Alamat  Dimana File  Tersebut Diletakan  Di  Komputer  Anda \t\n\n");
    printf("\t Apakah Anda Siap Untuk Melanjutkan?  \t\n");
    //memastikan bahwa pengguna sudah mengerti dengan deskripsi dan siap menggunakan program
    printf("  Jika Siap Silahkan Tekan Y Jika tidak tekan yang Lain \t\n");
    scanf("%c",&Pilihan);
    // looping sampai pengguna memasukan Y
    while (Pilihan != 'Y'){
        scanf("%c",&Pilihan);
    }
    //Memulai loop program utama
    while(Pilihan != 'K'){ // program akan berenti jika variabel pilihan bernilai K
    memset(text,0,sizeof(text));
    memset(ngram,0,sizeof(ngram));
    system("cls");//menghapus pesan pesan sebelumnya pada console
    kk =0;          //menginisiasi dan mereset nilai kk agar bernilai 0
    printf("Silahkan Memasukan Nama File yang Ingin Anda Baca: \n");
    scanf("%s", doc); //membaca file nama file yang akan digunakan
    system("cls");
    textFile(doc, text); //menggunakan fungsi textfile untuk menghasilkan array kata
    kk = *arrsize; //mengassign kk dengan jumlah kata pada array
    printf("%d\n",kk);
    //melakukan validasi pada jumlah kk dan memastikan bahwa file ada
    while(kk == 0)
    {
        if(lol <=3) //loop ditetapkan untuk hanya berulang sebanykan 3 kali jika pengguna bercanda
        {
            printf("Silahkan Memasukan Kembali Nama File yang Ingin Anda Baca: \n");
            printf("Anda Memiliki %d Percobaan Tersisa\n",(3-lol));
            scanf("%s", doc); //membaca kembali nama file yang dimasukan oleh pengguna
            system("cls");
            textFile(doc, text); //menggunakan fungsi textFIle kembali untuk membuat array of kata kembali
            kk = *arrsize;
            lol = lol+1; //mengurangi jumlah kesempatan mencoba pengguna
        }
        else if(lol == 3)//peringatan kembali kepada pengguna untuk memasukan nama file dengan benar
        {
            printf("Serius lah!Masukkan Nama File dengan benar  \n");
            printf("Anda Memiliki %d Percobaan Tersisa\n",(3-lol));
            scanf("%s", doc);//membaca kembali nama file yang dimasukan oleh pengguna
            system("cls");
            textFile(doc, text);//menggunakan fungsi textFIle kembali untuk membuat array of kata kembali
            kk = *arrsize;
            lol = lol+1; //mengurangi jumlah kesempatan mencoba pengguna
        }
        else if (lol >3) // jika pengguna sudah melebihi kesempatan yang diberikan
        {
            //pengguna terpaksa harus keluar dari program
            system("cls");
            printf("Udahlah Filenya Gaada\n");
            printf("Silahkan Tekan Apa Aja Untuk Keluar\n");
            scanf("%c",&Pilihan);
            scanf("%c",&Pilihan);
            return 0;
        }

    }
    //menetapkan pilihan kembali ke Y
    Pilihan = 'Y';
    //mencetak penjelasan tentang batasan dan anjuran penggunaan program
    printf("Sangat Disarankan Untuk Menggunakan Nilai N Diantara 1 - 9 \n");
    printf("Untuk Mendapatkan Hasil yang Maksimum.\n");
    printf("Program Ini Hanya akan Menerima Masukan N Dibawah Nilai 9 dan Diatas 1. Demi Keberjalanan Program. \n");
    printf("Silahkan Masukkan Jumlah N pada N-gram yang ingin anda gunakan:\n");
    //memasukan jumlah n yang akan digunakan pada n-gram
    scanf("%d", &n);
    //melakukan validasi pada masukan dan memastikan bahwa n bernilai dibawah 10
    while(n >=10 || n < 1)
    {
        printf("Program Ini Hanya akan Menerima Masukan N Dibawah Nilai 9 dan Diatas 1. Demi Keberjalanan Program. \n");
        printf("Silahkan Masukkan Jumlah N pada N-gram yang ingin anda gunakan:\n");
        scanf("%d", &n); //memasukan kembali nilai n yang baru
    }
    //menjalankan fungsi determine_key untuk memasukan key ke array dan fungsi determine_value untuk memasukan value ke key yang cocok
    determine_key(text, n, kk, ngram);
    determine_value(text, n, kk, ngram);
    system("cls");
    //melalukan loop untuk mencetak hasil n-grram
     while(Pilihan == 'Y' || Pilihan == 'y')
    {
       	printf("Silahkan Memasukan Jumlah Kata yang Ingin Anda Tampilkan: ");
        scanf("%d", &in);//membaca jumlah kata yang ingin dicetak
        while(in < n )
        {
            printf("Masukkan Anda Salah Jumlah Kata Harus Melebihi atau Sama Dengan N yang digunakan\n");
            scanf("%d", &in);
        }
        PrintnGrams(n, in, ngram); //mencetak ngram dengan fungsi printnGrams
        printf("\n\n Apakah Anda Ingin Memasukan Jumlah Kata Kembali ?\n");
        printf("Tekan Y untuk jika ya, Tekan T Jika Tidak\n");
        //memasukan pilihan pengguna apakah ingin memasukan jumlah kata kembali atau tidak
        scanf("%c",&Pilihan);
        scanf("%c",&Pilihan);
        system("cls");
    }
        //memasukan pilihan pengguna apakah ingin keluar dari program atau memasukan nama file lain
        printf("Apakah Anda Ingin Memasukan File Baru ?\n");
        printf("Tekan Y untuk jika ya, Tekan K Jika Anda Ingin Keluar\n");
        scanf("%c",&Pilihan);
        scanf("%c",&Pilihan);
        system("cls");
    }
    return 0;
}
