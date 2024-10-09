#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

typedef struct User{ // Dosya islemleri icin User sinifi olusturma.
    char name[20];
    char surname[20];
    char username[20];
    char password[20];
}User;

User users[20]; //users dizisiyle kullanicilari bir dizi icerisinde tutmus oluyoruz.
int userCounter=0;

//Hesap Olusturma Fonksiyonu
void hesapOlustur(void);

int girisYap(void);

//Hesap Olusturulurken daha once o isimde bir kullanici adi var mi kontrol eder.
int kullaniciAdiKontrol(char* kullaniciAdi);

// Hesap Olusturma Isleminden sonra dosyaya kaydeder.
void kullaniciBilgileriniDosyayaYaz(void);

// Text Formatinda verilmis haritalari Dinamik Bellek Olusturma Yontemine Gore Matris Olusturmaya Yarar
char** haritaDosyadanOku(char*, int*, int*);

//Olusturulan Harita Matrisini Yazdiran Fonksiyon
void haritaGetir(char**, int*, int*);

// Kullanicinin Bulundugu Konumun(X) X Lokasyonunu her adimda Guncellemek Icin Kullanılan Fonksiyon
int xLocation(char**,int*,int*);

// Kullanicinin Bulundugu Konumun(X) Y Lokasyonunu her adimda Guncellemek Icin Kullanılan Fonksiyon
int yLocation(char**,int*,int*);

// Her adimda toplanilan parcaciklari yazdiran fonksiyon
void parcacikYazdir(char*,int* parcacikSayisi);

// Oynu her adimda ilerletmemizi saglayan fonksiyon
void run(char**,char,int*,int*,char*,int*,int*,int*);

// Cikisa Girildiginde Elde Kalan Parcaciklara Gore Oyun Sonucunu Veren Fonksiyon
void parcacikKontrol(char*,int*);


