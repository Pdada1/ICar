//motor values
int speedA = 3;
int directionA = 12;
int speedB = 11;
int directionB =13;

//LED values
const int LED = 8;

//sensor values
const int THRESHOLD = 40; //try fiddling
const int MID = A0;
const int LEFT = A1;
const int RIGHT = A2;
//light inputs for LDR reading
int midLight=0;
int leftLight=0;
int rightLight=0;

int prev=69; //0 for straight 1 for left, 2 for right

void setup() {
  //motor pin modes
  pinMode(directionA, OUTPUT);
  pinMode(directionB, OUTPUT);

  //LED pin modes
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  //sensor pin modes
  pinMode(MID, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor
  midLight = analogRead(MID);
  leftLight = analogRead(LEFT);
  rightLight = analogRead(RIGHT);
  // print the sensor reading so you know its range
  Serial.print(leftLight);
  Serial.print(" ");
  Serial.print(midLight);
  Serial.print(" ");
  Serial.print(rightLight);

  if(midLight > THRESHOLD) {//too far right middle LDR sees black
    //rotate left around left wheel
    digitalWrite(directionB,LOW);
    analogWrite(speedB,80);
    digitalWrite(directionA,HIGH);
    analogWrite(speedA,50);
    prev = 1;
  }

  else if(rightLight > THRESHOLD){//centered on the edge, middle LDR sees white, right LDR sees black
    //straight
    digitalWrite(directionB,HIGH);
    analogWrite(speedB,90);
    digitalWrite(directionA,HIGH);
    analogWrite(speedA,90);
    prev=0;
  }
    else { //too far left, middle and right sees white
    digitalWrite(directionB,HIGH);
    analogWrite(speedB,75);
    digitalWrite(directionA,LOW);
    analogWrite(speedA,65);
    prev=2;
  }

  delay(20);

}
