// IRremote Library
//#include <IRremote.h>                               // Include IRremote library
//#define RECV_PIN 3                                  // Connect IR receiver pin 3

// Motor A Pins                                     // Left Motor Pins
#define ENA 10                                      // Connect ENA to pin 10
#define IN1 9                                       // Connect IN1 to pin 9
#define IN2 8                                       // Connect IN2 to pin 8

// Motor B Pins                                     // Right Motor Pins
#define ENB 5                                       // Connect ENB to pin 5
#define IN3 7                                       // Connect IN3 to pin 7
#define IN4 6                                       // Connect IN4 to pin 6

int Speed = 200;                                    // Variable to store the car speed (PWM)
//int command;                                        // Variable to store the infrared command

//ultrasonic sensor Forward
const int trigPinF = 11;//Trigger Pin of Ultrasonic
const int echoPinF = A2;//Echo Pin of Ultrasonic

//ultrasonic sensor Right
const int trigPinR = 13;//Trigger Pin of Ultrasonic
const int echoPinR = A0;//Echo Pin of Ultrasonic

//ultrasonic sensor Left
const int trigPinL = A1;//Trigger Pin of Ultrasonic
const int echoPinL = 3;//Echo Pin of Ultrasonic

long tF; // Variable to hold the time
long tL; // Variable to hold the time
long tR; // Variable to hold the time
int distanceF; // Variable to hold the distance
int distanceR; // Variable to hold the distance
int distanceL; // Variable to hold the distance


void setup() {
  Serial.begin(9600);                               // Begin serial communication at 9600 baud rate
//  IrReceiver.begin(RECV_PIN);                       // Start the receiver

  pinMode(ENA, OUTPUT);                             // Set ENA pin as output
  pinMode(ENB, OUTPUT);                             // Set ENB pin as output
  pinMode(IN1, OUTPUT);                             // Set IN1 pin as output
  pinMode(IN2, OUTPUT);                             // Set IN2 pin as output
  pinMode(IN3, OUTPUT);                             // Set IN3 pin as output
  pinMode(IN4, OUTPUT);                             // Set IN4 pin as output
  pinMode(trigPinF, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinF, INPUT); // Sets the echoPin as an Input
  pinMode(trigPinR, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinR, INPUT); // Sets the echoPin as an Input
  pinMode(trigPinL, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinL, INPUT); // Sets the echoPin as an Input
}

void loop() {

  distanceF=ultrasonicF();//take ultrasonic distance value
  if(distanceF>30)//if greater than 30 Cm
  {
    move_forward();//go to forward
          Serial.print("Forward");

  }else 
  {
    if(distanceF<=10&&distanceF>2)move_backward();// if close to object reverse to get more space to change orientation
    stop_car();                   //stop robot
    distanceR=ultrasonicR();  //get ultrasonic value at right
    delay(300);
    distanceL=ultrasonicL();  //get ultrasonic value at left
    delay(300);
    comparison(distanceR, distanceL); //go to Comparasion function
    stop_car();                    // stop after execute Comparison function action
    delay(150);
  }
//    Serial.print(distanceF);
//    Serial.print(distanceR);
//    Serial.print(distanceL);

    // reset all variables
  distanceR=0;
  distanceL=0;
  distanceF=0;








  //  if (IrReceiver.decode()) {                        // If a button is pressed
  //    command = IrReceiver.decodedIRData.command;     // Get the infrared command
  //    Serial.println(command, HEX);                   // Print button command in hexadecimal
  //
  //    switch(command){                                // Check the infrared command
  //      case 0x1E:                                    // Stop car
  //        stop_car();       break;
  //      case 0x5:                                     // Move forward
  //        move_forward();   break;
  //      case 0x1B:                                    // Move backward
  //        move_backward();  break;
  //      case 0x9:                                     // Turn right
  //        turn_right();     break;
  //      case 0x7:                                     // Turn left
  //        turn_left();      break;
  //    }
  //
  //    IrReceiver.resume();                            // Receive the next value
  //  }
  //
  //  delay(20);                                        // Short delay
}


//Function comparision

void comparison(int r, int l)//compare values of right and left Servo Pos 
{
  if(r>25||l>25)
  {
   if(r>l||r==l)
   {
     turn_right();
//       Serial.print("right");
       Serial.print(distanceR);


   }else if(l>r)
   {
     turn_left();
//           Serial.print(distanceL);
//           Serial.print("left");


   }
  }else if(r<25&&l<25)
  {
    ///*********////////////
    stop_car();
//    Serial.print("Stop");

  }
}
//Calculate distance Forward

