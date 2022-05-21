//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti için yazilmistir   //
// Menü tuþ takýmý modülünü kullanarak yukarý butonuna týklandýðýnda yukarýya doðru sayan, 
// aþaðý butonuna basýldýðýnda aþaðý doðru sayan programý yazýnýz.

                                                        // Menü butonlari tanimlaniyor.
#define yukari  GPIOC_IDR.B4                            // 'yukari' butonu PC4 pininin deger okuma registerina tanimlaniyor.
#define asagi   GPIOB_IDR.B14                           // 'asagi' butonu PB14 pininin deger okuma registerina tanimlaniyor.


void yukari_sayma(unsigned int k);
void asagi_sayma(unsigned int k);

unsigned int sayilar[10]={0x3F,0x06,0x5B,0x4F,0x66      // 7Segment displayde gösterilecek rakamlarin kodlari 'sayilar'
                          ,0x6D,0x7D,0x07,0x7F,0x6F};   // dizisi olarak tanimlaniyor.
unsigned int i=0,j=0,k=0;                               // i ve j isminde iki adet unsigned int tipinde degisken tanimlaniyor.

void display(unsigned int i)                            // 'display' isminde tanimlanmis ve isaretsiz tamsayi türünde
{                                                       // deger alan fonksiyon tanimlaniyor.
 char binler,yuzler,onlar,birler;                       // char tipinde basamaklara ait sayil degerleri tanimlaniyor.
 binler=i/1000;                                         // binler basamaginin sayi degeri hesaplaniyor.
 yuzler=(i/100)%10;                                     // yuzler basamaginin sayi degeri hesaplaniyor.
 onlar=(i/10)%10;                                       // onlar basamaginin sayi degeri hesaplaniyor.
 birler=i%10;                                           // birler basamaginin sayi degeri hesaplaniyor.

 GPIOE_ODR=0x0080 | sayilar[binler];                    // Binler basamaginin sayi degerine karsilik gelen 7 segment kodu
 delay_ms(2);                                           // diziden çekilerek displayin en soldaki hanesinde gösteriliyor ve
                                                        // 2 ms beklenerek sayinin displayde görülebilmesi saglaniyor.

 GPIOE_ODR=0x0100 | sayilar[yuzler];                    // Yuzler basamaginin sayi degerine karsilik gelen 7 segment kodu
 delay_ms(2);                                           // diziden çekilerek displayin en soldaki hanesinde gösteriliyor ve
                                                        // 2 ms beklenerek sayinin displayde görülebilmesi saglaniyor.

 GPIOE_ODR=0x0200 | sayilar[onlar];                     // Onlar basamaginin sayi degerine karsilik gelen 7 segment kodu
 delay_ms(2);                                           // diziden çekilerek displayin en soldaki hanesinde gösteriliyor ve
                                                        // 2 ms beklenerek sayinin displayde görülebilmesi saglaniyor.

 GPIOE_ODR=0x0400 | sayilar[birler];                    // Birler basamaginin sayi degerine karsilik gelen 7 segment kodu
 delay_ms(2);                                           // diziden çekilerek displayin en soldaki hanesinde gösteriliyor ve
                                                        // 2 ms beklenerek sayinin displayde görülebilmesi saglaniyor.
}

void yukari_sayma(unsigned int k)                       // yukari sayma fonksiyonu
{
  for(i=k;i<10000;i++)                                  // 0'dan baslayip 9999 olana kadar sayilari displayde gösteren döngü.
     {
      for(j=0;j<30;j++)display(i);                       // ayni sayi 5 kez gösterilerek sayi artisinda gecikme saglaniyor.
      k=i;
      if(asagi)asagi_sayma(k);                          // asagi butona basýlmasý halinde kaldýðý yerden asagý saymaya devam etmek icin
     }
}

void asagi_sayma(unsigned int k)                        // asagi sayma fonksiyonu
{
  for(i=k;i>0;i--)                                      // k'dan baslayip 0 olana kadar sayilari displayde gösteren döngü.
     {
      for(j=0;j<30;j++)display(i);                       // ayni sayi 5 kez gösterilerek sayi artisinda gecikme saglaniyor.
      k=i;
      if(yukari)yukari_sayma(k);
     }
}
void main()                                             // Ana program blogu
{
 GPIO_Digital_Output(&GPIOE_BASE,  _GPIO_PINMASK_0|     // 'E' portunun 0,1,2,3,4,5,6,7,8,9 ve 10. pinleri
                                   _GPIO_PINMASK_1|     // dijital çikis olarak tanimlaniyor.
                                   _GPIO_PINMASK_2|
                                   _GPIO_PINMASK_3|
                                   _GPIO_PINMASK_4|
                                   _GPIO_PINMASK_5|
                                   _GPIO_PINMASK_6|
                                   _GPIO_PINMASK_7|
                                   _GPIO_PINMASK_8|
                                   _GPIO_PINMASK_9|
                                  _GPIO_PINMASK_10);

 GPIO_Digital_Input(&GPIOC_BASE,  _GPIO_PINMASK_4);      // 'C' portunun 4. pini giriþ olarak tanýmlanýyor.
 GPIO_Digital_Input(&GPIOB_BASE,  _GPIO_PINMASK_14);     // 'B' portunun 14. pini giriþ olarak tanýmlanýyor.

 while(1)                                                // Sonsuz döngü.
 {
  if(yukari)yukari_sayma(k);                             // yukarý tusa basýlmasý halinde yukari sayma fonksiyonu calisacak.
  if(asagi)asagi_sayma(k);                               // asagi tusa basýlmasý halinde asagi sayma fonksiyonu calisacak.
 }
}