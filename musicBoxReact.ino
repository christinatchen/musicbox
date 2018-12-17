/****************************************************************************** 
SparkFun Spectrum Shield Demo
Toni Klopfenstein @ SparkFun Electronics
December 2015
https://github.com/sparkfun/Spectrum_Shield

This sketch shows the basic functionality of the Spectrum Shield, working with a basic RGB LED Matrix.

The Spectrum Shield code is based off of the original demo sketch by Ben Moyes @Bliptronics.  
This sketch is available in the Spectrum Shield repository. 

Development environment specifics:
Developed in Arduino 1.6.

This code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given.
*********************************************************************************/

//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1 


//Define LED connections on the Arduino/Shield
int LED[] = {6, 7, 8, 9, 10, 11, 12};

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7]; 
int i;
int vibMotor = 5;
/********************Setup Loop*************************/
void setup() {

  Serial.begin(9600);
  
  //Set LED pin configurations
  for(i=0; i<7; i++)
  {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH);
    //Serial.println(i);
    //Serial.println("turned on");
  }

  pinMode(vibMotor, OUTPUT);
  digitalWrite(vibMotor, LOW);
  
  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);  
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);
  
  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
}


/**************************Main Function Loop*****************************/
void loop() {
  
    Read_Frequencies();
    Graph_Frequencies();
    delay(50);
}


/*******************Pull frequencies from Spectrum Shield********************/
void Read_Frequencies(){
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two); 
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}

/*******************Light LEDs based on frequencies*****************************/

void Graph_Frequencies(){
   for( i= 0; i<7; i++)
   {
     if(Frequencies_Two[i] > Frequencies_One[i]){
      if (((i == 0) || (i == 5) ||(i == 4) || (i == 11)) && (Frequencies_Two[i]/5 < 200)){
        analogWrite(LED[i], 0);
        //analogWrite(LED[i], Frequencies_Two[i]/5);
      }else if (((i == 0) || (i == 5)) && (Frequencies_Two[i]/5 < 205)){
        analogWrite(LED[i], 0);
        //Serial.println(Frequencies_Two[i]/5);
        //analogWrite(LED[i], Frequencies_Two[i]/5);  
      }else{
        analogWrite(LED[i], Frequencies_Two[i]/5);
         if (((i == 2) || (i == 3)) && (Frequencies_Two[i]/5 > 120)){
          //Serial.print("freq 2");
          //Serial.println(Frequencies_Two[i]/5);
          digitalWrite(vibMotor, HIGH);
        }
      }
            
     }else{
        analogWrite(LED[i], Frequencies_One[i]/5);
         if (((i == 2) || (i == 3))&& (Frequencies_One[i]/5 > 120)){
          //Serial.print("freq 1");
          //Serial.println(Frequencies_One[i]/5);
          digitalWrite(vibMotor, LOW);
        }
     }
   }
}