//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti i�in yaz�lm��t�r   //
// "Sol" butonuna bas�ld�k�a ledleri sa�dan sola s�rayla s�nd�ren, "sa�" butonuna bas�ld�k�a soldan sa�a s�ras�yla yakan program� yaz�n�z.


                                                       // Men� butonlar� tan�mlan�yor.
#define yukari   GPIOC_IDR.B4                          // 'yukar�' butonu PC4 pininin de�er okuma register�na tan�mlan�yor.
#define asagi    GPIOB_IDR.B14                         // 'asagi' butonu PB14 pininin de�er okuma register�na tan�mlan�yor.
#define sol      GPIOB_IDR.B12                         // 'sol' butonu PB12 pininin de�er okuma register�na tan�mlan�yor.
#define sag      GPIOB_IDR.B13                         // 'sag' butonu PB13 pininin de�er okuma register�na tan�mlan�yor.
#define orta     GPIOB_IDR.B8                          // 'orta' butonu PB8 pininin de�er okuma register�na tan�mlan�yor.

#define buzzer   GPIOA_ODR.B8                          // 'buzzer' pini PA8 pininin ��k�� register�na tan�mlan�yor.
#define powerLed GPIOB_ODR.B6                          // 'powerLed' pini PB6 pininin ��k�� register�na tan�mlan�yor.

char ledler=0,buzzerSayac=0;                           // char tipinde 'ledler' ve 'buzzerSayac' isminde iki de�i�ken tan�mlan�yor.

void main()                                            // Ana program blo�u.
{
  GPIO_Digital_Input(&GPIOB_BASE,_GPIO_PINMASK_8 |     // 'B' Portunun 8,12,13 ve 14. pinleri dijital
                                 _GPIO_PINMASK_12|     // giri� olarak ayarlan�yor. (Men� butonlar�)
                                 _GPIO_PINMASK_13|
                                 _GPIO_PINMASK_14);
                                                 
  GPIO_Digital_Input(&GPIOC_BASE,_GPIO_PINMASK_4 );    // 'C' Portunun 4. pini dijital giri� olarak ayarlan�yor. (Men� butonu)
  
  GPIO_Digital_Output(&GPIOA_BASE,_GPIO_PINMASK_8);    // 'A' Portunun 8. pini dijital ��k�� olarak ayarlan�yor. (Buzzer)
  
  GPIO_Digital_Output(&GPIOB_BASE,_GPIO_PINMASK_6);    // 'B' Portunun 6. pini dijital ��k�� olarak ayarlan�yor. (Power Led)
  
  GPIO_Digital_Output(&GPIOE_BASE,_GPIO_PINMASK_0|     // 'E' Portunun 0-7. pinleri dijital ��k�� olarak ayarlan�yor.
                                  _GPIO_PINMASK_1|
                                  _GPIO_PINMASK_2|
                                  _GPIO_PINMASK_3|
                                  _GPIO_PINMASK_4|
                                  _GPIO_PINMASK_5|
                                  _GPIO_PINMASK_6|
                                  _GPIO_PINMASK_7);
  buzzer=0;                                            // Buzzer susturuluyor.
  powerLed=0;                                          // Power Led s�nd�r�l�yor.
  GPIOE_ODR=ledler;                                    // 'ledler' de�i�keni 0 oldu�u i�in hepsi s�nd�r�l�yor.

  while(1)                                             // Sonsuz D�ng�
  {
    if(yukari)                                         // Yukar� butonuna bas�ld�ysa ( GPIOC_IDR.B4=1 ise)
    {
      powerLed=1;                                      // Power Led'i yak. (GPIOB_ODR.B6=1 yap)
      delay_ms(200);                                   // Buton ark�n� �nlemek i�in 200 ms bekle.
      while(yukari);                                   // Yukar� tu�una bas�l� oldu�u m�ddet�e burada bekle.
    }
    
    if(asagi)                                          // A�a�� butonuna bas�ld�ysa ( GPIOB_IDR.B14=1 ise)
    {
      powerLed=0;                                      // Power Ledi s�nd�r. (GPIOB_ODR.B6=0 yap)
      delay_ms(200);                                   // Buton ark�n� �nlemek i�in 200 ms bekle.
      while(asagi);                                    // A�a�� tu�una bas�l� oldu�u m�ddet�e burada bekle.
    }
    
    if(sag)                                            // Sa� butonuna bas�ld�ysa ( GPIOB_IDR.B13=1 ise)
    {
     ledler=(ledler>>1)+128;                             // ledler degiskenini 1 kez saga kaydir ve 128 ekle.
     GPIOE_ODR=ledler;                                 // E portuna ledler degiskenini y�kleyerek istenilen ledlerin yanmasini sagla.
     delay_ms(200);                                    // Buton arkini �nlemek i�in 200 ms bekle.
     while(sag);                                       // Sa� tu�una bas�l� oldu�u m�ddet�e burada bekle.
    }
    
    if(sol)                                            // Sol butonuna bas�ld�ysa ( GPIOB_IDR.B12=1 ise)
    {
     if(ledler>0)ledler=(ledler-128)<< 1;                 // Eger ledler degiskeni 0'dan b�y�kse 128 eksilt ve 1 kez sola kaydir.
     GPIOE_ODR=ledler;                                 // E portuna ledler degiskenini y�kleyerek istenilen ledlerin yanmasini sagla.
     delay_ms(200);                                    // Buton arkini �nlemek i�in 200 ms bekle.
     while(sol);                                       // Sol tusuna basili oldugu m�ddet�e burada bekle.
    }
    
    if(orta)                                           // Orta butonuna bas�ld�ysa ( GPIOB_IDR.B8=1 ise)
    {
      if(buzzerSayac==0)                               // E�er buzzerSayac de�i�keni 0 ise
      {
        buzzer=1;                                      // Buzzer� �tt�r. (GPIOA_ODR.B8=1 yap)
        buzzerSayac++;                                 // buzzerSayac de�i�kenini 1 artt�r.
      }
      else if(buzzerSayac==1)                          // E�er buzzerSayac=1 ise
      {
        buzzer=0;                                      // Buzzer� sustur. (GPIOA_ODR.B8=0 yap)
        buzzerSayac=0;                                 // buzzerSayac de�i�kenini 0 yap.
      }
      delay_ms(200);                                   // Buton ark�n� �nlemek i�in 200 ms bekle.
      while(orta);                                     // orta tu�una bas�l� oldu�u m�ddet�e burada bekle.
    }
  }

}