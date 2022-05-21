//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti i�in yaz�lm��t�r   //
// Ledlerde binary olarak 0-255 aras� sayan program� yaz�n�z.//

void main()                                             // Ana Program Blo�u
{
 GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_0|      // 'E' Portunun 0-7. pinleri dijital
                                  _GPIO_PINMASK_1|      // ��k�� olarak ayarlan�yor.
                                  _GPIO_PINMASK_2|
                                  _GPIO_PINMASK_3|
                                  _GPIO_PINMASK_4|
                                  _GPIO_PINMASK_5|
                                  _GPIO_PINMASK_6|
                                  _GPIO_PINMASK_7);
 while(1)                                               // Sonsuz d�ng�.
 {
  char leds=1;                                          // char tipinde 'leds' isminde bir de�i�ken tan�mlan�yor.

  for(leds;leds<256;leds++)                                      // 256 kez tekrarlanan for d�ng�s� blo�u.
                  {
                   GPIOE_ODR=leds;                      // 'E' portuna 'leds' de�i�keni y�kleniyor.( ilk anda 00000001)
                   delay_ms(100);                       // 100 ms bekleniyor.
                  }
 }
}