int main() {
    char** harita; // harita matrisi
    int i,satir, sutun,x,y;
    char parcaciklar[30]; // parcaciklarin tutuldugu matris
    int parcacikSayisi=0,flag=0; // parcacikSayisi, kullanici adi ve sifrenin dogru olup olmadigini kontrol etmeye yarayan flag degiskeni
    char tus,secim='0',girisSecim='0',haritaSecim='0'; // tus: kullanicidan alinan, ilerlememizi saglayan degisken, secim ve girisSecimler ise menude ilerlememizi saglayan degiskenler.
    
    printf("Labirent Oyununa Hos Geldiniz! \n");
    
    do {
        // Oyun Menusu
        printf("**** MENU ****\n");
        printf("1. Oyuna Giris\n");
        printf("2. Oyun Nasil Oynanir?\n");
        printf("3. Oyundan Cikis\n");
        printf("Seciminizi yapiniz (1-3): ");
        scanf(" %c", &secim);
        
        switch (secim) {
            case '1':
                do{
                    // Hesap Olusturma-Login Menuleri
                    printf("1. Hesap Olustur\n2. Giris Yap\n3. Cikis\nSeciminizi yapin:\n");
                    scanf(" %c", &girisSecim);
                    switch (girisSecim) {
                        case '1':
                            hesapOlustur();
                            break;
                        case '2':
                           flag = girisYap();
                            if(flag==1){
                                //Harita Secme Kismi Her Bir harita icin if bloguna gore secim koydum. Sadece "filename" degisiyor. Baska hicbir degisiklik yok Ayni kodlar.
                                printf("1: 1.Harita\n2: 2.Harita\n3: 3.Harita\nSeciminizi yapin:\n");
                                scanf(" %c", &haritaSecim);
                                if(haritaSecim=='1'){
                                    harita = haritaDosyadanOku("harita1.txt", &satir, &sutun);
                                    haritaGetir(harita, &satir, &sutun);
                                    x = xLocation(harita, &satir, &sutun); // Kullanıcının X eksenindeki Konumu
                                    y = yLocation(harita, &satir, &sutun); // Kullanıcının Y eksenindeki Konumu
                                    
                                    for (i=30;i>0;i--) { // Geri Sayım
                                        printf("\nGeri Sayim:%d\n",i);
                                        printf("Lutfen Yukari Icin W Asagi icin S Sag icin D Sol icin A ya basiniz.\n ");
                                        tus = _getch();
                                        if (tus==27) // ESC ile Oyun Sonlandırma
                                        {
                                            printf("Oyundan Cikis Yapildi\n");
                                            Sleep(10000);
                                            exit(1);
                                        }
                                        else {
                                            printf("Bastiginiz ok tusu:%c\n",tus);
                                            run(harita,tus,&x,&y,parcaciklar,&satir,&sutun,&parcacikSayisi);
                                        }
                                    }
                                    printf("\nBOOOOM!\n");
                                    // Belleği serbest bırak
                                    for (i = 0; i < satir; i++) {
                                        free(harita[i]);
                                    }
                                    free(harita);
                                }
                                else if (haritaSecim=='2'){
                                        harita = haritaDosyadanOku("harita2.txt", &satir, &sutun);
                                        haritaGetir(harita, &satir, &sutun);
                                        x = xLocation(harita, &satir, &sutun); // Kullanıcının X eksenindeki Konumu
                                        y = yLocation(harita, &satir, &sutun); // Kullanıcının Y eksenindeki Konumu
                                        
                                        for (i=30;i>0;i--) { // Geri Sayım
                                            printf("\nGeri Sayim:%d\n",i);
                                            printf("Lutfen Yukari Icin W Asagi icin S Sag icin D Sol icin A ya basiniz.\n ");
                                            tus = _getch();
                                            if (tus==27) // ESC ile Oyun Sonlandırma
                                            {
                                                printf("Oyundan Cikis Yapildi\n");
                                                Sleep(10000);
                                                exit(1);
                                            }
                                            else {
                                                printf("Bastiginiz ok tusu:%c\n",tus);
                                                run(harita,tus,&x,&y,parcaciklar,&satir,&sutun,&parcacikSayisi);
                                            }
                                        }
                                        printf("\nBOOOOM!\n");
                                        // Belleği serbest bırak
                                        for (i = 0; i < satir; i++) {
                                            free(harita[i]);
                                        }
                                        free(harita);
                                    
                                }
                                else if(haritaSecim=='3'){
                                    
                                        harita = haritaDosyadanOku("harita3.txt", &satir, &sutun);
                                        haritaGetir(harita, &satir, &sutun);
                                        x = xLocation(harita, &satir, &sutun); // Kullanıcının X eksenindeki Konumu
                                        y = yLocation(harita, &satir, &sutun); // Kullanıcının Y eksenindeki Konumu
                                        
                                        for (i=30;i>0;i--) { // Geri Sayım
                                            printf("\nGeri Sayim:%d\n",i);
                                            printf("Lutfen Yukari Icin W Asagi icin S Sag icin D Sol icin A ya basiniz.\n ");
                                             tus = _getch();
                                            if (tus==27) // ESC ile Oyun Sonlandırma
                                            {
                                                printf("Oyundan Cikis Yapildi\n");
                                                 Sleep(10000);
                                                exit(1);
                                            }
                                            else {
                                                printf("Bastiginiz ok tusu:%c\n",tus);
                                                run(harita,tus,&x,&y,parcaciklar,&satir,&sutun,&parcacikSayisi);
                                            }
                                        }
                                        printf("\nBOOOOM!\n");
                                        // Belleği serbest bırak
                                        for (i = 0; i < satir; i++) {
                                            free(harita[i]);
                                        }
                                        free(harita);
                                    }
                            }
                            break;
                        case '3':
                            printf("Oyundan Cikiliyor...\n");
                            break;
                    }
                }while(girisSecim!='3');
                break;
                
            case '2':
                printf("Labirentte gezinmek icin WASD tuslari kullanilacaktir. Karadelikler uzerine gelinirse oyun sonlanir. Kullanici oyunda x ile gosterilmektedir.\n");
                printf("Duvarlara ve matris disina hamle yapildiginda kullanicinin yeri degismez. Istediginiz zaman ESC tusuyla oyundan cikis yapabilirsiniz.\n");
                printf("Karsit hidrojen uretebilmek icin labirentin cikisinda elinizde sadece p ve E parcaciklari bulunmalidir.\n Labirentin cikisi C ile gosterilmektedir.\n");
                printf("Iyi Oyunlar...\n");
                Sleep(30000);
                break;
            case '3':
            printf("Oyundan Cikis Yapildi\n");
            Sleep(1000);
            exit(1);
            break;
        }
    } while (secim=='1');
    return 0;
}

