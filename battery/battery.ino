#include <Servo.h>
#include <BluetoothSerial.h>

int TRIGGER_DISTANCE = 5;
//#define signalPin 12

#define triggerPin 12
#define echoPin 27

Servo myservo1;
Servo myservo2;
BluetoothSerial BT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  BT.begin("003");//請改名
  
  myservo1.attach(13); // 連接數位腳位13，伺服馬達的訊號線
  myservo2.attach(14);
}

int distance() {
  long cm;
//  pinMode(signalPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
//  pinMode(signalPin, INPUT);
  cm = pulseIn(echoPin, HIGH)/58;    
  delay(250);
  return cm;
}

boolean battery() {
    Serial.print(distance());
  Serial.print("cm");
  Serial.println();
    if(distance()<TRIGGER_DISTANCE){return 1;}
    else {return 0;}
  }

//動作
void block1(int numSpeed, int numDelay) {
  for(int i = 0; i <= 90; i+=numSpeed){
    myservo1.write(i); // 使用write，傳入角度，從0度轉到180度
    delay(numDelay);
  }
}

void pass1(int numSpeed, int numDelay) {
  for(int i = 90; i >= 0; i-=numSpeed){
    myservo1.write(i);// 使用write，傳入角度，從180度轉到0度
    delay(numDelay);
  }
}

void block2(int numSpeed, int numDelay) {
  for(int i = 0; i <= 90; i+=numSpeed){
    myservo2.write(i); // 使用write，傳入角度，從0度轉到180度
    delay(numDelay);
  }
}

void pass2(int numSpeed, int numDelay) {
  for(int i = 90; i >= 0; i-=numSpeed){
    myservo2.write(i);// 使用write，傳入角度，從180度轉到0度
    delay(numDelay);
  }
}
void loop() {
  
  while (BT.available()){
    char BTch = char(BT.read());
    Serial.println(BTch);
    if(BTch == 'a'){
      if(battery() == 1){
        BT.write('b');
      }
    }
    else if(BTch == 'w'){
      pass1(3,10);
      block1(3,10);
      pass2(3,10);
      block2(3,10);
    }
  } 
  delay(1);

//  byte BTch[20];
//  int strsize;
//  
//  while (BT.available()){
//    if((strsize = (BT.available())) > 0){
//      for (int i = 0; i < strsize; i++) {
//        BTch[0] = char(BT.read());
//      }
//      Serial.println(BTch[0]);
//     }
//    if(BTch[0] == 'a'){
//      if(battery() == 1){
//        BT.write('b');
//        delay(1);
//      }
//    }
//    else if(BTch[0] == 'w'){
//      pass1(3,10);
//      block1(3,10);
//      pass2(3,10);
//      block2(3,10);
//      BTch[0] = ' ';
//    }
//  } 
//  delay(1);

}
