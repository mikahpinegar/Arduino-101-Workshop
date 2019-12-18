/*
Arduino workshop 101 -- Digital Theremin
Written to complement the Sparkfun Inventors Kit -- this program builds off of the buzzer project and digital trumpet 

This project acts as a Theremin 
The program reads the distance of your hand from the sensor and then plays a tone on the buzzer accordingly
The potentiometer controls the volume of the buzzer

Author -- Mikah Pinegar
Date -- 12/18/2019
*/

int speakerPin = 10;               //the pin that buzzer is connected to

const int trigPin = 11;           //connects to the trigger pin on the distance sensor       
const int echoPin = 12;           //connects to the echo pin on the distance sensor     

float myTone = 0;               //stores the distance measured by the distance sensor -- this value is used to calculate the tone of the buzzer

int currentFrequency = 0;    //the frequency that is calculated by multiplying myTone by a constant
int beatLength = 10;   //the length of one beat -- changing this value will make the tone smoother or more choppy
int beats;
int multiplier = 500    //stores the constant used to multiply myTone to get the final frequency played on the buzzer


//the code in this section runs once to setup the Arduino
void setup()
{
  pinMode(speakerPin, OUTPUT);    //set the output pin for the speaker
  pinMode(trigPin, OUTPUT);   //the trigger pin will output pulses of electricity 
  pinMode(echoPin, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

  Serial.begin (9600);        //set up a serial connection with the computer
}

//the code in this section repeats in an infinite loop
void loop()
{
  myTone = getTone();   //variable to store the distance measured by the sensor

  currentFrequency = int(myTone * multiplier);   //variable used to store the actual tone once myTone is multiplied by multiplier

  Serial.print(myTone);     //print the distance that was measured
  Serial.println(" Hz");      //print units after the distance
    
  tone(speakerPin, currentFrequency, beatLength);   
}




//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getTone()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calcualtedTone;         //variable to store the distance calculated from the echo time
  
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calcualtedTone = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  if(calcualtedTone < 2) calcualtedTone = 0;    //sets calculatedTone to 0 if the distance is less than 2 inches to make a smoother range of tones
  else if(calcualtedTone > 12) calcualtedTone = 12;   //sets calculatedTone to 12 if the distance is greater than 12 inches because there are occasional false reading of >500 inches
  return calcualtedTone;              //send back the distance that was calculated
}