void hesapOlustur(void){
    printf("Isim: ");
    scanf("%s",users[userCounter].name);
    
    printf("Soy Isim: ");
    scanf("%s",users[userCounter].surname);
    do {
        printf("Kullanici Adi: ");
        scanf("%s",users[userCounter].username);
        
        if(kullaniciAdiKontrol(users[userCounter].username)){
            printf("Kullanici Adi zaten kullanilmakta. Yeni bir kullanici adi giriniz\n");
        }
    } while (kullaniciAdiKontrol(users[userCounter].username));
    
    
    printf("Sifre: ");
    scanf("%s", users[userCounter].password);

    userCounter++;

    printf("Hesap olusturuldu.\n");
    kullaniciBilgileriniDosyayaYaz();
}



int girisYap(void){
    char kullaniciAdi[20]; // daha once olusturulmus hesap varsa kullanicidan girmesini istiyorum
    char sifre[20]; // daha once olusturulmus hesap varsa kullanicidan girmesini istiyorum
    int i=0,flag=0; // flag kontrol etmemizi saglayan degisken
    
    FILE* dosya = fopen("kullanicilar.txt", "r");
        if (dosya == NULL) {
            printf("Dosya Acilamadi.\n");
            exit(1);
        }
    
    printf("Kullanici Adi: ");
    scanf("%s",kullaniciAdi);
    printf("Sifre:  ");
    scanf("%s",sifre);
    
   
    while (fscanf(dosya, "%s %s %s %s", users[i].name, users[i].surname, users[i].username, users[i].password) != EOF) {
            if (strcmp(kullaniciAdi, users[i].username) == 0 && strcmp(sifre, users[i].password) == 0) {
                printf("Giris basarili. Merhaba %s!\n", users[i].name);
                flag = 1;
                break;
            }
            i++;
        }
    fclose(dosya);
    
    if (flag == 0) {
            printf("Giris basarisiz. Kullanici adi veya sifre hatali.\n");
        }
    
    return flag;
}

int kullaniciAdiKontrol(char* kullaniciAdi){
    int i;
    for (i=0; i<userCounter; i++) {
        if(users[i].username == users[userCounter].username)
        return 1;
    }
    return 0;
}

void kullaniciBilgileriniDosyayaYaz(void){
    FILE* dosya = fopen("kullanicilar.txt", "a+");

       if (dosya == NULL) {
           printf("Dosya acilirken hata olustu.\n");
           exit(1);
       }

       for (int i = 0; i < userCounter; i++) {
           fprintf(dosya, "%s %s %s %s\n", users[i].name, users[i].surname, users[i].username, users[i].password);
       }

       fclose(dosya);
   }
    




