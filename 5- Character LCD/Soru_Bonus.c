//        2x16 Karakter LCD Kullanimi      //
//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti için yazilmistir   //
// Yukari Tus =  Anahtarlar 1 konumunda oldugunda ledler yansin.
// Asagi Tus = Anahtarlar 0 konumunda oldugunda ledler yansin.
// Orta Tus = Basma durumunda yanik olan ledlerin degerini ondalik tabanda "Sayi= "X" " olarak LCD Ekrana yazdirsin.
// Sag Tus = LCD Ekranda yazan yaziyi saga kaydirsin.
// Sol Tus = LCD Ekranda yazan yaziyi sola kaydirsin.

                                                       // Menü butonlari tanimlaniyor.
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
char txt[7];                                            // char tipinde 'txt' isminde dizi tanymlanyyor.

void main()                                             // Ana program blogu
{
 GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_0|     // 'E' Portunun 0-7. pinleri dijital
                                  _GPIO_PINMASK_1|     //  çikis olarak ayarlaniyor. (led)
                                  _GPIO_PINMASK_2|
                                  _GPIO_PINMASK_3|
                                  _GPIO_PINMASK_4|
                                  _GPIO_PINMASK_5|
                                  _GPIO_PINMASK_6|
                                  _GPIO_PINMASK_7|
                                  _GPIO_PINMASK_13|    // 'E' Portunun 13,14 ve 15. pinleri dijital
                                  _GPIO_PINMASK_14|    //  giris olarak ayarlaniyor.(switch)
                                  _GPIO_PINMASK_15);

 GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_4|      // 'C' Portunun 4. pini dijital giris olarak ayarlaniyor.(Menü butonu)
                                 _GPIO_PINMASK_8);     // 'C' Portunun 8. pini dijital giris olarak ayarlaniyor.(switch)

 GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_9 |     // 'D' Portunun 9,10 ve 11. pinleri dijital
                                 _GPIO_PINMASK_10|     // giris olarak ayarlaniyor.(switch)
                                 _GPIO_PINMASK_11);
                                 
 GPIO_Digital_Input(&GPIOB_BASE,_GPIO_PINMASK_8 |      // 'B' Portunun 8,12,13 ve 14. pinleri dijital
                                 _GPIO_PINMASK_12|     // giris olarak ayarlaniyor. (Menü butonlari)
                                 _GPIO_PINMASK_13|
                                 _GPIO_PINMASK_14|
                                 _GPIO_PINMASK_15);    // 'B' Portunun 15. pini dijital giris olarak ayarlaniyor.(switch)

 Lcd_Init();                                           // LCD kurulumu yapiliyor.
 delay_ms(200);                                        // LCD kurulumunun hatasiz sonuçlanmasi için 200 ms bekleniyor.
 Lcd_Cmd(_LCD_CLEAR);                                  // LCD ekrani temizleniyor.
 Lcd_Cmd(_LCD_CURSOR_OFF);                             // LCD imleci kapatiliyor.
 
 while(1)
 {   
   char switches;                                    // char tipinde 'switches' isminde bir degisken olusturuluyor.
   
    if(orta)
    {
     Lcd_Out(1,1,"Sayi= ");                           // LCD'nin 1. satir 1. sütunundan itibaren 'Sayi='  yazisi yazdiriliyor.
     delay_ms(20);
     IntToStr(GPIOE_ODR,txt);                         // int tipindeki i degiskeni yaziya dönüstürülerek txt isimli diziye aktariliyor..
     Lcd_Out(1,6,txt);                                // LCD'nin 1. satir 6. sütunundan itibaren txt  degiskeni yazdiriliyor.
    }
    
    if(yukari)
    {
     switches.b0=GPIOE_IDR.B13;                      // 'E' portunun 13. pininin degeri okunarak
                                                     // 'switches' degiskeninin 7. bitine aktariliyor.
     switches.b1=GPIOE_IDR.B14;                      // 'E' portunun 14. pininin degeri okunarak
                                                     // 'switches' degiskeninin 6. bitine aktariliyor.
     switches.b2=GPIOE_IDR.B15;                      // 'E' portunun 15. pininin degeri okunarak
                                                     // 'switches' degiskeninin 5. bitine aktariliyor.
     switches.b3=GPIOB_IDR.B15;                      // 'B' portunun 15. pininin degeri okunarak
                                                     // 'switches' degiskeninin 4. bitine aktariliyor.
     switches.b4=GPIOC_IDR.B8 ;                      // 'C' portunun 18. pininin degeri okunarak
                                                     // 'switches' degiskeninin 3. bitine aktariliyor.
     switches.b5=GPIOD_IDR.B9 ;                      // 'D' portunun 9. pininin degeri okunarak
                                                     // 'switches' degiskeninin 2. bitine aktariliyor.
     switches.b6=GPIOD_IDR.B10;                      // 'D' portunun 10. pininin degeri okunarak
                                                     // 'switches' degiskeninin 1. bitine aktariliyor.
     switches.b7=GPIOD_IDR.B11;                      // 'D' portunun 11. pininin degeri okunarak
                                                     // 'switches' degiskeninin 0. bitine aktariliyor.
     GPIOE_ODR=switches;                             // 'E' portuna switches degiskeni aktarilarak anahtarlarin
                                                     // durumu ledlerde gösteriliyor.
    }
    
    if(asagi)
    {
     switches.b0=GPIOE_IDR.B13;                      // 'E' portunun 13. pininin degeri okunarak
                                                     // 'switches' degiskeninin 7. bitine aktariliyor.
     switches.b1=GPIOE_IDR.B14;                      // 'E' portunun 14. pininin degeri okunarak
                                                     // 'switches' degiskeninin 6. bitine aktariliyor.
     switches.b2=GPIOE_IDR.B15;                      // 'E' portunun 15. pininin degeri okunarak
                                                     // 'switches' degiskeninin 5. bitine aktariliyor.
     switches.b3=GPIOB_IDR.B15;                      // 'B' portunun 15. pininin degeri okunarak
                                                     // 'switches' degiskeninin 4. bitine aktariliyor.
     switches.b4=GPIOC_IDR.B8 ;                      // 'C' portunun 18. pininin degeri okunarak
                                                     // 'switches' degiskeninin 3. bitine aktariliyor.
     switches.b5=GPIOD_IDR.B9 ;                      // 'D' portunun 9. pininin degeri okunarak
                                                     // 'switches' degiskeninin 2. bitine aktariliyor.
     switches.b6=GPIOD_IDR.B10;                      // 'D' portunun 10. pininin degeri okunarak
                                                     // 'switches' degiskeninin 1. bitine aktariliyor.
     switches.b7=GPIOD_IDR.B11;                      // 'D' portunun 11. pininin degeri okunarak
                                                     // 'switches' degiskeninin 0. bitine aktariliyor.
     GPIOE_ODR=~switches;                            // 'E' portuna switches degiskeni aktarilarak anahtarlarin
                                                     // durumu ledlerde gösteriliyor.
    }
    
    if(sag)
    {
     Lcd_Cmd(_LCD_SHIFT_RIGHT);
     delay_ms(200);
    }
    
    if(sol)
    {
     Lcd_Cmd(_LCD_SHIFT_LEFT);
     delay_ms(200);
    }
 }

}