//        2x16 Karakter LCD Kullanimi      //
//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti i�in yazilmistir   //
//Men� tu� tak�m� mod�l�n� kullanarak yukar� butonuna t�kland�k�a LCD' de yukar�ya do�ru sayan, a�a�� butonuna bast�k�a a�a�� do�ru sayan program� yaz�n�z.

                                                       // Men� butonlari tanimlaniyor.
#define yukari   GPIOC_IDR.B4                          // 'yukari' butonu PC4 pininin deger okuma registerina tanimlaniyor.
#define asagi    GPIOB_IDR.B14                         // 'asagi' butonu PB14 pininin deger okuma registerina tanimlaniyor.
#define sol      GPIOB_IDR.B12                         // 'sol' butonu PB12 pininin deger okuma registerina tanimlaniyor.
#define sag      GPIOB_IDR.B13                         // 'sag' butonu PB13 pininin deger okuma registerina tanimlaniyor.
#define orta     GPIOB_IDR.B8                          // 'orta' butonu PB8 pininin deger okuma registerina tanimlaniyor

sbit LCD_RS at GPIOD_ODR.B2;                            // RS pini PD2 pinine bagli.
sbit LCD_EN at GPIOD_ODR.B3;                            // EN pini PD3 pinine bagli.
sbit LCD_D4 at GPIOD_ODR.B4;                            // D4 pini PD4 pinine bagli.
sbit LCD_D5 at GPIOD_ODR.B5;                            // D5 pini PD5 pinine bagli.
sbit LCD_D6 at GPIOD_ODR.B6;                            // D6 pini PD6 pinine bagli.
sbit LCD_D7 at GPIOD_ODR.B7;                            // D7 pini PD7 pinine bagli.

int i=0;                                                // int tipinde 'i' isminde degisken tanimlaniyor.
char txt[7];                                            // char tipinde 'txt' isminde dizi tan�mlan�yor.

void main()                                             // Ana program blogu
{
 GPIO_Digital_Input(&GPIOB_BASE,_GPIO_PINMASK_8 |     // 'B' Portunun 8,12,13 ve 14. pinleri dijital
                                 _GPIO_PINMASK_12|     // giris olarak ayarlaniyor. (Men� butonlari)
                                 _GPIO_PINMASK_13|
                                 _GPIO_PINMASK_14);

 GPIO_Digital_Input(&GPIOC_BASE,_GPIO_PINMASK_4 );    // 'C' Portunun 4. pini dijital giris olarak ayarlaniyor. (Men� butonu)
 
 Lcd_Init();                                            // LCD kurulumu yapiliyor.
 delay_ms(200);                                         // LCD kurulumunun hatasiz sonu�lanmasi i�in 200 ms bekleniyor.
 Lcd_Cmd(_LCD_CLEAR);                                   // LCD ekrani temizleniyor.
 Lcd_Cmd(_LCD_CURSOR_OFF);                              // LCD imleci kapatiliyor.
 
 while(1)
 {
  if(yukari)
  {
   i++;
   delay_ms(100);
   }
   
  if(asagi)
  {
   i--;
   delay_ms(100);
  }
  
  Lcd_Cmd(_LCD_CLEAR);
  IntToStr(i,txt);                                     // int tipindeki i de�i�keni yaz�ya d�n��t�r�lerek txt isimli diziye aktar�l�yor..
  Lcd_Out(1,1,txt);                                    // LCD'nin 1. sat�r 6. s�tununa txt dizisinin i�eri�i yazd�r�l�yor.
  delay_ms(50);
  }                                        // 50 ms bekleniyor.
}