#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>



void listele(void);
void sinif(void);
void ogrenciekle(void);

FILE *dosya,*yedek;
int kisisayisi;

struct ogrenci
{
    char ad[15];
    char soyad[15];
    int ogr_no;
    int ogr_turu;
    int sira; // kayit sirasi
};
struct ogrenci bilgi[999];

int main()
{
    system("cls");
    //  printf("\nprogrami baslatmak icin bir tusa basiniz.");
    // getch();
    listele(); // bu fonksiyonun icinde kullanicinin istegine gore sinif ya da ogrenciekle fonksiyonu cagiriliyor.


    return 0;
}
void listele(void)
{
    double baslangic,son;  //fonksiyonun zamanini yazdirmak icin tanimladigimiz degiskenler.
    baslangic=clock();

    int i=0;
    char no[15]; // duzenlenmemis listede butun numaralar int deger olmadigi icin ilk basta ogrenci numarasini char ile aliyoruz.
    dosya=fopen("ogrenci_kayit_bilgileri.txt","r"); // duzenlenmemis dosyayi sadece okumak icin aciyoruz.
    if(dosya==NULL) // dosyanin bos olma durumunu kontrol ediyoruz.
    {
        puts("Dosya acilamadi!");
        exit(1);
    }
///----DOSYADAKI VERILERI OKURKEN AYNI ZAMANDA NUMARASI OLMAYANLARA NUMARA ATIYORUZ-------


// http://cprogramarsivi.blogspot.com.tr/2015/04/c-dosyalama-ogrenci-kayd.html
    while(!feof(dosya))
    {
        fscanf(dosya,"%s %s %s %d %d",no,bilgi[i].ad,bilgi[i].soyad,&bilgi[i].sira,&bilgi[i].ogr_turu);
        bilgi[i].ogr_no=atoi(no); // bu atama sirasinda soldaki veri sayi degilse,0 ataniyor.(bunu deneme yaparken fark ettik)
        //atoi() integer a donusturme fonksiyonu.
        if(bilgi[i].ogr_no==0)
        {
            bilgi[i].ogr_no=((100000*17)+(1000*bilgi[i].ogr_turu)+bilgi[i].sira);
        }
        // printf("%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
        i++;
    }
// suan i degeri dosyadaki ogrenci sayisina esittir.
    printf("\n+Numarasi olmayanlara numara atanmistir.");
    printf("\n+Birden fazla ismi gecen kayitlar silinmistir.\n");
    printf("+Silinen kayitlar:\n");
    int m,n,k,j;


///----------TEKRARLI ISIMLERI SILLIYORUZ VE SILINEN ISIMLERI ADEDINCE YAZDIRIYORUZ------------
//http://www.c4learn.com/c-programs/to-delete-duplicate-elements-in-array.html
// basit bir dizi elemani silmek gibi dusunup,kosulumuzu herhangi iki ismin ve soyadin esit olmasi seklinde belirtip silmeyi gerceklestirdik.

    for(m=0; m<i; m++)
    {
        for(n=m+1; n<i;)
        {
            if(strcmp(bilgi[n].ad,bilgi[m].ad)==0 &&strcmp(bilgi[n].soyad,bilgi[m].soyad)==0 )
            {
                printf(" -%s %s\n",bilgi[n].ad,bilgi[n].soyad); //silicecek isimleri yazdiriyoruz.
                for(k=n; k<i; k++)
                {
                    bilgi[k].ogr_no=bilgi[k+1].ogr_no;
                    strcpy(bilgi[k].ad,bilgi[k+1].ad);
                    strcpy(bilgi[k].soyad,bilgi[k+1].soyad);
                    bilgi[k].ogr_turu=bilgi[k+1].ogr_turu;
                    bilgi[k].sira=bilgi[k+1].sira;
                }
                i--; //her eleman silindikten sonra kisi sayimiz 1 azaliyor
            }
            else n++;

        }
    }
    i--;
    kisisayisi=i;
///------------NUMARAYA GORE SIRALAMA YAPIYORUZ---------------------------
    printf("\n+Ogrenciler numaralarina gore siralanmistir.");
    int g_no=0; //gecici no
    char g_ad[15];  //gecici ad
    char g_soyad[15]; //gecici soyad
    int g_oTuru;    // gecici ogrenim turu
    int g_sira; // gecici kayit sirasi

//basit bir dizi elemanlari siralama gibi dusunduk.

    for(k=0; k<i-1; k++)
    {
        for(j=k+1; j<i; j++)
        {
            if(bilgi[k].ogr_no>bilgi[j].ogr_no)
            {
                /// no icin
                g_no =bilgi[k].ogr_no;
                bilgi[k].ogr_no=bilgi[j].ogr_no;
                bilgi[j].ogr_no= g_no;
                /// isim icin
                strcpy(g_ad,bilgi[k].ad);
                strcpy(bilgi[k].ad,bilgi[j].ad);
                strcpy(bilgi[j].ad,g_ad);
                /// soyad icin
                strcpy(g_soyad,bilgi[k].soyad);
                strcpy(bilgi[k].soyad,bilgi[j].soyad);
                strcpy(bilgi[j].soyad,g_soyad);
                /// kayit sirasi icin
                g_sira =bilgi[k].sira;
                bilgi[k].sira=bilgi[j].sira;
                bilgi[j].sira= g_sira;
                /// ogrenim turu icin
                g_oTuru=bilgi[k].ogr_turu;
                bilgi[k].ogr_turu=bilgi[j].ogr_turu;
                bilgi[j].ogr_turu=g_oTuru;
            }
        }
    }

    printf("\n");
///----------duzenledigimiz guncel listeyi yedek dosyamiza yazdiriyoruz.---------------------
    dosya=fopen("yedek.txt","w+");
    for (m=0; m<i; m++)
    {
        fprintf(dosya,"%d %s %s %d %d \n",bilgi[m].ogr_no,bilgi[m].ad,bilgi[m].soyad,bilgi[m].sira,bilgi[m].ogr_turu);

        //  printf("%d %s %s %d %d \n",bilgi[m].ogr_no,bilgi[m].ad,bilgi[m].soyad,bilgi[m].sira,bilgi[m].ogr_turu);

    }
    printf("+Dosya yenilenmistir.");
    fclose(dosya);
    ///---------1. ogretim ve 2. ogretim ogrencilerin sayilarini ekrana yazdiriyoruz.---------------
    int ogr1=0,ogr2=0; // sayac icin degiskenler
    for(m=0; m<i; m++)
    {
        if(bilgi[m].ogr_turu==1) ogr1++;
        else ogr2++;
    }

    printf("\n\nBirinci ogretim sayisi: %d",ogr1);
    printf("\nIkinci ogretim sayisi: %d",ogr2);

    son=clock();
    double zaman=son-baslangic;

    printf("\n----Siniflandirma fonksiyonunda gecen sure: %.2lf----",zaman);
    printf("\nOgrenci eklemek icin: 1'e, sinif ayrimi icin 2'ye basiniz:");
    int secim;
    //continue yu arastirirken goto yu ogrendik ve birkac yerde kullandik.
tekrar:
    scanf("%d",&secim);
    if(secim!=1&&secim!=2)
    {
        printf("\nLutfen tekrar giriniz:");
        goto tekrar;
    }


    if(secim==1)
    {
        ogrenciekle();

    }
    else if(secim==2) sinif();
}


