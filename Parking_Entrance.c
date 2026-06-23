// biblioteca pentru servo motor
#include <Servo.h> 
#include <Wire.h>
// biblioteca pentru ecranul LCD
#include <LiquidCrystal_I2C.h> 

//declararea ecranului LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
//declararea motorului
Servo servo; 

// declararea și inițializarea variabilelor angle și k
int angle = 1, k = 4; 
// declararea variabilelor pentru valorile senzorilor
unsigned int AVant0, AV0, AVant1, AV1; 

void setup() {
  //funcție care arată unde a fost conectat motorul
  servo.attach(8); 
  //funcție care setează motorul la un anumit unghi
  servo.write(angle); 
  // pentru a putea afișa în Serial Monitor
  Serial.begin(9600);
  // funcții pentru ecranul LCD 
  lcd.init(); 
  lcd.clear();
  lcd.backlight();
 // setarea locului unde se va afișa propoziția pe ecranul LCD
  lcd.setCursor(0,0);
  // afișarea propoziției "Locuri libere: " (se afișeaza doar o dată)
  lcd.print("Locuri libere: "); 
  // inițializarea variabilei anterioare 0
  AVant0 = analogRead(A0); 
  // inițializarea variabilei anterioare 1
  AVant1 = analogRead(A1); 
}

void loop() {
  
  Serial.println(" ");

  // delay pentru ca valoarea curentă și cea anterioară să nu aibă aceeași valoare
  delay(500); 

  //AV0 primește valoarea curentă a senzorului 0
  AV0 = analogRead(A0); 
  //AV1 primește valoarea curentă a senzorului 1
  AV1 = analogRead(A1); 

  // setarea cursorului pentru afișarea pe LCD a numărului de locuri (k)
  lcd.setCursor(15,0);
  // afișarea pe LCD a numărului de locuri (k) 
  lcd.print(k); 

  // afișarea valorilor primite de la senzorul 0
  Serial.println("Senzor0 : "); 
  Serial.println("AV0: ");
  Serial.println(AV0);
  Serial.println("AVant0: ");
  Serial.println(AVant0);

  delay(1000);

  // verificare ca numărul k să nu fie mai mic sau egal cu 0
  if(k > 0){ 
    // compararea valorilor senzorului 0
    if(AV0 > AVant0 + 20){ 
      // decrementarea lui k
      k--; 

      // ridicarea barierei                          
      for(angle = 1; angle < 90; angle++){ 
        servo.write(angle);               
        delay(15);                   
      } 

      // delay pentru ca mașina să intre în parcare
      delay(5000); 

      // coborârea barierei                            
      for(angle = 90; angle > 1; angle--){
        servo.write(angle);           
        delay(15);       
      } 
    }
  }

  // afișarea valorilor senzorului 1
  Serial.println("Senzor1 : "); 
  Serial.println("AV1: ");
  Serial.println(AV1);
  Serial.println("AVant1: ");
  Serial.println(AVant1);

  delay(1000);

  // verificarea ca numărul k să nu fie mai mare de 4 (câte locuri sunt în total)
  if(k < 4){ 
    // compararea valorilor senzorului 1
    if(AV1 > AVant1 + 20){ 
      // incrementarea lui k
      k++; 

      // ridicarea barierei                               
      for(angle = 1; angle < 90; angle++){ 
        servo.write(angle);               
        delay(15);                   
      } 
  
      // delay pentru ca mașina să iasă din parcare
      delay(5000); 

      // coborârea barierei                             
      for(angle = 90; angle > 1; angle--){ 
        servo.write(angle);           
        delay(15);       
      } 
    }
  }
  
  // resetarea valorii anterioare 0
  AVant0 = AV0; 
  // resetarea valorii anterioare 1
  AVant1 = AV1; 

  Serial.println("-------------------------------------------------");

}

