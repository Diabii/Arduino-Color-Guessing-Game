#include<LiquidCrystal.h>
const int redPin = 11;
const int greenPin = 9;
const int bluePin = 10;
const int buttonPin = 8;
//Dane
const char* colors[] = {"Czerwony", "Zielony", 
"Niebieski", "Zolty",
 "Fioletowy", "Pomaranczowy", "Rozowy", 
"Bialy"};
const int colorValues[][5] = {
 {255, 0, 0, 0, 127}, // Czerwony
 {0, 255, 0, 128, 255}, // Zielony
 {0, 0, 255, 256, 383}, // Niebieski
 {255, 255, 0, 384, 511}, // Żółty
 {128, 0, 128, 512, 639}, // Fioletowy
 {255, 90, 0, 640, 767}, // Pomarańczowy 
 {255, 0, 255, 768, 895}, // Różowy
 {255, 255, 255, 896, 1023} // Biały
};
int targetColor = 0;
int value = 0;
int selectedColor = -1;
bool nowaRunda = true;
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
void setup() {
 pinMode(redPin, OUTPUT);
 pinMode(greenPin, OUTPUT);
 pinMode(bluePin, OUTPUT);
 pinMode(buttonPin, INPUT);
 randomSeed(analogRead(0));
 
 //Ustawienia wyswietlacza
 lcd.begin(16, 2);
 analogWrite(6, 50);
 
 Serial.begin(9600);
}
void loop() {
 //Start nowej rundy
 if (nowaRunda) {
 targetColor = random(0, 8);
 setColor(colorValues[targetColor][0], 
colorValues[targetColor][1],
 colorValues[targetColor][2]);
 
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Wybrany kolor:");
 
 nowaRunda = false;
 }
 
 //Odczyt potencjometru
 value = analogRead(A0);
 
 for (int i = 0; i < 8; i++) {
 if (value >= colorValues[i][3] && value <= 
colorValues[i][4]) {
 if (selectedColor != i) { //tylko jeśli się zmienił
 selectedColor = i;
 
 lcd.setCursor(0, 1);
 lcd.print(" "); //czyszczenie linii
 lcd.setCursor(0, 1);
 lcd.print(colors[selectedColor]);
 }
 break;
 }
 }
 
 //Odczyt przycisku
 int buttonState = digitalRead(buttonPin);
 
 if (buttonState == HIGH) {
 if (selectedColor == targetColor) {
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Dobrze!"); 
 } else {
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Zle!");
 }
 delay(5000);
 nowaRunda = true; //przygotowanie nowej rundy
 }
 delay(100); //małe opóźnienie na stabilizację przycisku
}
void setColor(int r, int g, int b) {
 analogWrite(redPin, r);
 analogWrite(greenPin, g);
 analogWrite(bluePin, b);
}