char** haritaDosyadanOku(char* fileName, int* satir, int* sutun) {
    int i, j;
    FILE* fp = NULL;
    char** harita;
    char ch;

    *satir = 0;
    *sutun = 1;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Dosya Acilamadi.");
        exit(1);
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            (*satir)++;
        }
    }

    printf("Satir Sayisi %d\n", *satir);
    rewind(fp);

    while ((ch = fgetc(fp)) != EOF) {
        if (ch != ' ') {
            if (ch != '\n') {
                (*sutun)++;
            }
        }
    }

    *sutun = *sutun / *satir;
    printf("Sutun Sayisi %d\n", *sutun);

   

    harita = (char**)malloc(*satir * sizeof(char*));
    for (i = 0; i < *satir; i++) {
        harita[i] = (char*)malloc(*sutun * sizeof(char));
    }

    rewind(fp);

    for (i = 0; i < *satir; i++) {
        for (j = 0; j < *sutun; j++) {
            do {
                ch = fgetc(fp);
            } while (ch == ' ' || ch == '\n');
            harita[i][j] = ch;
        }
    }

    fclose(fp);

    return harita;
}

void haritaGetir(char** harita, int* satir, int* sutun) {
    int i, j;
    for (i = 0; i < *satir; i++) {
        printf("|");
        for (j = 0; j < *sutun; j++) {
            printf(" %c ", harita[i][j]);
        }
        printf("|");
        printf("\n");
    }
}

 int xLocation(char** harita,int* satir,int* sutun){
     int i,j,x=-1;
     for (i=0; i<*satir; i++) {
         j=0;
         while (harita[i][j]!= 'X' && j<*sutun) {
             j++;
         }
         if(j<*sutun){
             x=j;
             break;
         }
         
     }
     return x;
}

int yLocation(char** harita,int* satir,int* sutun){
    int i,j,y=-1;
    for (i=0; i<*satir; i++) {
        j=0;
        while (harita[i][j]!= 'X' && j<*sutun) {
            j++;
        }
        if(j<*sutun){
            y=i;
            break;
        }
        
    }
    return y;
}

void parcacikYazdir(char* parcaciklar,int* parcacikSayisi){
    int i,len;
    len = *parcacikSayisi;
    if(len>0){
        printf("Toplanan atom alti parcaciklar:\n");
        for (i=0; i<len; i++) {
            printf(" %c",parcaciklar[i]);
        }
    }
    else
        printf(" ");
}

void parcacikKontrol(char* parcaciklar,int* parcacikSayisi){
    int i,P=0,e=0,p=0,E=0; // P+, e-, p-, E+ sayılarını tutmak için değişkenler
    int score=0;
    
    for (i=0; i<*parcacikSayisi; i++) {
        if(parcaciklar[i]=='P'){
            P++;
        }
        else if (parcaciklar[i]=='e'){
            e++;
        }
    }
    
    if(P!=e){
        printf("Karsit Hidrojen Olusturulamadi!\n");
    }
    else{
        for (i=0; i<*parcacikSayisi; i++) {
            if(parcaciklar[i]=='p'){
                p++;
            }
            else if (parcaciklar[i]=='E'){
                E++;
            }
        }
    }
    
    if(p>E){
        printf("%d adet karsit madde uretildi\n",E);
        score = E*10;
        printf("Toplanilan Puan: %d\n",score);
    }
    else{
        printf("%d adet karsit madde uretildi\n",p);
        score = p*10;
        printf("Toplanilan Puan: %d\n",score);
    }
}



