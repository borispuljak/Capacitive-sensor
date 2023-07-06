const int UDA = 2;
const int INCA = 3;
const int CS10kA = 4;
const int CS1kA = 5;
const int POWA = 6;

const int UDB = 8;
const int INCB = 9;
const int CS10kB = 10;
const int CS1kB = 11;
const int POWB = 12;

void setup() {
    pinMode(CS10kA,OUTPUT);
    pinMode(CS1kA,OUTPUT);
    pinMode(UDA,OUTPUT);
    pinMode(INCA,OUTPUT);
    pinMode(POWA,OUTPUT);
    pinMode(A0,INPUT);
    pinMode(CS10kB,OUTPUT);
    pinMode(CS1kB,OUTPUT);
    pinMode(UDB,OUTPUT);
    pinMode(INCB,OUTPUT);
    pinMode(POWB,OUTPUT);
    pinMode(A1,INPUT);
    digitalWrite(POWA,HIGH);
    digitalWrite(POWB,HIGH);
    digitalWrite(INCA,HIGH);
    digitalWrite(UDA,LOW);
    digitalWrite(CS10kA,HIGH);
    digitalWrite(CS1kA,HIGH);
    digitalWrite(INCB,HIGH);
    digitalWrite(UDB,LOW);
    digitalWrite(CS10kB,HIGH);
    digitalWrite(CS1kB,HIGH);
    Serial.begin(9600);
    // petlja za stavit pot na min
    for (int i = 0; i < 100; i++) {
        potDown1kA();
        potDown10kA();
        potDown1kB();
        potDown10kB();
    }
    // inicijalna kalibracija:
    // povećavam pot dok ne prijeđe threshold
    for (int j = 0; j < 100; j++) {
      Serial.print(0);
      Serial.print(" ");
      Serial.print(1200);
      Serial.print(" ");
      Serial.print(analogRead(A0));
      Serial.print(" ");
      if (analogRead(A0) < 900) {
        Serial.print(" ");
        Serial.print(400);
        Serial.print(" ");
        potUp10kA();
      }
      Serial.print(analogRead(A1));
      Serial.println(" ");
      if (analogRead(A1) < 900) {
        Serial.print(" ");
        Serial.print(400);
        Serial.print(" ");
        potUp10kB();
      }
    }
}

void loop() {
    Serial.print(0);
    Serial.print(" ");
    Serial.print(1200);
    Serial.print(" ");
    Serial.print(analogRead(A0));
    //Serial.print(" ");
    //Serial.print(analogRead(A1));
    Serial.println(" ");
    if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    // "q" na tipkovnici povećava vrijednost pota 1kA
    if (incomingByte == 113) {
      potDown10kA();
    }
    // "a" na tipkovnici smanjuje vrijednost pota 1kA
    if (incomingByte == 97) {
      potUp10kA();
    }
    // "w" na tipkovnici povećava vrijednost pota 1kB
    if (incomingByte == 119) {
      potDown1kA();
    }
    // "s" na tipkovnici smanjuje vrijednost pota 1kB
    if (incomingByte == 115) {
      potUp1kA();
    }
    // "0" postavlja 1k potove na sredinu
    if (incomingByte == 48) {
      for (int i = 0; i < 100; i++) {
        potUp1kA();
        potUp1kB();
        potUp10kA();
        potUp10kB();
        
      }
      for (int j = 0; j < 50; j++) {
        potDown1kA();
        potDown1kB();
        potDown10kA();
        potDown10kB();
      }
    }
  }
}

void potUp10kA(){
  digitalWrite(CS10kA,LOW);
  digitalWrite(UDA,HIGH);
  digitalWrite(INCA,LOW);
  delay(10);
  digitalWrite(INCA,HIGH);
  delay(10);
  digitalWrite(CS10kA,HIGH);
}

void potDown10kA(){
  digitalWrite(CS10kA,LOW);
  digitalWrite(UDA,LOW);
  digitalWrite(INCA,LOW);
  delay(10);
  digitalWrite(INCA,HIGH);
  delay(10);
  digitalWrite(CS10kA,HIGH);
}

void potUp1kA(){
  digitalWrite(CS1kA,LOW);
  digitalWrite(UDA,HIGH);
  digitalWrite(INCA,LOW);
  delay(10);
  digitalWrite(INCA,HIGH);
  delay(10);
  digitalWrite(CS1kA,HIGH);
}

void potDown1kA(){
  digitalWrite(CS1kA,LOW);
  digitalWrite(UDA,LOW);
  digitalWrite(INCA,LOW);
  delay(10);
  digitalWrite(INCA,HIGH);
  delay(10);
  digitalWrite(CS1kA,HIGH);
}

void potUp10kB(){
  digitalWrite(CS10kB,LOW);
  digitalWrite(UDB,HIGH);
  digitalWrite(INCB,LOW);
  delay(10);
  digitalWrite(INCB,HIGH);
  delay(10);
  digitalWrite(CS10kB,HIGH);
}

void potDown10kB(){
  digitalWrite(CS10kB,LOW);
  digitalWrite(UDB,LOW);
  digitalWrite(INCB,LOW);
  delay(10);
  digitalWrite(INCB,HIGH);
  delay(10);
  digitalWrite(CS10kB,HIGH);
}

void potUp1kB(){
  digitalWrite(CS1kB,LOW);
  digitalWrite(UDB,HIGH);
  digitalWrite(INCB,LOW);
  delay(10);
  digitalWrite(INCB,HIGH);
  delay(10);
  digitalWrite(CS1kB,HIGH);
}

void potDown1kB(){
  digitalWrite(CS1kB,LOW);
  digitalWrite(UDB,LOW);
  digitalWrite(INCB,LOW);
  delay(10);
  digitalWrite(INCB,HIGH);
  delay(10);
  digitalWrite(CS1kB,HIGH);
}
