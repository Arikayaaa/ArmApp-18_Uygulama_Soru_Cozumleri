//    Anahtarlarýn ve Ledlerin kullanýmý.  //
//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti için yazýlmýþtýr   //
/* 	SW7 - LED0
	SW6 - LED1
	SW5 - LED2
	SW4 - LED3
	SW3 - LED4
	SW2 - LED5 
	SW1 - LED6
	SW0 - LED7
    eþleþmesi ile anahtarlarýn eþleþtikleri ledlerin durumlarýný kontrol etmelerini saðlayýnýz.*/


void main()                                           // Ana Program Bloðu
{
 GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_0|    // 'E' Portunun 0-7. pinleri dijital
                                  _GPIO_PINMASK_1|    //  çýkýþ olarak ayarlanýyor.
                                  _GPIO_PINMASK_2|
                                  _GPIO_PINMASK_3|
                                  _GPIO_PINMASK_4|
                                  _GPIO_PINMASK_5|
                                  _GPIO_PINMASK_6|
                                  _GPIO_PINMASK_7);

 GPIO_Digital_Input(&GPIOE_BASE, _GPIO_PINMASK_13|   // 'E' Portunun 13,14 ve 15. pinleri dijital
                                 _GPIO_PINMASK_14|   //  giriþ olarak ayarlanýyor.
                                 _GPIO_PINMASK_15);

 GPIO_Digital_Input(&GPIOB_BASE, _GPIO_PINMASK_15);  // 'B' Portunun 15. pini dijital
                                                     // giriþ olarak ayarlanýyor.

 GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_8 );  // 'C' Portunun 8. pini dijital
                                                     // giriþ olarak ayarlanýyor.
 
 GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_9 |   // 'D' Portunun 9,10 ve 11. pinleri dijital
                                 _GPIO_PINMASK_10|   // giriþ olarak ayarlanýyor.
                                 _GPIO_PINMASK_11);
                                 
 while(1)                                            // Sonsuz döngü
    {
     char switches;                                  // char tipinde 'switches' isminde bir deðiþken oluþturuluyor.
     switches.b7=GPIOE_IDR.B13;                      // 'E' portunun 13. pininin deðeri okunarak
                                                     // 'switches' deðiþkeninin 0. bitine aktarýlýyor.
     switches.b6=GPIOE_IDR.B14;                      // 'E' portunun 14. pininin deðeri okunarak
                                                     // 'switches' deðiþkeninin 1. bitine aktarýlýyor.
     switches.b5=GPIOE_IDR.B15;                      // 'E' portunun 15. pininin deðeri okunarak
                                                     // 'switches' deðiþkeninin 2. bitine aktarýlýyor.
     switches.b4=GPIOB_IDR.B15;                      // 'B' portunun 15. pininin deðeri okunarak
                                                     // 'switches' deðiþkeninin 3. bitine aktarýlýyor.
     switches.b3=GPIOC_IDR.B8 ;                      // 'C' portunun 18. pininin deðeri okunarak
                                                     // 'switches' deðiþkeninin 4. bitine aktarýlýyor.
     switches.b2=GPIOD_IDR.B9 ;                      // 'D' portunun 9. pininin deðeri okunarak
                                                     // 'switches' deðiþkeninin 5. bitine aktarýlýyor.
     switches.b1=GPIOD_IDR.B10;                      // 'D' portunun 10. pininin deðeri okunarak
                                                     // 'switches' deðiþkeninin 6. bitine aktarýlýyor.
     switches.b0=GPIOD_IDR.B11;                      // 'D' portunun 11. pininin deðeri okunarak
                                                     // 'switches' deðiþkeninin 7. bitine aktarýlýyor.
     GPIOE_ODR=switches;                             // 'E' portuna switches deðiþkeni aktarýlarak anahtarlarýn
                                                     // durumu ledlerde gösteriliyor.
    }
}