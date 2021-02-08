//Bluetooth connection of BeBlocky Game with Arduino car.
//BeBlocky sends string to bluetooth module after connected successfully.
//The strings are like "F", "R", "L",... to controll the car.
//and the car moves on grid of line. so if it accept string "F", it should move one step of the grid line and stop.
//and if the next command is "R", it should turn to the right side until the right side of the grid line and stop and the same is true for turn left.
//to controll the car move on the grid, we use three line sensors (with the middle line sensor on the grid line).
char command;
String string;
#define enA 13
#define enB 8
int Sensor1 = 0;
int Sensor2 = 0;
int Sensor3 = 0;
  void setup()
  {
    pinMode(12,OUTPUT);   //motor 1
    pinMode(11,OUTPUT);   //motor 2
    pinMode(10,OUTPUT);   //motor 3
    pinMode(9,OUTPUT);   //motor 4
    pinMode(enA,OUTPUT); //enabler 1
    pinMode(enB,OUTPUT); //enabler 2
    pinMode(Sensor1, INPUT); //the first line sensor
    pinMode(Sensor2, INPUT); //the second line sensor
    pinMode(Sensor3, INPUT); //the third line sensor
    Serial.begin(9600);
  }
  void loop()
  {
    Sensor1 = digitalRead(7);
    Sensor2 = digitalRead(6);
    Sensor3 = digitalRead(5);
    int c;
    if (Serial.available() > 0) 
    {
      string = "";
    }
  
    if(Serial.available() > 0)
    {
       command = ((byte)Serial.read());
        string += command;
        Serial.println(string);
    }
    if(string == "F")
    {
      //when all the 3 sensors detect the line => stop b/c the car may be at the turn point.
      if(c==0 && Sensor1 == HIGH && Sensor2 == HIGH && Sensor3 == HIGH){
        Stop();
        c=2;
        delay(100);
      }
      //when the car miss the line and move to the left side of the line
      if((Sensor1 == LOW && Sensor2 == LOW && Sensor3 == HIGH) ||
         (Sensor1 == LOW && Sensor2 == HIGH && Sensor3 == HIGH) ||
         (c==1 && (Sensor1 == LOW && Sensor2 == LOW && Sensor3 == LOW)))
         {
          Right();
          c=1;
          }
      //when the car miss the line and move to the riht side of the line
      else if((Sensor1 == HIGH && Sensor2 == LOW && Sensor3 == LOW) ||
              (Sensor1 == HIGH && Sensor2 == HIGH && Sensor3 == LOW) ||
              (c==-1 && (Sensor1 == LOW && Sensor2 == LOW && Sensor3 == LOW))
              {
                Left();
                c=-1;
               }
      else{
        Forward();
        c=0;
      }
    }
    else if(string =="B")
    {
        Backward();
    }
    else if(string =="R")
    {
      //when it turn to the right if the second sensor detect the line and the others not, the car finished the turn.
      if(Sensor1 == LOW && Sensor2 == HIGH && Sensor3 == LOW){
        Stop();
      }
      else{
        Right();
      }
    }
    else if(string =="L")
    {
      //when it turn to the left if the second sensor detect the line and the others not, the car finished the turn.
     if(Sensor1 == LOW && Sensor2 == HIGH && Sensor3 == LOW){
        Stop();
      }
      else{
        Left();
      }
    }
    else if(string == "S")
    {
      Stop();
    }
    delay(500);
    Stop();
 }
void Forward()
   {
     digitalWrite(12,HIGH);
     digitalWrite(11,LOW);
     digitalWrite(10,LOW);
     digitalWrite(9,HIGH);
     analogWrite(enA, 150);
     analogWrite(enB, 150);
    }
 void Backward()
 {
     digitalWrite(12,LOW);
     digitalWrite(11,HIGH);
     digitalWrite(10,HIGH);
     digitalWrite(9,LOW);
     analogWrite(enA, 150);
     analogWrite(enB, 150);
 }
  void Right()
 {
     digitalWrite(12,HIGH);
     digitalWrite(11,LOW);
     digitalWrite(10,LOW);
     digitalWrite(9,LOW);
     analogWrite(enB, 130);
 }
  void Left()
 {
     digitalWrite(12,LOW);
     digitalWrite(11,LOW);
     digitalWrite(10,LOW);
     digitalWrite(9,HIGH);
     analogWrite(enA, 130);
 }
 void Stop()
 {
     digitalWrite(12,LOW);
     digitalWrite(11,LOW);
     digitalWrite(10,LOW);
     digitalWrite(9,LOW);
 }
 

    