int ultrasonicF(void)//get distance captured by ultrasonic sensor
{
  distanceF=0;
  // Clears the trigPin
digitalWrite(trigPinF, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPinF, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinF, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
tF = pulseIn(echoPinF, HIGH);
// Calculating the distance
distanceF= tF*0.0343/2;
return distanceF;
}

//calculate diatance right
int ultrasonicR(void)//get distance captured by ultrasonic sensor
{
  distanceR=0;
  // Clears the trigPin
digitalWrite(trigPinR, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPinR, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinR, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
tR = pulseIn(echoPinR, HIGH);
// Calculating the distance
distanceR= tR*0.0342/2;
return distanceR;
}

//calculate diatance Left
int ultrasonicL(void)//get distance captured by ultrasonic sensor
{
  distanceL=0;
  // Clears the trigPin
digitalWrite(trigPinL, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPinL, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinL, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
tL = pulseIn(echoPinL, HIGH);
// Calculating the distance
distanceL= tL*0.0343/2;
return distanceL;
}





// Stop the car by setting INs to LOW
void stop_car() {
  // Motor A                                        // Stop Left Motor
  digitalWrite(IN1, LOW);                           // Set IN1 to LOW
  digitalWrite(IN2, LOW);                           // Set IN2 to LOW
  analogWrite(ENA, 0);                              // Set motor A speed to 0

  // Motor B                                        // Stop Right Motor
  digitalWrite(IN3, LOW);                           // Set IN3 to LOW
  digitalWrite(IN4, LOW);                           // Set IN4 to LOW
  analogWrite(ENB, 0);                              // Set motor B speed to 0
}



// Move the car forward by moving both motors
void move_forward() {
  // Motor A                                        // Move Left Motor
  digitalWrite(IN1, HIGH);                          // Set IN1 to HIGH
  digitalWrite(IN2, LOW);                           // Set IN2 to LOW
  analogWrite(ENA, 130);                          // Set motor A speed

  // Motor B                                        // Move Right Motor
  digitalWrite(IN3, HIGH);                          // Set IN3 to HIGH
  digitalWrite(IN4, LOW);                           // Set IN4 to LOW
  analogWrite(ENB, 130);                          // Set motor B speed
}

// Move the car backward by moving both motors in reverse
void move_backward() {
  // Motor A                                        // Move Left Motor in Reverse
  digitalWrite(IN1, LOW);                           // Set IN1 to LOW
  digitalWrite(IN2, HIGH);                          // Set IN2 to HIGH
  analogWrite(ENA, 140);                          // Set motor A speed

  // Motor B                                        // Move Right Motor in Reverse
  digitalWrite(IN3, LOW);                           // Set IN3 to LOW
  digitalWrite(IN4, HIGH);                          // Set IN4 to HIGH
  analogWrite(ENB, 140);                          // Set motor B speed
    delay(450);

}

// Turn the car right by moving left moror, and stopping right motor
void turn_right() {
  // Motor A                                        // Move Left Motor
  digitalWrite(IN1, HIGH);                          // Set IN1 to HIGH
  digitalWrite(IN2, LOW);                           // Set IN2 to LOW
  analogWrite(ENA, 150);                          // Set motor A speed

  // Motor B                                        // Stop Right Motor
  digitalWrite(IN3, LOW);                           // Set IN3 to LOW
  digitalWrite(IN4, LOW);                           // Set IN4 to LOW
  analogWrite(ENB, 0);  // Set motor B speed to 0
  delay(750);  

}

// Turn the car left by stopping left motor, and moving right motor
void turn_left() {
  // Motor A                                        // Stop Left Motor
  digitalWrite(IN1, LOW);                           // Set IN1 to LOW
  digitalWrite(IN2, LOW);                           // Set IN2 to LOW
  analogWrite(ENA, 0);                              // Set motor A speed to 0

  // Motor B                                        // Move Right Motor
  digitalWrite(IN3, HIGH);                          // Set IN3 to HIGH
  digitalWrite(IN4, LOW);                           // Set IN4 to LOW
  analogWrite(ENB, 160);                          // Set motor B speed
  delay(650);

}

//void Tleft180()
//{
//  analogWrite(ENA,150);
//  analogWrite(ENB,150);
//  digitalWrite(IN1,LOW);
//  digitalWrite(IN2,HIGH);
//  digitalWrite(IN3,HIGH);
//  digitalWrite(IN4,LOW);
//  delay(1500);
//}
