/**
 *  First LCD test
 *  by tony
 *  Date: 2016/9/2
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0 , 4, 5, 6, 7, 3, POSITIVE);

String printString;
int strLength;
int shiftLen = 10;

int input = 0;
int darkBox = 0;

const int button1Pin = 7;
int inputCount = 0;

const int button2Pin = 6;

void setup() {
  randomSeed(millis());
  darkBox = random(1,11);

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  
  Serial.begin(115200);
  lcd.begin(16, 2);

  blinkBackLight(3);

  printLine(1, "Guess from 1 - 9");
}

void loop() {

  if(digitalRead(button1Pin) == HIGH){
    resetLCD();
    
    inputCount++;
    
    printInput();
  }

  if(digitalRead(button2Pin) == HIGH){
    resetLCD();
    
    printInput();

    checkReuslt();

    resetInput();
  }
  
}

void resetLCD(){
  lcd.clear();
}

void printLine(int lineIndex, String msg){
  switch(lineIndex){
    case 1:
      lcd.setCursor(0, 0);
      lcd.print(msg);
      break;
    case 2:
      lcd.setCursor(0, 1);
      lcd.print(msg);
      break;
  }

  delay(250);
}

void checkResult(){
  if(verifyNum(inputCount)){  
      youWin();
    }else{
      youLose();
    }
}

boolean verifyNum(int num){
  Serial.println(num, DEC);
  Serial.println(darkBox);
  if(num == darkBox){
    return true;
  } else {
    return false;
  }
}

void printInput(){
  printLine(1, "Yor input: " + inputCount);
}

void youWin(){
  printLine(2, "You got it!!!");
}

void youLose(){
  printLine(2, "Guess again!!!");
}

void printSerial(){
  Serial.print("count: ");
  Serial.println(inputCount, DEC);
  Serial.print("darkBox: ");
  Serial.println(darkBox, DEC);
}

void blinkBackLight(int blinkTime){
  for(int i=0; i<blinkTime; i++){
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();
}

void resetInput(){
  inputCount = 0;
}

