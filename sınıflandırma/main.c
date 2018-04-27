#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>


void listele(void);
void sinif(void);
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
void listele(void);

int main()
{
    listele();
    sinif();
    // kayitGirisi();
    // siniflandir();
    getch();
    return 0;
}
void listele(void)
{
    double baslangic,son;
    baslangic=clock();

    int i=0;
    char no[15];
    dosya=fopen("test.txt","r");
    if(dosya==NULL)
    {
        puts("Dosya acilamadi!");
        exit(1);
    }



    while(!feof(dosya))
    {
        fscanf(dosya,"%s %s %s %d %d",no,bilgi[i].ad,bilgi[i].soyad,&bilgi[i].sira,&bilgi[i].ogr_turu);
        bilgi[i].ogr_no=atoi(no);
        if(bilgi[i].ogr_no==0)
        {
            bilgi[i].ogr_no=(100000*(2017%2000)+(1000*bilgi[i].ogr_turu)+bilgi[i].sira);
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

    for(m=0; m<i; m++)
    {
        for(n=m+1; n<i;)
        {
            if(strcmp(bilgi[n].ad,bilgi[m].ad)==0 &&strcmp(bilgi[n].soyad,bilgi[m].soyad)==0 )
            {
                printf(" -%s %s\n",bilgi[n].ad,bilgi[n].soyad);
                for(k=n; k<i; k++)
                {
                    bilgi[k].ogr_no=bilgi[k+1].ogr_no;
                    strcpy(bilgi[k].ad,bilgi[k+1].ad);
                    strcpy(bilgi[k].soyad,bilgi[k+1].soyad);
                    bilgi[k].ogr_turu=bilgi[k+1].ogr_turu;
                    bilgi[k].sira=bilgi[k+1].sira;
                }
                i--;
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

    dosya=fopen("yedek.txt","w+");
    for (m=0; m<i; m++)
    {
        fprintf(dosya,"%d %s %s %d %d \n",bilgi[m].ogr_no,bilgi[m].ad,bilgi[m].soyad,bilgi[m].sira,bilgi[m].ogr_turu);

        //  printf("%d %s %s %d %d \n",bilgi[m].ogr_no,bilgi[m].ad,bilgi[m].soyad,bilgi[m].sira,bilgi[m].ogr_turu);

    }
    printf("+Dosya yenilenmistir.");
    fclose(dosya);
    int ogr1=0,ogr2=0; // sayac icin degiskenler
    for(m=0; m<i; m++)
    {
        if(bilgi[m].ogr_turu==1) ogr1++;  // ogrenim turu dagilimi
        else ogr2++;
    }
    printf("\n\nBirinci ogretim sayisi: %d",ogr1);
    printf("\nIkinci ogretim sayisi: %d",ogr2);

    son=clock();
    double zaman=son-baslangic;
    printf("\n----Siniflandira fonksiyonunda gecen sure: %.2lf----",zaman);
}



void sinif()
{
    FILE *dosya;
    double baslangic,son,zaman;
    baslangic=clock();
    int sayac1=0,sayac2=0,sayac3=0,sayac4=0;
    int i,ss,k; //ss=sinif sayisi
    printf("\nsinif sayisini giriniz: ");
    scanf("%d",&ss);
    int dizi[ss];
    for(i=0; i<ss; i++)
    {
        printf("%d.sinifin kapasitesini giriniz: ",i+1);
        scanf("%d",&dizi[i]);

    }
    int secim,gecici=0,esit1=sayac2%ss;
    int esit2=sayac2%ss;
    char text1[]="sinif1ogrX.txt";
    char text2[]="sinif2ogrX.txt";

    printf("\n en az sinif dagilimi icin:1,  esit dagilim icin 2 ye basiniz: ");
    scanf("%d",&secim);
    for(i=0; i<ss; i++)
    {
        for(k=i+1; k<ss; k++)
        {
            if(dizi[i]<dizi[k])
                gecici=dizi[i];
            dizi[i]=dizi[k];
            dizi[k]=gecici;
        }


    }

    if(secim==1)
    {
        for(k=0; k<ss; k++)
        {
            text1[9]=esit1+'0';
            text2[9]=esit2+'0';

            for(i=0; i<kisisayisi; i++)
            {
                if(bilgi[i].ogr_turu==1)
                {
                    if(sayac3>=dizi[k])
                    {
                        sayac3=0;
                        continue;
                    }
                    dosya=fopen(text1,"a+");
                    fprintf(dosya,"%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
                    fclose(dosya);
                    sayac3++;
                }

                if(bilgi[i].ogr_turu==2&&sayac4!=dizi[k])
                {
                    if(sayac4>=dizi[k])
                    {
                        sayac4=0;
                        continue;
                    }
                    dosya=fopen(text2,"a+");
                    fprintf(dosya,"%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
                    fclose(dosya);
                    sayac4++;
                }
            }
        }



    }
    if(secim==2)
    {int j;
     for(j=0; j<ss; j++)
        {
            text1[9]=j+1+'0';
            text2[9]=j+1+'0';
            sayac1=0;
            sayac2=0;
        dongu:  for(i=0; i<kisisayisi; i++)
            {
                if(bilgi[i].ogr_turu==1)
                {
                    if(sayac1>=dizi[j])
                    {

                        goto dongu;
                    }

                    dosya=fopen(text1,"a+");
                    fprintf(dosya,"%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
                    fclose(dosya);
                    sayac1++;

                }
                else
                {
                    if(sayac2>=dizi[j])
                    {

                        continue;
                    }

                    dosya=fopen(text2,"a+");
                    fprintf(dosya,"%d %s %s %d %d \n",bilgi[i].ogr_no,bilgi[i].ad,bilgi[i].soyad,bilgi[i].sira,bilgi[i].ogr_turu);
                    fclose(dosya);
                    sayac2++;
                }

            }
        }

    }


    son=clock();
    zaman=son-baslangic;

    printf("\n----Sinif fonksiyonunda gecen zaman:%.2lf ----",zaman);
    puts("cikmak icin tusa basiniz:");
    getch();
}

