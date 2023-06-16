#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void display_init() {
  lcd.begin();
  lcd.backlight();
}


void display_put_txt(String text)
{
  lcd.begin();
	lcd.print(text);
}