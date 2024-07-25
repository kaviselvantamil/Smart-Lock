#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

//-----------------------keypad-----------------------------//
const byte ROWS = 4;//rows in the keypad
const byte COLS = 4;//columns in the keypad

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};//key layout

byte rowPins[ROWS] = {A3, 8, 7, 6};//pins connected to rows
byte colPins[COLS] = {5, 4, 3, 2};//pins connected to columns

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//-------------------------LCD-------------------------------//
LiquidCrystal lcd(11, 10, A4, A5, 12, 13);//(rs, enable, d4, d5, d6, d7)

//-------------------------Password-------------------------------//
#define Password_Length 5
char Data[Password_Length]; 
char Passkey[Password_Length] = "1234"; 
byte data_count = 0;//passkey_count = 0;
char customKey;

//--------------door action---------//
int G_doorled = A1;//green led
int R_doorled = A0;//red led
int door_buzzer1 = A2;//buzzer
Servo door_ser; //door servo



void setup(){
  lcd.begin(16, 2);// set up the LCD's number of columns and rows:
  lcd.clear();// Clears the LCD screen
  pinMode(G_doorled, OUTPUT);
  pinMode(R_doorled, OUTPUT);
  pinMode(door_buzzer1,OUTPUT);//buzzer
}
  
void loop(){
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
  
  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey;//array Data[...] 
    lcd.setCursor(data_count,1);//display data_count'th column & 1'th row
    lcd.print(Data[data_count]); 
    data_count++;
    }
  
  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, Passkey)){ //Data & Master comparing
      lcd.print("Correct");
      digitalWrite(R_doorled, LOW);
      digitalWrite(G_doorled, HIGH);
      
      door_ser.attach(9);//door servo
      door_ser.write(90);//door open
      noTone(door_buzzer1);//buzzer OFF(incase in ON)
      delay(500);
      //door_ser.write(0);
      
      digitalWrite(G_doorled, LOW);
      }
    else{
      lcd.print("Incorrect");
      digitalWrite(R_doorled, HIGH);
      
      tone(door_buzzer1,600);//buzzer
      delay(500);
      }
    
    lcd.clear();
    clearData();//clear data from data_count(from void clearData()) 
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}