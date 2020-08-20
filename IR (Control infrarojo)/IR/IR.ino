
//https://gist.github.com/steakknife/e419241095f1272ee60f5174f7759867
#include <LiquidCrystal.h>
#include <IRremote.h>

#define RS 2
#define E 3
#define IRSENSOR 8


LiquidCrystal lcd(RS, E, 4, 5, 6, 7);
IRrecv recv(IRSENSOR);
decode_results codigo;

void setup(){
  pinMode(IRSENSOR, INPUT);
  recv.enableIRIn();
  Serial.begin(9600);
  lcd.begin(20, 4);
}

void loop(){
  lcd.setCursor(0,1);
  lcd.print("Codigo: ");
  if(recv.decode(&codigo)){
    lcd.print(codigo.value, HEX);
    Serial.println(codigo.value, HEX);
    recv.resume();
  }
}
