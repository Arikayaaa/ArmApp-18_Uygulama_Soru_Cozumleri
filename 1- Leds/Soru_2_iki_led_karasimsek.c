//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti için yazýlmýþtýr   //
// Ledleri ayný anda iki led yanacak þekilde kara þimþek efekti yapan programý yazýnýz.//

void main()                                             // Ana Program Bloðu
{
 GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_0|      // 'E' Portunun 0-7. pinleri dijital
                                  _GPIO_PINMASK_1|      // çýkýþ olarak ayarlanýyor.
                                  _GPIO_PINMASK_2|
                                  _GPIO_PINMASK_3|
                                  _GPIO_PINMASK_4|
                                  _GPIO_PINMASK_5|
                                  _GPIO_PINMASK_6|
                                  _GPIO_PINMASK_7);
 while(1)                                               // Sonsuz döngü.
 {
  int i=0;                                              // int tipinde 'i' isminde yerel deðiþken tanýmlanýyor.
  char leds=3;                                          // char tipinde 'leds' isminde bir deðiþken tanýmlanýyor.

  for(i=0;i<6;i++)                                      // 6 kez tekrarlanan for döngüsü bloðu.
                  {
                   GPIOE_ODR=leds;                      // 'E' portuna 'leds' deðiþkeni yükleniyor.( ilk anda 00000011)
                   leds<<=1;                            // 'leds' deðiþkeni 1 kez sola öteleniyor. (ilk evrede 00000110)
                   delay_ms(100);                       // 100 ms bekleniyor.
                  }
  for(i=0;i<6;i++)                                      // 6 kez tekrarlanan for döngüsü bloðu.
                  {
                   GPIOE_ODR=leds;                      // 'E' portuna 'leds' deðiþkeni yükleniyor.( ilk anda 11000000)
                   leds>>=1;                            // 'leds' deðiþkeni 1 kez sola öteleniyor. (ilk evrede 01100000)
                   delay_ms(100);                       // 100 ms bekleniyor.
                  }
 }
}