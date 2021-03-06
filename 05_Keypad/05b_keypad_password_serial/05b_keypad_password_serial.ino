#include "Keypad.h"
const byte ROWS = 4; // Ile wierszy
const byte COLS = 4; // Ile kolumn 
byte rowPins[ROWS] = {9, 8, 7, 6}; //Piny wierszy
byte colPins[COLS] = {5, 4, 3, 2}; //Piny kolum 
char keys[ROWS][COLS] = { //Mapowanie znaków klawiatury
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char klucz[4] = {'1','2','3','4'}; // domyslny klucz
char proba[4];
int z=0;

void setup()
{
   Serial.begin(9600);
   Serial.println("Enter password:");
}

// wykonywane jak poprawny klucz
void correctKEY() 
{
   Serial.println(" Password ACCEPTED...");
}

// wykonywane jeśli błędny klucz
void incorrectKEY() 
{
   Serial.println("Password REJECTED!");
}

// Sprawdzanie klucza
void checkKEY()
{
   int correct=0;
   for (int i = 0; i < 4 ; i++)
   {
      if (proba[i]==klucz[i])
      {
         correct++;
      }
   }
   if (correct==4)
   {
      correctKEY();
   }
   else
   {
      incorrectKEY();
   }
   for (int zz=0; zz<4; zz++) // zerowanie hasła tymczasowego
   {
      proba[zz]=0;
   }
}

// Odczytywanie znaków z klawiatury
void readKeypad()
{
   char klawisz = klawiatura.getKey(); 
   if (klawisz)
   {
      //Serial.print(z);
      switch(klawisz)
      {
      case '*': 
        z=0; 
        Serial.println();
        break;
      case '#':
        checkKEY();
        break;
      default:
        Serial.print("*");
        proba[z]=klawisz;
        z++;
      }
   }
   if (z == 4){
    Serial.println();
    z=0;
   }
}

void loop()
{
   readKeypad();
}
