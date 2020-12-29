#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


const char matrix_bigram_strings[10][2] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};

const char matrix_trigram_strings[10][3]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};

const char languages[2][7]={"english", "german"};

//İngilizce dilinin frekans değerleri
 const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
 //Almanca dilinin frekans değerleri
 const float frequency_germ[20]={ 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };


float calculated_frequencies[20];
float distances [2]={0,0};

void filter_str(char str[]);
void calculate_frequencies_bi(char str[]);
void calculate_frequencies_tri(char str[]);
void calculate_distances();
void detect_lang();


int main()
{
    char Alinan[1000+1];          // ekstra 1 ekledik cunku bitis karekterini dahil etmeliyiz yani 1000 karekter yazilabilir.
    printf("Bir metin giriniz: \n");
    gets(Alinan);

    filter_str(Alinan);         //Bu Fonksiyona atlamak icin komut.

    // Alinan metinimiz artik Filtrelendi.

    calculate_frequencies_bi(Alinan);//Alinan metinimiz üzerinde bigram frekansının hesaplanması.
    calculate_frequencies_tri(Alinan);//Alinan metinimiz üzerinde trigram frekansının hesaplanması.
    calculate_distances(); //Elde ettigimiz frekans matrisi ve eng ve germ matrislerin birer arasindaki distance hesaplanmasi.
    detect_lang(); //Metinin yazıldığı dili calculate_distances sonucuna göre tahmin edilmesi.

      return 0;
}
void filter_str(char str[])     //ascii tablosu sayesinde olmaması gereken karekterleri cikartıyoruz
{
    printf("\n******************************************\n");


    for(int i=0;i<strlen(str);i++)      //strlen() komudu ile char dizimin uzunlugunu bulup gereksiz islemi azaltiyoruz
        for(int j=0;j<=64;j++)
            if(str[i]==j)
                str[i]=32;

    for(int i=0;i<strlen(str);i++)
        for(int j=91;j<=96;j++)
            if(str[i]==j)
                str[i]=32;

    for(int i=0;i<strlen(str);i++)
        for(int j=123;j<=127;j++)
            if(str[i]==j)
                str[i]=32;
    for(int i=0;i<strlen(str);i++) // Burada aldığımız metnin içerisinde bulunan büyük harfler küçük harflere çevriyoruz.
        for(int j=65;j<=90;j++)
            if(str[i]==j)
                str[i]=j+32;

    printf("Yazinin olmamasi gereken kelimelerden arindirilmis hali: \n\n%s\n\n",str);

}
void calculate_frequencies_bi(char str[])
{
     printf("\n******************************************\n");

    int i,j;
    float calculated_frequencies[20];
    float sayac = 0.0;
    for(int i=0;i<10;i++){
        sayac = 0.0;
        for(int k=0;k<strlen(str);k++){//Burada metinimizin uzerinde bigramlarımızın tek tek frekanslarını hesaplıyoruz.
                if(matrix_bigram_strings[i][0]==str[k] && matrix_bigram_strings[i][1]==str[k+1])
                    sayac++;
        }
        calculated_frequencies[i]=sayac; //Her bigramin metinimizin üzerinde frekanslarını hesaplayıp ve bu dizisinde yerleştiriyoruz.
    }

     printf("Alinan metinin uzerinde bigram frekanslari: \n");
     for(i=0;i<10;i++)//Burada hesapladığımız bigram frekansları ekrana yazdırıyoruz.
         printf("%c%c = %.2f\n",matrix_bigram_strings[i][0],matrix_bigram_strings[i][1],calculated_frequencies[i]);

}
void calculate_frequencies_tri(char str[])
{
   printf("\n******************************************\n");
   int i,j;
   float calculated_frequencies[20];
   float sayac = 0.0;
   for(int i=0;i<10;i++){
        sayac = 0.0;
        for(int k=0;k<strlen(str);k++){//Burada metinimizin uzerinde trigramlarımızın tek tek frekanslarını hesaplıyoruz.
                if((matrix_trigram_strings[i][0]==str[k] && matrix_trigram_strings[i][1]==str[k+1]) && matrix_trigram_strings[i][2]==str[k+2])
                    sayac++;
        }
        //calculated_frequencies[1][i]=sayac;//Bir trigramin frekansı hesapladıktan sonra bir sonrakine geçmeden önce değerini bu matrisine aktarıyoruz.Matrisin 2. satrında olacağı için 1 yazdık sartırın numarası olarak.
        calculated_frequencies[10+i]=sayac;//Her dil için aynı dizinde hem bigram hem de trigram olduğundan
    }

    printf("Alinan metinin uzerinde trigram frekanslari: \n");
    for(i=0;i<10;i++)//Burada hesapladığımız trigram frekansları ekrana yazdırıyoruz.
         printf("%c%c%c = %.2f\n",matrix_trigram_strings[i][0],matrix_trigram_strings[i][1],matrix_trigram_strings[i][2],calculated_frequencies[10+i]);

}
void calculate_distances()
{
     printf("\n******************************************\n");

     float toplam = 0.0, dist;
     float calculated_frequencies[20];
     printf("\n\ncalculated_frequences dizisi: \n");
     for(int i=0;i<20;i++){ //calculated_frequencies dizisi ekrana yazdılıyor.
        printf("%.2f ",calculated_frequencies[i]);
     }
     for(int i=0;i<20;i++)
     { //İngilizce dili için verilmiş olan frekans matrisi ile calculated_frequencies dizisi arasında uzaklık hesabı yapılıyor.
            toplam += pow((frequency_eng[i]-calculated_frequencies[i]),2);
     }
     dist= sqrt(toplam);
     distances[0]=dist; //İngilizce için distances dizimizin ilk elemanına aktarıyoruz.

     toplam=0.0;
     for(int i=0;i<20;i++)
     {//Almanca dili için verilmiş olan frekans matrisi ile calculated_frequencies dizisi arasında uzaklık hesabı yapılıyor.
            toplam += pow((frequency_germ[i]-calculated_frequencies[i]),2);
     }
     dist= sqrt(toplam);
     distances[1]=dist;//Almanca için distances dizimizin ikinci elemanına aktarıyoruz.

     printf("\n\neng= %.2f.\ngerm= %.2f\n",distances[0],distances[1]);//Burada ingilizce için ve almanca için uzaklıkları ekrana yazdırıyoruz.
}

void detect_lang()
{
    printf("\n******************************************\n");
    printf("Girdiginiz metnin yazildigi dili: ");
    //Burada distances'lere göre metinimizin yazıldığı dili tahmin ediliyor. İki dillerin arasında hangisinin diğerine göre daha küçükse metinimiz o dilinde yazılmış demektir.

    if(distances[0]>distances[1])
    {
        for(int i=0;i<7;i++)
        {
            printf("%c",languages[1][i]);
        }
    }
    else
        for(int i=0;i<7;i++)
        {
            printf("%c",languages[0][i]);
        }

    printf("\n\n");
}
