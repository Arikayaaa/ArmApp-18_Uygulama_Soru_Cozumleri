//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti için yazýlmýþtýr   //
// "Sol" butonuna basýldýkça ledleri saðdan sola sýrayla söndüren, "sað" butonuna basýldýkça soldan saða sýrasýyla yakan programý yazýnýz.


                                                       // Menü butonlarý tanýmlanýyor.
#define yukari   GPIOC_IDR.B4                          // 'yukarý' butonu PC4 pininin deðer okuma registerýna tanýmlanýyor.
#define asagi    GPIOB_IDR.B14                         // 'asagi' butonu PB14 pininin deðer okuma registerýna tanýmlanýyor.
#define sol      GPIOB_IDR.B12                         // 'sol' butonu PB12 pininin deðer okuma registerýna tanýmlanýyor.
#define sag      GPIOB_IDR.B13                         // 'sag' butonu PB13 pininin deðer okuma registerýna tanýmlanýyor.
#define orta     GPIOB_IDR.B8                          // 'orta' butonu PB8 pininin deðer okuma registerýna tanýmlanýyor.

#define buzzer   GPIOA_ODR.B8                          // 'buzzer' pini PA8 pininin çýkýþ registerýna tanýmlanýyor.
#define powerLed GPIOB_ODR.B6                          // 'powerLed' pini PB6 pininin çýkýþ registerýna tanýmlanýyor.

char ledler=0,buzzerSayac=0;                           // char tipinde 'ledler' ve 'buzzerSayac' isminde iki deðiþken tanýmlanýyor.

void main()                                            // Ana program bloðu.
{
  GPIO_Digital_Input(&GPIOB_BASE,_GPIO_PINMASK_8 |     // 'B' Portunun 8,12,13 ve 14. pinleri dijital
                                 _GPIO_PINMASK_12|     // giriþ olarak ayarlanýyor. (Menü butonlarý)
                                 _GPIO_PINMASK_13|
                                 _GPIO_PINMASK_14);
                                                 
  GPIO_Digital_Input(&GPIOC_BASE,_GPIO_PINMASK_4 );    // 'C' Portunun 4. pini dijital giriþ olarak ayarlanýyor. (Menü butonu)
  
  GPIO_Digital_Output(&GPIOA_BASE,_GPIO_PINMASK_8);    // 'A' Portunun 8. pini dijital çýkýþ olarak ayarlanýyor. (Buzzer)
  
  GPIO_Digital_Output(&GPIOB_BASE,_GPIO_PINMASK_6);    // 'B' Portunun 6. pini dijital çýkýþ olarak ayarlanýyor. (Power Led)
  
  GPIO_Digital_Output(&GPIOE_BASE,_GPIO_PINMASK_0|     // 'E' Portunun 0-7. pinleri dijital çýkýþ olarak ayarlanýyor.
                                  _GPIO_PINMASK_1|
                                  _GPIO_PINMASK_2|
                                  _GPIO_PINMASK_3|
                                  _GPIO_PINMASK_4|
                                  _GPIO_PINMASK_5|
                                  _GPIO_PINMASK_6|
                                  _GPIO_PINMASK_7);
  buzzer=0;                                            // Buzzer susturuluyor.
  powerLed=0;                                          // Power Led söndürülüyor.
  GPIOE_ODR=ledler;                                    // 'ledler' deðiþkeni 0 olduðu için hepsi söndürülüyor.

  while(1)                                             // Sonsuz Döngü
  {
    if(yukari)                                         // Yukarý butonuna basýldýysa ( GPIOC_IDR.B4=1 ise)
    {
      powerLed=1;                                      // Power Led'i yak. (GPIOB_ODR.B6=1 yap)
      delay_ms(200);                                   // Buton arkýný önlemek için 200 ms bekle.
      while(yukari);                                   // Yukarý tuþuna basýlý olduðu müddetçe burada bekle.
    }
    
    if(asagi)                                          // Aþaðý butonuna basýldýysa ( GPIOB_IDR.B14=1 ise)
    {
      powerLed=0;                                      // Power Ledi söndür. (GPIOB_ODR.B6=0 yap)
      delay_ms(200);                                   // Buton arkýný önlemek için 200 ms bekle.
      while(asagi);                                    // Aþaðý tuþuna basýlý olduðu müddetçe burada bekle.
    }
    
    if(sag)                                            // Sað butonuna basýldýysa ( GPIOB_IDR.B13=1 ise)
    {
     ledler=(ledler>>1)+128;                             // ledler degiskenini 1 kez saga kaydir ve 128 ekle.
     GPIOE_ODR=ledler;                                 // E portuna ledler degiskenini yükleyerek istenilen ledlerin yanmasini sagla.
     delay_ms(200);                                    // Buton arkini önlemek için 200 ms bekle.
     while(sag);                                       // Sað tuþuna basýlý olduðu müddetçe burada bekle.
    }
    
    if(sol)                                            // Sol butonuna basýldýysa ( GPIOB_IDR.B12=1 ise)
    {
     if(ledler>0)ledler=(ledler-128)<< 1;                 // Eger ledler degiskeni 0'dan büyükse 128 eksilt ve 1 kez sola kaydir.
     GPIOE_ODR=ledler;                                 // E portuna ledler degiskenini yükleyerek istenilen ledlerin yanmasini sagla.
     delay_ms(200);                                    // Buton arkini önlemek için 200 ms bekle.
     while(sol);                                       // Sol tusuna basili oldugu müddetçe burada bekle.
    }
    
    if(orta)                                           // Orta butonuna basýldýysa ( GPIOB_IDR.B8=1 ise)
    {
      if(buzzerSayac==0)                               // Eðer buzzerSayac deðiþkeni 0 ise
      {
        buzzer=1;                                      // Buzzerý öttür. (GPIOA_ODR.B8=1 yap)
        buzzerSayac++;                                 // buzzerSayac deðiþkenini 1 arttýr.
      }
      else if(buzzerSayac==1)                          // Eðer buzzerSayac=1 ise
      {
        buzzer=0;                                      // Buzzerý sustur. (GPIOA_ODR.B8=0 yap)
        buzzerSayac=0;                                 // buzzerSayac deðiþkenini 0 yap.
      }
      delay_ms(200);                                   // Buton arkýný önlemek için 200 ms bekle.
      while(orta);                                     // orta tuþuna basýlý olduðu müddetçe burada bekle.
    }
  }

}