void run(char** harita, char tus, int* x, int* y, char* parcaciklar,int* satir,int* sutun,int* parcacikSayisi){
    int i=*parcacikSayisi;
    
    switch (tus) {
        case 'W':
        case 'w':
            if(harita[(*y)-1][*x]=='K'){
                harita[(*y)-1][*x]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
                printf("\nKaradelige dustunuz! Oyun Sonlandi!\n");
                Sleep(10000);
                exit(1);
            }
            else if (harita[(*y)-1][*x]=='C'){
                harita[(*y)-1][*x]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
                printf("\nCikisa Girdiniz. Oyundan Cikis Yapiliyor....\n");
                parcacikKontrol(parcaciklar, parcacikSayisi);
                 Sleep(10000);
                exit(1);
            }
            else if ((*y)-1<0 || harita[(*y)-1][*x] =='1'){
                printf("Gecersiz Hareket! Konumunuz Degismedi!\n");
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            else if(harita[(*y)-1][*x]=='0'){
                harita[(*y)-1][*x]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            else{
                parcaciklar[i]=harita[(*y)-1][*x];
                i++;
                *parcacikSayisi=i;
                harita[(*y)-1][*x]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            
            break;
            
        case 'A':
        case 'a':
            if(harita[(*y)][*x-1]=='K'){
                harita[*y][(*x)-1]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
                printf("\nKaradelige dustunuz! Oyun Sonlandi!\n");
                 Sleep(10000);
                exit(1);
            }
            else if (harita[*y][(*x)-1]=='C'){
                harita[*y][(*x)-1]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
                printf("\nCikisa Girdiniz. Oyundan Cikis Yapiliyor....\n");
                parcacikKontrol(parcaciklar, parcacikSayisi);
                Sleep(10000);
                exit(1);
            }
            else if ((*x)-1<0 || harita[*y][(*x)-1] =='1'){
                printf("Gecersiz Hareket! Konumunuz Degismedi!\n");
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            else if(harita[*y][(*x)-1]=='0'){
                harita[*y][(*x)-1]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            else{
                parcaciklar[i]=harita[*y][(*x)-1];
                i++;
                *parcacikSayisi=i;
                harita[*y][(*x)-1]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            break;
            
        case 'S':
        case 's':
            if(harita[(*y)+1][*x]=='K'){
                harita[(*y)+1][*x]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
                printf("\nKaradelige dustunuz! Oyun Sonlandi!\n");
                Sleep(10000);
                exit(1);
            }
            else if (harita[(*y)+1][*x]=='C'){
                harita[(*y)+1][*x]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
                printf("\nCikisa Girdiniz. Oyundan Cikis Yapiliyor....\n");
                parcacikKontrol(parcaciklar, parcacikSayisi);
                 Sleep(10000);
                exit(1);
            }
            else if ((*y)+1<0 || harita[(*y)+1][*x] =='1'){
                printf("Gecersiz Hareket! Konumunuz Degismedi!\n");
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            else if(harita[(*y)+1][*x]=='0'){
                harita[(*y)+1][*x]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            else{
                parcaciklar[i]=harita[(*y)+1][*x];
                i++;
                *parcacikSayisi=i;
                harita[(*y)+1][*x]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            break;
            
        case 'D':
        case 'd':
            if(harita[*y][(*x)+1]=='K'){
                harita[*y][(*x)+1]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
                printf("\nKaradelige dustunuz! Oyun Sonlandi!\n");
                Sleep(10000);
                exit(1);
            }
            else if (harita[*y][(*x)+1]=='C'){
                harita[*y][(*x)+1]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
                printf("\nCikisa Girdiniz. Oyundan Cikis Yapiliyor....\n");
                parcacikKontrol(parcaciklar, parcacikSayisi);
                Sleep(10000);
                exit(1);
            }
            else if ((*x)+1<0 || harita[*y][(*x)+1] =='1'){
                printf("Gecersiz Hareket! Konumunuz Degismedi!\n");
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            else if(harita[*y][(*x)+1]=='0'){
                harita[*y][(*x)+1]='X';
                harita[*y][*x]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            else{
                parcaciklar[i]=harita[*y][(*x)+1];
                i++;
                *parcacikSayisi=i;
                harita[*y][(*x)+1]='X';
                harita[*y][(*x)]='0';
                haritaGetir(harita, satir, sutun);
                parcacikYazdir(parcaciklar,parcacikSayisi);
                *x = xLocation(harita, satir, sutun);
                *y = yLocation(harita, satir, sutun);
            }
            break;
            
        default:
            printf("Gecersiz Tusa Bastiniz!\n");
            break;
    }
}


