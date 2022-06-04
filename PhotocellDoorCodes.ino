#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <Thread.h>

#define DEG_PER_STEP 1.8
#define STEP_PER_REVOLUTION (360 / DEG_PER_STEP)

AccelStepper stepper(AccelStepper::FULL4WIRE, 3,4,5,6);
Thread myThread = Thread();

long moveToPosition = -1 * (STEP_PER_REVOLUTION + 350); //-550
String data = "";
const int trigger_pin = 8;
const int echo_pin = 9;
long motorPosition = 0;
long newPosition = 0;
long pirInputPin = 10;
int val = 0; // variable for reading the pin status 


int sure;
int mesafe;

void YakinlikSensoru(){
    digitalWrite(trigger_pin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(trigger_pin, LOW);
      sure = pulseIn(echo_pin, HIGH);
      mesafe = (sure/2) / 29.1;
//      Serial.println(mesafe);
}

void KapiAcKapa(){
    stepper.setCurrentPosition(0);
    moveToPosition = -1 * moveToPosition; //+550
    stepper.moveTo(moveToPosition);
    while (stepper.currentPosition() != moveToPosition){
      stepper.run();
     }
    delay(3000);
    stepper.setCurrentPosition(0);
    moveToPosition = -1 * moveToPosition; // -550
    stepper.moveTo(moveToPosition);
    while (stepper.currentPosition() != moveToPosition){
      
      if(myThread.shouldRun())
          myThread.run();
      if (mesafe < 18 && mesafe > 0) {
        delay(100);
        motorPosition = stepper.currentPosition();
        stepper.setCurrentPosition(0);
        newPosition =  (-1 * motorPosition) - 1;
        stepper.moveTo(newPosition);
        while(stepper.currentPosition() != newPosition){
          stepper.run();
          }
        stepper.setCurrentPosition(0);
        stepper.moveTo(moveToPosition);
        delay(2000);
       }else {
        stepper.run();
      }
     }  
     delay(1000); 
}

void setup() {
  Serial.begin(9600);

  stepper.setAcceleration(700.0); // set acceleration
  stepper.setSpeed(100);          // set initial speed
  stepper.setCurrentPosition(0);  // set position to 0

  lcd.begin();
  
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(pirInputPin, INPUT); // declare sensor as input 
  myThread.onRun(YakinlikSensoru);
  myThread.setInterval(200);
//  stepper.moveTo(STEP_PER_REVOLUTION); // move motor one revolution, in clockwise direction
//  Serial.println("Motor moving in clockwise direction");
}

void loop() {
  val = digitalRead(pirInputPin);
  if (val == HIGH) { // check if the input is HIGH 
    KapiAcKapa();
  }else {
    while (Serial.available())    //whatever the data that is coming in serially and assigning the value to the variable “data”
  { 
    data = Serial.readString();
    lcd.setCursor(3,0); // İlk satırın başlangıç noktası
    lcd.print("Merhabalar");
    if (data.length() % 2 == 1){
    lcd.setCursor(((12-data.length())/2),1); // İkinci satırın başlangıç noktası
    }
    else {
    lcd.setCursor(((12-data.length())/2),1);  
    }
    lcd.print(data + " Bey");
    // Motor
    KapiAcKapa();
     Serial.println("Kapi Kapandi");
    lcd.clear();
  }
    }
  
  lcd.setCursor(4,0); // İlk satırın başlangıç noktası
  lcd.print("BITIRME");
  lcd.setCursor(4,1); // İkinci satırın başlangıç noktası
  lcd.print("PROJESI");
  delay(500);
}