void sinif()
{
    FILE *dosya;
    double baslangic,son,zaman;
    baslangic=clock();

    /// Kullanicidan sinif sayisini ve bu siniflarin kapasite bilgisini aliyoruz

    int ss,i,j,gecici; //ss=sinif sayisi
    printf("\nsinif sayisini giriniz: ");
    scanf("%d",&ss);

    int dizi[ss];
    for(i=0; i<ss; i++)
    {
        printf("%d.sinifin kapasitesini giriniz:",i+1);
        scanf("%d",&dizi[i]);
    }

    /// Kapasiteyi buyukten kucuge siraliyoruz

    for( i=0; i<ss-1; i++)
    {
        for( j=i+1; j<ss; j++)
        {
            if(dizi[i] <dizi[j])
            {
                gecici = dizi[i];
                dizi[i] = dizi[j];
                dizi[j] = gecici;
            }
        }
    }

    char text1[] = "ogr1sinifX.txt";
    char text2[] = "ogr2sinifX.txt";
    int secim;
    printf("\n en az sinif dagilimi icin:1,  esit dagilim icin 2 ye basiniz: ");
devammm:
    scanf("%d",&secim);

    if(secim==1)
    {
        int say1=0,say2=0,sinifbir=0,sinifiki=0;
        for(i=0; i<kisisayisi; i++)
        {
            if(bilgi[i].ogr_turu==1)
            {
                text1[9]=(sinifbir+1)+'0';
                if(say1==dizi[sinifbir]-1) //sayac kapasiteye esit oldugu zaman bir sonraki sinifa yazmaya basliyoruz.
                {
                    say1=0; // yeni sinif icin sayaci sifirliyoruz.
                    sinifbir++;
                    text1[9]=sinifbir+'0';
                    dosya=fopen(text1,"a+");
                    fprintf(dosya,"%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
                    fclose(dosya);
                    continue;
                }
                dosya=fopen(text1,"a+");
                fprintf(dosya,"%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
                fclose(dosya);
                say1++;

            }
            if(bilgi[i].ogr_turu==2)
            {
                text2[9]=(sinifiki+1)+'0';
                if(say2==dizi[sinifiki]-1)
                {
                    say2=0;
                    sinifiki++;
                    text2[9]=sinifiki+'0';
                    dosya=fopen(text2,"a+");
                    fprintf(dosya,"%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
                    fclose(dosya);
                    continue;

                }
                dosya=fopen(text2,"a+");
                fprintf(dosya,"%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
                fclose(dosya);
                say2++;

            }
        }
    }
    else if(secim==2)
    {
        int say1=0,say2=0,top1,top2;

        //   int sinifbir=say1%ss,sinifiki=say2%ss;
        int sinifbir,sinifiki;
        for(i=0; i<kisisayisi; i++)
        {

            if(bilgi[i].ogr_turu==1)
            {
                sinifbir=say1%ss;
                top1=say1/ss;
                text1[9]=(sinifbir+1)+'0';
                if(top1>=dizi[sinifbir])
                {
                    say1=0;

                    continue;
                }

                dosya=fopen(text1,"a+");
                fprintf(dosya,"%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
                fclose(dosya);
                say1++;
            }

            if(bilgi[i].ogr_turu==2)
            {
                sinifiki=say2%ss;
                top2=say2/ss;
                text2[9]=(sinifiki+1)+'0';
                if(top2>=dizi[sinifiki])
                {
                    say2=0;
                    continue;
                }

                dosya=fopen(text2,"a+");
                fprintf(dosya,"%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
                fclose(dosya);
                say2++;


            }

        }

    }
    else
    {

        printf("\nHatali giris yaptiniz.");
        goto devammm;
    }

    son=clock();
    zaman=son-baslangic;

    printf("\n----Sinif fonksiyonunda gecen zaman:%.2lf ----",zaman);
devamm:
    puts("\ncikmak icin 0'a,devam etmek icin 1'e basiniz.");
    switch(getch())
    {
    case '0':
    {
        break;
    }
    case '1':
    {
        main();
        break;
    }
    default:
    {
        printf("\nhatali girdiniz:");
        goto devamm;
    }
    }

}


void ogrenciekle()
{
    double baslangic,son,zaman;
    baslangic=clock();

    char name[10];
    char last_name[15];
    int number,kind,list;
    printf("\nOgrencinin adini giriniz: ");
    scanf("%s",name);
    printf("\nOgrencinin soyadini giriniz: ");
    scanf("%s",last_name);

    int m;
    for(m=0; m<kisisayisi; m++)
    {
        if(strcmp(name,bilgi[m].ad)==0 &&strcmp(last_name,bilgi[m].soyad)==0 ) //listele fonksiyonunda yaptigimiz kontrolun aynisi.
        {

            printf("\nBu ogrenci zaten bulunmaktadir.");
            ogrenciekle();
        }
    }
tekrar:
    printf("\nOgrencinin ogrenim turunu giriniz: ");
    scanf("%d",&kind);
    if(kind<1|| kind>2)
    {
        printf("\nogrenim turunu yanlis girdiniz.");
        goto tekrar;
    }
tekrar2:
    printf("\nKayit sirasini giriniz:");
    scanf("%d",&list);

    number=(100000*17+(1000*kind)+list);
    for(m=0; m<kisisayisi; m++)
    {
        if(bilgi[m].ogr_no==number)
        {
            printf("\nOgrenci numarasi cakismaktadir.");
            goto tekrar2;
        }
    }

    FILE *dosya;
    dosya=fopen("ogrenci_kayit_bilgileri.txt","a+"); //dosyayi ilave seklinde aciyoruz.
    fprintf(dosya,"%d %s %s %d %d\n",number,name,last_name,list,kind);
    fclose(dosya);
    son=clock();
    zaman=son-baslangic;

    printf("\n----Sinif fonksiyonunda gecen zaman:%.2lf ----",zaman);
    puts("\ndevam etmek icin tusa basiniz:");
    getch();

    listele();

}
