//        2x16 Karakter LCD Kullanimi      //
//        MikroC v6.2 - STM32F407VG        //
// ARMapp-18 Deney Seti için yazilmistir   //
//1. Satira adinizi ve soyadinizi, 2. Satira okul numaranizi yazan programi yaziniz.


sbit LCD_RS at GPIOD_ODR.B2;                            // RS pini PD2 pinine bagli.
sbit LCD_EN at GPIOD_ODR.B3;                            // EN pini PD3 pinine bagli.
sbit LCD_D4 at GPIOD_ODR.B4;                            // D4 pini PD4 pinine bagli.
sbit LCD_D5 at GPIOD_ODR.B5;                            // D5 pini PD5 pinine bagli.
sbit LCD_D6 at GPIOD_ODR.B6;                            // D6 pini PD6 pinine bagli.
sbit LCD_D7 at GPIOD_ODR.B7;                            // D7 pini PD7 pinine bagli.

char dizi[16]="SuleymanArikaya";                        // 16 karakterlik dizi içerisinde bir text tanimlaniyor.
int i=1316;                                             // int tipinde 'i' isminde degisken tanimlaniyor.
char txt[7];

void main()                                             // Ana program blogu
{
 Lcd_Init();                                            // LCD kurulumu yapiliyor.
 delay_ms(200);                                         // LCD kurulumunun hatasiz sonuçlanmasi için 200 ms bekleniyor.
 Lcd_Cmd(_LCD_CLEAR);                                   // LCD ekrani temizleniyor.
 Lcd_Cmd(_LCD_CURSOR_OFF);                              // LCD imleci kapatiliyor.
 Lcd_Out(1,1,"SuleymanArikaya");                        // LCD'nin 1. satir 1. sütunundan itibaren 'SuleymanArikaya'  yazisi yazdiriliyor.

 /*for(i=0;i<15;i++)                                      // LCD'nin 2. satir 1. sütunundan itibaren 'SuleymanArikaya'  yazisi yazdiriliyor.
  {
   Lcd_Chr(1,(i+1),dizi[i]);
  }*/
  
 IntToStr(i,txt);                                     // int tipindeki i degiskeni yaziya dönüstürülerek txt isimli diziye aktariliyor..
 Lcd_Out(2,1,txt);                                    // LCD'nin 1. satir 6. sutununa txt dizisinin içerigi yazdiriliyor.
 delay_ms(50);                                        // 50 ms bekleniyor.
}
}