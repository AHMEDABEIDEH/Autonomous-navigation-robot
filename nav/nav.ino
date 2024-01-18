#include <NewPing.h>

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define TRIG_PINr A2
#define ECHO_PINr A3
#define TRIG_PINfr A4 
#define ECHO_PINfr A5
#define TRIG_PINfl A8 
#define ECHO_PINfl A9
#define TRIG_PINl A10 
#define ECHO_PINl A11
#define MAX_DISTANCE 200 
#define SPEED 20 // WE SIT THE SPEED OF THE MOTOR FOR 150 USING AFMOTOR LIBRARY


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
NewPing sonarL(TRIG_PINl, ECHO_PINl, MAX_DISTANCE); //change position
NewPing sonarR(TRIG_PINr, ECHO_PINr, MAX_DISTANCE); 
NewPing sonarFR(TRIG_PINfr, ECHO_PINfr, MAX_DISTANCE); 
NewPing sonarFL(TRIG_PINfl, ECHO_PINfl, MAX_DISTANCE); 



boolean movingForward = false; //this boolean is important to indicate whether the motors are currently moving forward or not 


int distance = 45; //setting an inital random distance
int distanceRightSensor = 30; //right sensor
int distanceLeftSensor = 30; // left sensor
int distanceForwardRightSensor = 30; //right sensor
int distanceForwardLeftSensor = 30; // left sensor
int speedSet = 0;
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;

//readPing is a function we are using to assign the distance value of the intended sensor
int readPing() { 
  delay(20);
  int CM = sonar.ping_cm(); //ping_cm is a function in in NewPing library that takes the echo pin, trigger pin and the max assigned distance and returns the distance between the sensor and the obstacle
  if(CM == 0) //ultrasonic sensor waves have a max physical distance for their wave so if no data is coming back in we set it as a big value like 250 to avoid errors
  {
    CM = 250;
  }
  return CM;
}

//Similar to previous readPing function except for the right mounted sensor
int readPingL() { 
  delay(20);
  int CM = sonarL.ping_cm();
  if(CM == 0)
  {
    CM = 250;
  }
  return CM;
}

//Similar to previous readPing function except for the left mounted sensor
int readPingR() { 
  delay(20);
  int CM = sonarR.ping_cm();
  if(CM == 0)
  {
    CM = 250;
  }
  return CM;
}

int readPingFR() { 
  delay(20);
  int CM = sonarFR.ping_cm();
  if(CM == 0)
  {
    CM = 250;
  }
  return CM;
}

int readPingFL() { 
  delay(20);
  int CM = sonarFL.ping_cm();
  if(CM == 0)
  {
    CM = 250;
  }
  return CM;
}



void SpeedNormal(){

    analogWrite(enA, 70); //motor 1
    analogWrite(enB, 70); //motor 2
	  delay(5);
}

//motor stop function to stop the motors from spinning
void moveStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  movingForward = false;
  } 

//Function to make all motors spin clockwise (forward movement)
void moveForward() {

 if(movingForward == false)
  {
    movingForward = true;
    SpeedNormal();
 
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
	  delay(5);
  }
}

void moveBackward() {
    movingForward = false;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(5);
}




void turnRight()
{
      analogWrite(enA, 110); //motor 1
      analogWrite(enB, 110); //motor 2
      delay(5);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      delay(5);
}

void turnLeft()
{
      analogWrite(enA, 110); //motor 1
      analogWrite(enB, 110); //motor 2
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      delay(5);
}





void setup() {
  Serial.begin(9600);
  delay(15000);
  distance = readPing(); // we repeat each distance assigning more than 1 time incase of an error reading that might occur at the start
  delay(100);
  distanceForwardRightSensor = readPingFR();
  delay(100);
  distanceForwardLeftSensor = readPingFL();
  delay(100);
  distanceRightSensor = readPingR();
  delay(100);
  distanceLeftSensor = readPingL();
  delay(100);

}

