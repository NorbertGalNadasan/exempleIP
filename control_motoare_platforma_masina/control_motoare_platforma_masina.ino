
//https://web.archive.org/web/20151214164138/http://www.robofun.ro/shield-motoare-l298-v2?search=l298



int MOTOR2_PIN1 = 3;
int MOTOR2_PIN2 = 5;
int MOTOR1_PIN1 = 6;
int MOTOR1_PIN2 = 9;

char direction;
     // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
   
    if (Serial1.available()) {       // If anything comes in Serial1 (pins 0 & 1)
    direction = Serial1.read();
    Serial.print(direction);
    }

  switch (direction) {
  case 'F':
    // statements
     go(50,50); 
     delay(500);
    break;
  case 'B':
    go(-50,-50);
    delay(500);
    // statements
    break;
  case 'L':
   go(50,0);delay(500);
   break;
   case 'R':
   go(0,50);delay(500);
   break;
  default:
    go(0,0);
  break;
}
}

void go(int speedLeft, int speedRight) {
  if (speedLeft > 0) {
   
    analogWrite(MOTOR1_PIN1, speedLeft);
    Serial.println("left");
    analogWrite(MOTOR1_PIN2, 0);
  } 
  else {
    analogWrite(MOTOR1_PIN1, 0);
    analogWrite(MOTOR1_PIN2, -speedLeft);
  }
 
  if (speedRight > 0) {
    analogWrite(MOTOR2_PIN1, speedRight);
    Serial.println("right");
    analogWrite(MOTOR2_PIN2, 0);
  }else {
    analogWrite(MOTOR2_PIN1, 0);
    analogWrite(MOTOR2_PIN2, -speedRight);
  }
}
