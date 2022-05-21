//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti için yazýlmýþtýr   //
// Ledlerde binary olarak 0-255 arasý sayan programý yazýnýz.//

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
  char leds=1;                                          // char tipinde 'leds' isminde bir deðiþken tanýmlanýyor.

  for(leds;leds<256;leds++)                                      // 256 kez tekrarlanan for döngüsü bloðu.
                  {
                   GPIOE_ODR=leds;                      // 'E' portuna 'leds' deðiþkeni yükleniyor.( ilk anda 00000001)
                   delay_ms(100);                       // 100 ms bekleniyor.
                  }
 }
}