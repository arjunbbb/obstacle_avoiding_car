#include <Servo.h>
int motor1A = 2;
int motor1B = 3;
int motor2A = 4;
int motor2B = 5;
int trigPin = 10;
int echoPin = 9;
int LEDR = 8;
int LEDG = 6;
int LEDB = 7;
int BUZ = 12;
bool servod = false;

Servo s;

long duration;
int distance;
int leftDistance;
int rightDistance;

int getDistance();

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(BUZ,OUTPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  Serial.begin(9600);
  s.attach(11);
  s.write(90);
}
void loop() {
  int d = getDistance();

  if (d > 40) {
    moveForward();
    digitalWrite(LEDR, HIGH);
   digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
    s.write(90);
    servod = false;
   
  } else {
  digitalWrite(LEDR,HIGH);
  digitalWrite(LEDG, LOW);
   digitalWrite(LEDB, LOW);
    digitalWrite(BUZ,HIGH);
    stopCar();
    reverseCar();
      delay(1000);
    digitalWrite(BUZ,LOW);
    stopCar();
     if (!servod) {    
      servoScanOnce();
      servod = true;
    }
   

    if (rightDistance > leftDistance) {
       turnRight();
      delay(1000);
      moveForward();
    } else if (leftDistance > rightDistance) {
      turnLeft(); 
       delay(1000);
      moveForward();
    } else {
      Serial.println("not possible");
      digitalWrite(LEDR, HIGH);
    }{
      digitalWrite(LEDG,LOW);
      digitalWrite(LEDB,LOW);
    }
  }
}
void servoScanOnce() {
  s.write(20);
  delay(1000);
  rightDistance = getDistance();

  s.write(160);
  delay(1000);
  leftDistance = getDistance();
 delay(500);
  s.write(90); 
  delay(500);          
}
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void moveForward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}
void stopCar(){
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}

void turnRight() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  digitalWrite(LEDG,HIGH);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDB, LOW);
}

void turnLeft() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  digitalWrite(LEDB,HIGH);
  digitalWrite(LEDG, LOW); 
  digitalWrite(LEDR,LOW);
}
void reverseCar(){
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  delay(1000);
}
