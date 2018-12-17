/****************************************************************************** 
Code heavily modified from: 

SparkFun Spectrum Shield Demo
Toni Klopfenstein @ SparkFun Electronics
December 2015
https://github.com/sparkfun/Spectrum_Shield

by Christina Chen

Written for CS320: Tangible User Interfaces Project, MusicBox
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

//define vibration motor connection on Arduino/Shield
int vibMotor = 5;

/********************Setup Loop*************************/
void setup() {

  Serial.begin(9600);
  
  //Set LED pin configurations
  for(i=0; i<7; i++)
  {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
    //Serial.println(i);
    //Serial.println("turned on");
  }

  //set vibration motor configuration
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

/*******************Light LEDs and vibrate motor based on frequencies*****************************/

void Graph_Frequencies(){
   for( i= 0; i<7; i++)
   {
     if(Frequencies_Two[i] > Frequencies_One[i]){

      //cancel out frequencies created by white noise on certain pins
      if (((i == 0) || (i == 5) ||(i == 4) || (i == 11)) && (Frequencies_Two[i]/5 < 200)){
        analogWrite(LED[i], 0);
        
      //cancel out frequencies created by white noise on certain pins
      }else if (((i == 0) || (i == 5)) && (Frequencies_Two[i]/5 < 205)){
        analogWrite(LED[i], 0); 
        
      }else{
        analogWrite(LED[i], Frequencies_Two[i]/5);
         //make vibration motor correlate with certain pins
         if (((i == 2) || (i == 3)) && (Frequencies_Two[i]/5 > 120)){
          digitalWrite(vibMotor, HIGH);
        }
      }
            
     }else{
        analogWrite(LED[i], Frequencies_One[i]/5);
         //turn off vibration motor with certain pins
         if (((i == 2) || (i == 3))&& (Frequencies_One[i]/5 > 120)){
          digitalWrite(vibMotor, LOW);
        }
     }
   }
}