void loop() {

  if(distance>=30 && distanceForwardRightSensor > 10 && distanceForwardLeftSensor > 10)
  {
    if(distanceRightSensor <= 90 && distanceRightSensor >= 5)
    {
      while(distance >= 30 && distanceForwardRightSensor > 11 && distanceForwardLeftSensor > 11)
      {
        if(distanceRightSensor <= 18)
        {
          moveStop();
          turnLeft();
          Serial.println("RIGHT WALL CLOSE TURNING LEFT!!");
          delay(50);
          moveStop();
          moveForward();
          delay(70);
        }
        else if (distanceRightSensor >= 50 && distanceRightSensor <= 80)
        {
          moveStop();
          turnRight();
          Serial.println("RIGHT WALL FAR TURNING RIGHT!!");
          delay(50);
          moveStop();
          moveForward();
          delay(70);
          
        }
        else if (distanceRightSensor >= 125)
        {
          moveStop();
          turnRight(); //need to code this function
          delay(500);
          moveStop();
          moveForward();
          delay(500);
          Serial.println("new right, right wall");
        }
        else
        {
        moveForward();
        delay(5);
        Serial.println("moving forward, right wall");
        }
        distance = readPing();
        delay(10);
        distanceForwardRightSensor = readPingFR();
        delay(10);
        distanceForwardLeftSensor = readPingFL();
        delay(10);
        distanceRightSensor = readPingR();
        delay(10);
        distanceLeftSensor = readPingL();
        delay(10);
        char buffer[100];
        sprintf(buffer, "NEW READINGS INSIDE WHILE OF RIGHT WALLS Values are: %d -- %d -- %d -- %d -- %d", distance, distanceForwardRightSensor, distanceForwardLeftSensor, distanceRightSensor, distanceLeftSensor);
        Serial.println(buffer);            
      }
        
        turnLeft();
        delay(10);
        Serial.println("turning left obstacle ahead!!");
        distance = readPing();
        delay(10);
        distanceForwardRightSensor = readPingFR();
        delay(10);
        distanceForwardLeftSensor = readPingFL();
        delay(10);
        distanceRightSensor = readPingR();
        delay(10);
        distanceLeftSensor = readPingL();
        delay(10);        
      
    }
    else if(distanceLeftSensor <= 80 && distanceLeftSensor >= 5)
    {
      while(distance >= 35 && distanceForwardRightSensor > 11 && distanceForwardLeftSensor > 11)
      {
        if(distanceLeftSensor <= 18)
        {
          moveStop();
          turnRight();
          Serial.println("LEFT WALL FAR CLOSE RIGHT!!");
          delay(40);
          moveStop();
          moveForward();
          delay(60);
          
        }
        else if (distanceLeftSensor >= 50 && distanceLeftSensor <= 80)
        {
          moveStop();
          turnLeft();
          Serial.println("LEFT WALL FAR TURNING LEFT!!");
          delay(40);
          moveStop();
          moveForward();
          delay(60);
          
        }
        else if (distanceLeftSensor >= 125)
        {
          moveStop();
          turnLeft(); //need to code this function
          delay(400);
          moveStop();
          moveForward();
          delay(400);
          Serial.println("new left, left wall");
        }
        else
        {
        moveForward();
        delay(5);
        }
        distance = readPing();
        delay(10);
        distanceForwardRightSensor = readPingFR();
        delay(10);
        distanceForwardLeftSensor = readPingFL();
        delay(10);
        distanceRightSensor = readPingR();
        delay(10);
        distanceLeftSensor = readPingL();
        delay(10);
        char buffer[100];
        sprintf(buffer, "NEW READINGS INSIDE WHILE OF LEFT WALLS Values are: %d -- %d -- %d -- %d -- %d", distance, distanceForwardRightSensor, distanceForwardLeftSensor, distanceRightSensor, distanceLeftSensor);
        Serial.println(buffer);
      }
      
        
        turnRight();
        delay(10);
        Serial.println("turning right obstacle ahead!!");
        distance = readPing();
        delay(10);
        distanceForwardRightSensor = readPingFR();
        delay(10);
        distanceForwardLeftSensor = readPingFL();
        delay(10);
        distanceRightSensor = readPingR();
        delay(10);
        distanceLeftSensor = readPingL();
        delay(10);
        Serial.println("obstacle ahead, moving right after following left walls");
        char buffer[100];
        sprintf(buffer, "Values are: %d -- %d -- %d -- %d -- %d", distance, distanceForwardRightSensor, distanceForwardLeftSensor, distanceRightSensor, distanceLeftSensor);
        Serial.println(buffer);
      
    }
    else {
      moveForward();
      delay(10);
      Serial.println("No walls to follow, moving forward");
    }
  }
  else
  {
    if(distance < 30)
    {
      if(distanceLeftSensor > distanceRightSensor)
      {
        turnLeft();
        delay(5);
      }
      else if(distanceLeftSensor < distanceRightSensor)
      {
        turnRight();
        delay(5);
      }
    }
    else if(distanceForwardRightSensor <= 10)
    {
      turnLeft();
      delay(5);
    }
    else if(distanceForwardLeftSensor <= 10)
    {
      turnRight();
      delay(5);
    }
  }

  distance = readPing();
  delay(10);
  distanceForwardRightSensor = readPingFR();
  delay(10);
  distanceForwardLeftSensor = readPingFL();
  delay(10);
  distanceRightSensor = readPingR();
  delay(10);
  distanceLeftSensor = readPingL();
  delay(10);


}