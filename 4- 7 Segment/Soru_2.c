//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti i�in yazilmistir   //
// Men� tu� tak�m� mod�l�n� kullanarak yukar� butonuna t�kland���nda yukar�ya do�ru sayan, 
// a�a�� butonuna bas�ld���nda a�a�� do�ru sayan program� yaz�n�z.

                                                        // Men� butonlari tanimlaniyor.
#define yukari  GPIOC_IDR.B4                            // 'yukari' butonu PC4 pininin deger okuma registerina tanimlaniyor.
#define asagi   GPIOB_IDR.B14                           // 'asagi' butonu PB14 pininin deger okuma registerina tanimlaniyor.


void yukari_sayma(unsigned int k);
void asagi_sayma(unsigned int k);

unsigned int sayilar[10]={0x3F,0x06,0x5B,0x4F,0x66      // 7Segment displayde g�sterilecek rakamlarin kodlari 'sayilar'
                          ,0x6D,0x7D,0x07,0x7F,0x6F};   // dizisi olarak tanimlaniyor.
unsigned int i=0,j=0,k=0;                               // i ve j isminde iki adet unsigned int tipinde degisken tanimlaniyor.

void display(unsigned int i)                            // 'display' isminde tanimlanmis ve isaretsiz tamsayi t�r�nde
{                                                       // deger alan fonksiyon tanimlaniyor.
 char binler,yuzler,onlar,birler;                       // char tipinde basamaklara ait sayil degerleri tanimlaniyor.
 binler=i/1000;                                         // binler basamaginin sayi degeri hesaplaniyor.
 yuzler=(i/100)%10;                                     // yuzler basamaginin sayi degeri hesaplaniyor.
 onlar=(i/10)%10;                                       // onlar basamaginin sayi degeri hesaplaniyor.
 birler=i%10;                                           // birler basamaginin sayi degeri hesaplaniyor.

 GPIOE_ODR=0x0080 | sayilar[binler];                    // Binler basamaginin sayi degerine karsilik gelen 7 segment kodu
 delay_ms(2);                                           // diziden �ekilerek displayin en soldaki hanesinde g�steriliyor ve
                                                        // 2 ms beklenerek sayinin displayde g�r�lebilmesi saglaniyor.

 GPIOE_ODR=0x0100 | sayilar[yuzler];                    // Yuzler basamaginin sayi degerine karsilik gelen 7 segment kodu
 delay_ms(2);                                           // diziden �ekilerek displayin en soldaki hanesinde g�steriliyor ve
                                                        // 2 ms beklenerek sayinin displayde g�r�lebilmesi saglaniyor.

 GPIOE_ODR=0x0200 | sayilar[onlar];                     // Onlar basamaginin sayi degerine karsilik gelen 7 segment kodu
 delay_ms(2);                                           // diziden �ekilerek displayin en soldaki hanesinde g�steriliyor ve
                                                        // 2 ms beklenerek sayinin displayde g�r�lebilmesi saglaniyor.

 GPIOE_ODR=0x0400 | sayilar[birler];                    // Birler basamaginin sayi degerine karsilik gelen 7 segment kodu
 delay_ms(2);                                           // diziden �ekilerek displayin en soldaki hanesinde g�steriliyor ve
                                                        // 2 ms beklenerek sayinin displayde g�r�lebilmesi saglaniyor.
}

void yukari_sayma(unsigned int k)                       // yukari sayma fonksiyonu
{
  for(i=k;i<10000;i++)                                  // 0'dan baslayip 9999 olana kadar sayilari displayde g�steren d�ng�.
     {
      for(j=0;j<30;j++)display(i);                       // ayni sayi 5 kez g�sterilerek sayi artisinda gecikme saglaniyor.
      k=i;
      if(asagi)asagi_sayma(k);                          // asagi butona bas�lmas� halinde kald��� yerden asag� saymaya devam etmek icin
     }
}

void asagi_sayma(unsigned int k)                        // asagi sayma fonksiyonu
{
  for(i=k;i>0;i--)                                      // k'dan baslayip 0 olana kadar sayilari displayde g�steren d�ng�.
     {
      for(j=0;j<30;j++)display(i);                       // ayni sayi 5 kez g�sterilerek sayi artisinda gecikme saglaniyor.
      k=i;
      if(yukari)yukari_sayma(k);
     }
}
void main()                                             // Ana program blogu
{
 GPIO_Digital_Output(&GPIOE_BASE,  _GPIO_PINMASK_0|     // 'E' portunun 0,1,2,3,4,5,6,7,8,9 ve 10. pinleri
                                   _GPIO_PINMASK_1|     // dijital �ikis olarak tanimlaniyor.
                                   _GPIO_PINMASK_2|
                                   _GPIO_PINMASK_3|
                                   _GPIO_PINMASK_4|
                                   _GPIO_PINMASK_5|
                                   _GPIO_PINMASK_6|
                                   _GPIO_PINMASK_7|
                                   _GPIO_PINMASK_8|
                                   _GPIO_PINMASK_9|
                                  _GPIO_PINMASK_10);

 GPIO_Digital_Input(&GPIOC_BASE,  _GPIO_PINMASK_4);      // 'C' portunun 4. pini giri� olarak tan�mlan�yor.
 GPIO_Digital_Input(&GPIOB_BASE,  _GPIO_PINMASK_14);     // 'B' portunun 14. pini giri� olarak tan�mlan�yor.

 while(1)                                                // Sonsuz d�ng�.
 {
  if(yukari)yukari_sayma(k);                             // yukar� tusa bas�lmas� halinde yukari sayma fonksiyonu calisacak.
  if(asagi)asagi_sayma(k);                               // asagi tusa bas�lmas� halinde asagi sayma fonksiyonu calisacak.
 }
}