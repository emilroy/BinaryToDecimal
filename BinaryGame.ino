//Author: Emil
//Description: Exercise to help you translate from unsigned binary to decimal

#include <Keypad.h>

//prototyping the functions
String randBinary(int n);
String convertToDecimal(int bin);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class Keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//SETUP==========================================================================
int green = 12;//green led with pin 12
int red = 13; //red led with pin 13
String binary, decimal;//the binary and decimal numbers we'll be creating

void setup() {
  pinMode(green, OUTPUT); //Declaring LED as an output
  pinMode(red, OUTPUT);

  //this is to make it so that our binary number will truly be random
  //if analog pin A0 is unconnected, there will be random noise that'll
  //cause generate different seed numbers everytime the sketch runs
  //randomSeed() then shuffles the random function
  randomSeed(analogRead(A0));
  
  Serial.begin(9600);
  while (!Serial); //wait until Serial is ready
  
  binary = randBinary(4);//creates random unsigned binary number with 4 bits
  decimal = convertToDecimal(binary.toInt());//converts the binary number to decimal
  Serial.println("What number is this in decimal?");
  Serial.println("Use your keypad to enter the number and press '*' to submit your answer");
  Serial.println("Binary: " + binary);//displays the randomly created binary number
}

//LOOP===========================================================================
String input="";//the answer user enters in
void loop() {
  char key = customKeypad.getKey();//the key on the keypad that the user presses
  
  if(key){//if a key is pressed
    if(key == '*'){//what to do when user submits their answer
      if(input==decimal){//if user enters the right decimal answer
        Serial.println("\nYou got it!");
        digitalWrite(green, HIGH);
        delay(2000);
        digitalWrite(green, LOW);

        //start over with new binary
        Serial.println("What number is this in decimal?");
        binary = randBinary(4);//you can change number of bits here by replacing the 4
        Serial.println("Binary: " + binary);
        decimal = convertToDecimal(binary.toInt());//converts the binary number to decimal
        input="";//reset their input
      }
      else{
        input="";//reset their input
        Serial.println("\nYou didn't get it :( Try again");
        digitalWrite(red, HIGH);
        delay(2000);
        digitalWrite(red, LOW);
      }
    }
    else if(key != 'A' and key != 'B' and key != 'D' and key!='C' and key != '#'){//when they press a number
      Serial.print(key);//writes out on the screen what the user enters
      input+=key;//adds that number to part of their answer
    }
  }
  delay(50);
}

/*randBinary function===========================================================
 * Decription: Creates randomly generated unsigned binary with n bits
 * Paramaters: int n - the number of bits the binary is going to be
 * Return: binary - returns the binary number as a string
 */
String randBinary(int n){
    
   String binary = "";

   for (int i = 0; i < n; i++) {
       int x = random()%2;
       binary += String(x);
   }
   return binary;
}

/*convertToDecimal function=====================================================
 * Description: converts a binary number to decimal
 * Parameters: int bin - the binary number needed to be converted
 * Return: String(decimal) - returns the decimal transalation of the binary 
 *                           as a string
 */
String convertToDecimal(int bin){
  
   int decimal = 0, i = 1, remainder;
  
   while (bin!=0)
   {
       remainder = bin%10;
       decimal = decimal+(remainder*i);
       i *= 2;
       bin=bin/10;
   }
   return String(decimal);
}
