/**
 * File: Robojax_L298N_DC_motor.cpp
Written by Ahmad Shamshiri (Robojax.com) on Dec 24, 2019

 * Description: This libray allows you to control 1 or 2 DC motors using L298N Dual H-bridge motor driver module

 * Author: Ahmad Shamshiri
 * Contact: robojax.com
 * Copyright: 2019 Ahmad Shamshiri
 * Version: 1.00 Dec 24, 2019


    Robojax_L298N_DC_motor is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Arduino.h"
#include "Robojax_L298N_DC_motor.h"


// -- constructor 1 for single motor -Arduino
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1,int IN2,int ENA)
{
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=ENA;
}

// -- constructor 1 for single motor with debug - Arduino
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, boolean debug)
{
    // -- pin settings
   _in1 = IN1;
   _in2 = IN2;
   _enA = ENA;
   _debug = debug;
}

// -- constructor 1 for single motor - ESP32
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int CHA)
{
#if defined(ARDUINO_ARCH_ESP32)		
  ledcSetup(CHA, this->_frequency, this->_resulotion);
  ledcAttachPin(ENA, CHA);
  _chA = CHA;
#endif  	
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=CHA;


}

// -- constructor 1 for single motor with debug - ESP32
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int CHA, boolean debug)
{
#if defined(ARDUINO_ARCH_ESP32)		
  ledcSetup(CHA, this->_frequency, this->_resulotion);
  ledcAttachPin(ENA, CHA);
  _chA = CHA;  
#endif  
    // -- pin settings
   _in1 = IN1;
   _in2 = IN2;
   _enA = CHA;
   _debug = debug;

}

// -- constructor 2 for dual motor - Ardino
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int IN3,int IN4,int ENB)
{
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=ENA;
   _in3=IN3;
   _in4=IN4;
   _enB=ENB;
   if( IN3 && IN4  && ENB)
   _dual = true;
}

// -- constructor 2 for dual motor with debug - Arduino
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1,int IN2, int ENA,int IN3,int IN4,int ENB, boolean debug)
{
#if defined(ARDUINO_ARCH_ESP32)		
  ledcSetup(0, this->_frequency, this->_resulotion);
  ledcAttachPin(ENA, 0);
#endif  	
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=ENA;
   _in3=IN3;
   _in4=IN4;
   _enB=ENB;
   _debug = debug;   
   if( IN3 && IN4  && ENB)
   _dual = true;     
 
}


// -- constructor 2 for dual motor - ESP32
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1, int IN2, int ENA, int CHA, int IN3, int IN4, int ENB, int CHB)
{

#if defined(ARDUINO_ARCH_ESP32)		
  ledcSetup(CHA, this->_frequency, this->_resulotion);
  ledcAttachPin(ENA, CHA);
  
  ledcSetup(CHB, this->_frequency, this->_resulotion);
  ledcAttachPin(ENB, CHB);  
  
  _chA = CHA;  
  _chB = CHB;
#endif  	
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=CHA;
   _in3=IN3;
   _in4=IN4;
   _enB=CHB;
   if( IN3 && IN4  && ENB)
   _dual = true;      
 
}

// -- constructor 2 for dual motor with debug - ESP32
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1, int IN2, int ENA, int CHA, int IN3, int IN4, int ENB, int CHB, boolean debug)
{

	
#if defined(ARDUINO_ARCH_ESP32)		
  ledcSetup(CHA, this->_frequency, this->_resulotion);
  ledcAttachPin(ENA, CHA);
  
  ledcSetup(CHB, this->_frequency, this->_resulotion);
  ledcAttachPin(ENB, CHB);  
  
  _chA = CHA;  
  _chB = CHB;
#endif  	
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=CHA;
   _in3=IN3;
   _in4=IN4;
   _enB=CHB;
   _debug = debug;   
   if( IN3 && IN4  && ENB)
   _dual = true;     
 
}


// -- constructor 4 for quar motor - Arduino
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1, int IN2, int ENA,  int IN3, int IN4, int ENB, int IN5, int IN6, int ENC, int IN7, int IN8, int END)
{
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=ENA;
   _in3=IN3;
   _in4=IN4;
   _enB=ENB;
   
   _in5=IN1;
   _in6=IN2;
   _enC=ENC;
   _in7=IN3;
   _in8=IN4;
   _enD=END;
   
   if(IN3 && IN4  && ENB && IN5&& IN6&& ENC&& IN7&& IN8&& END)
   //_dual = true;
   _quar = true;
}

// -- constructor 4 for quar motor with debug - Arduino
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1, int IN2, int ENA, int IN3, int IN4, int ENB, int IN5, int IN6, int ENC, int IN7, int IN8, int END, boolean debug)
{
#if defined(ARDUINO_ARCH_ESP32)		
  ledcSetup(0, this->_frequency, this->_resulotion);
  ledcAttachPin(ENA, 0);
#endif  	
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=ENA;
   _in3=IN3;
   _in4=IN4;
   _enB=ENB;
   
   _in5=IN5;
   _in6=IN6;
   _enC=ENC;
   _in7=IN7;
   _in8=IN8;
   _enD=END;
   
   _debug = debug;
   
   if(IN3 && IN4  && ENB && IN5&& IN6&& ENC&& IN7&& IN8&& END)
   //_dual = true;
   _quar = true;
}

//********************************************************************************************************************
//********************************************************************************************************************
// -- constructor 4 for QUAR motor - ESP32****************************************************************************
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1, int IN2, int ENA, int CHA, int IN3, int IN4, int ENB, int CHB, int IN5, int IN6, int ENC, int CHC, int IN7, int IN8, int END, int CHD)
{
#if defined(ARDUINO_ARCH_ESP32)		
  ledcSetup(CHA, this->_frequency, this->_resulotion);
  ledcAttachPin(ENA, CHA);
  
  ledcSetup(CHB, this->_frequency, this->_resulotion);
  ledcAttachPin(ENB, CHB);  
  
  ledcSetup(CHC, this->_frequency, this->_resulotion);
  ledcAttachPin(ENC, CHC);
  
  ledcSetup(CHD, this->_frequency, this->_resulotion);
  ledcAttachPin(END, CHD);  
  
  _chA = CHA;  
  _chB = CHB;
  _chC = CHC;  
  _chD = CHD;
#endif  	
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=CHA;
   
   _in3=IN3;
   _in4=IN4;
   _enB=CHB;
   
   _in5=IN5;
   _in6=IN6;
   _enC=CHC;
   
   _in7=IN7;
   _in8=IN8;
   _enD=CHD;
   
   if(IN3 && IN4  && ENB && IN5&& IN6&& ENC&& IN7&& IN8&& END)
   //_dual = true;      
   _quar = true;
}//*******************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
 
// -- constructor 4 for quar motor with debug - ESP32
Robojax_L298N_DC_motor::Robojax_L298N_DC_motor(int IN1, int IN2, int ENA, int CHA, int IN3, int IN4, int ENB, int CHB, int IN5, int IN6, int ENC, int CHC, int IN7, int IN8, int END, int CHD, boolean debug)
{
#if defined(ARDUINO_ARCH_ESP32)
  ledcSetup(CHA, this->_frequency, this->_resulotion);
  ledcAttachPin(ENA, CHA);
  ledcSetup(CHB, this->_frequency, this->_resulotion);
  ledcAttachPin(ENB, CHB);  
  ledcSetup(CHC, this->_frequency, this->_resulotion);
  ledcAttachPin(ENC, CHC);
  ledcSetup(CHD, this->_frequency, this->_resulotion);
  ledcAttachPin(END, CHD);  
  
  _chA = CHA;  
  _chB = CHB;
  _chC = CHC;  
  _chD = CHD;
#endif  	
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=CHA;
   
   _in3=IN3;
   _in4=IN4;
   _enB=CHB;
   
   _in5=IN5;
   _in6=IN6;
   _enC=CHC;
   
   _in7=IN7;
   _in8=IN8;
   _enD=CHD;
   _debug = debug;
   if(IN3 && IN4  && ENB && IN5&& IN6&& ENC&& IN7&& IN8&& END)
   //_dual = true;      
   _quar = true;
}

void Robojax_L298N_DC_motor::begin()
{
#if defined(ARDUINO_ARCH_ESP32)	
	pinMode(this->_in1, OUTPUT);
	pinMode(this->_in2, OUTPUT);

	if(this->_debug){
		Serial.println("Robojax.com L298N Motor Library");				
	}
   if(this->_quar){
      pinMode(this->_in3, OUTPUT);
		pinMode(this->_in4, OUTPUT);
      pinMode(this->_in5, OUTPUT);
		pinMode(this->_in6, OUTPUT);
      pinMode(this->_in7, OUTPUT);
		pinMode(this->_in8, OUTPUT);
      if(this->_debug){
			Serial.println("Quar Motor Demo");
		}
   } else if(this->_dual){
		pinMode(this->_in3, OUTPUT);
		pinMode(this->_in4, OUTPUT);
      if(this->_debug){
			Serial.println("Dual Motor Demo");
		}
   } else {
		if(this->_debug){
			Serial.println("Single Motor Demo");
		}
	}
   
#else
	pinMode(this->_in1, OUTPUT);
	pinMode(this->_in2, OUTPUT);
	pinMode(this->_enA, OUTPUT);	
	if(this->_debug){
		Serial.println("Robojax.com L298N Motor Library");				
	}
  
   if(this->_quar){
      pinMode(this->_in3, OUTPUT);
		pinMode(this->_in4, OUTPUT);
      pinMode(this->_enB, OUTPUT);
      pinMode(this->_in5, OUTPUT);
		pinMode(this->_in6, OUTPUT);
      pinMode(this->_enC, OUTPUT);
      pinMode(this->_in7, OUTPUT);
		pinMode(this->_in8, OUTPUT);
      pinMode(this->_enD, OUTPUT);
      if(this->_debug){
			Serial.println("Quar Motor Demo");
		}
   } else if(this->_dual){
		pinMode(this->_in3, OUTPUT);
		pinMode(this->_in4, OUTPUT);
		pinMode(this->_enB, OUTPUT);
		if(this->_debug){			
			Serial.println("Dual Motor Demo");
		}
	}else{
		if(this->_debug){
			Serial.println("Single Motor Demo");
		}
	}
#endif
}

/************************************************
************the rotate function******************
*************************************************
*************************************************/ //NOTE PRINTDEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void Robojax_L298N_DC_motor::rotate(int motor, int value, int dir) {

#if defined(ARDUINO_ARCH_ESP32)	
  uint32_t duty = (this->_bits / 255) * min(toPWM(value), 255);

/* 
   Serial.print("value:");
   Serial.print (value);  
   Serial.print(" duty:");
   Serial.print (duty); 
   Serial.print(" toPWM(value)");
   Serial.println (toPWM(value));    
*/ 
   
	if(dir ==1){
		if(motor ==1){
			digitalWrite(this->_enA, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN			
			digitalWrite(this->_in1, LOW);
			digitalWrite(this->_in2, HIGH);
			this->printDebug3(motor, this->_in1,LOW,this->_in2, HIGH, dir, value , duty);					
		}else if(motor == 2){
			digitalWrite(this->_enB, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in3, LOW);
			digitalWrite(this->_in4, HIGH);	
			this->printDebug3(motor, this->_in3,LOW,this->_in4, HIGH, dir, value , duty);					
		}else if(motor == 3){
			digitalWrite(this->_enC, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in5, LOW);
			digitalWrite(this->_in6, HIGH);	
			this->printDebug3(motor, this->_in5,LOW,this->_in6, HIGH, dir, value , duty);					
		}else{
			digitalWrite(this->_enD, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in7, LOW);
			digitalWrite(this->_in8, HIGH);	
			this->printDebug3(motor, this->_in7,LOW,this->_in8, HIGH, dir, value , duty);					
		}
	}else{
		if(motor ==1){
			digitalWrite(this->_enA, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in1, HIGH);
			digitalWrite(this->_in2, LOW);
			this->printDebug3(motor, this->_in1,HIGH,this->_in2, LOW, dir, value, duty );					
		}else if(motor ==2){
			digitalWrite(this->_enB, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in3, HIGH);
			digitalWrite(this->_in4, LOW);	
			this->printDebug3(motor, this->_in3,HIGH,this->_in4, LOW, dir, value , duty);					
		}else if(motor ==3){
			digitalWrite(this->_enC, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in5, HIGH);
			digitalWrite(this->_in6, LOW);	
			this->printDebug3(motor, this->_in5,HIGH,this->_in6, LOW, dir, value , duty);					
		}else{
			digitalWrite(this->_enD, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in7, HIGH);
			digitalWrite(this->_in8, LOW);	
			this->printDebug3(motor, this->_in7,HIGH,this->_in8, LOW, dir, value , duty);					
		}
	}

   int enPin;
	if(motor ==1){
		enPin= this->_enA;
	}else if(motor ==2){
		enPin= this->_enB;
	}else if(motor ==3){
		enPin= this->_enC;
	}else{
		enPin= this->_enD;
	}

#else
	if(dir ==1){
		if(motor ==1){
			digitalWrite(this->_enA, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN			
			digitalWrite(this->_in1, LOW);
			digitalWrite(this->_in2, HIGH);
			this->printDebug1(motor, this->_in1, LOW, this->_in2, HIGH, dir, value );					
		}else if(motor ==2){
			digitalWrite(this->_enB, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in3, LOW);
			digitalWrite(this->_in4, HIGH);	
			this->printDebug1(motor, this->_in3, LOW, this->_in4, HIGH, dir, value );					
		}else if(motor ==3){
			digitalWrite(this->_enC, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in5, LOW);
			digitalWrite(this->_in6, HIGH);	
			this->printDebug1(motor, this->_in5, LOW, this->_in6, HIGH, dir, value );					
		}else{
			digitalWrite(this->_enD, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in7, LOW);
			digitalWrite(this->_in8, HIGH);	
			this->printDebug1(motor, this->_in7, LOW, this->_in8, HIGH, dir, value );					
		}
	}else{
		if(motor ==1){
			digitalWrite(this->_enA, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in1, HIGH);
			digitalWrite(this->_in2, LOW);
			this->printDebug1(motor, this->_in1, HIGH, this->_in2, LOW, dir, value );					
		}else if(motor == 2){
			digitalWrite(this->_enB, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in3, HIGH);
			digitalWrite(this->_in4, LOW);	
			this->printDebug1(motor, this->_in3, HIGH, this->_in4, LOW, dir, value );					
		}else if(motor == 3){
			digitalWrite(this->_enC, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in5, HIGH);
			digitalWrite(this->_in6, LOW);	
			this->printDebug1(motor, this->_in5, HIGH, this->_in6, LOW, dir, value );					
		}else{
			digitalWrite(this->_enD, LOW);
         // see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
			digitalWrite(this->_in7, HIGH);
			digitalWrite(this->_in8, LOW);	
			this->printDebug1(motor, this->_in7, HIGH, this->_in8, LOW, dir, value );					
		}
	}

   int enPin;
	if(motor ==1){
		enPin= this->_enA;
	}else if(motor ==2){
		enPin= this->_enB;
	}else if(motor ==3){
		enPin= this->_enC;
	}else{
		enPin= this->_enD;
	}	
#endif	

   if(value >=0 && value <=100 ){
   #if defined(ARDUINO_ARCH_ESP32)	
     // write duty to LEDC
      ledcWrite(enPin, duty);
   #else
      analogWrite(enPin, toPWM(value));
   #endif
	}else{
		if(this->_debug){
			Serial.print("***** Speed Value must be between 0 and 100");
		}
	}
}//rotate


/*********************************************
**********************************************
**Runs series of motor control demonstration**
**********************************************
**********************************************/
void Robojax_L298N_DC_motor::demo(int motor){
  //slowly speed up the motor to 100% in CCW
  	if(this->_debug){
		Serial.print("**** Demo: Speeding Motor ");
		Serial.print(motor);
		Serial.println(" from 0% to 100%");				
	}
   
   for(int i=0; i <= 100; i++){
      this->rotate(motor, i, 1);//CW direction
      delay(100);    
   }
   delay(2000);
   
   if(this->_debug){
      Serial.print("**** Demo: Slowing Motor ");
      Serial.print(motor);
      Serial.println(" from 100% to 0%");				
   }
   //slowly speed up the motor to 100% in CW
   for(int i=100; i >=0; i--){
      this->rotate(motor, i, 2);//CCW direction
      delay(100);
   }	
   
   delay(2000);
   this->brake(motor);
   if(this->_debug){
      Serial.print("**** Demo: Brake applied to Motor ");
      Serial.println(motor);
   }
   delay(2000);
   
   this->rotate(motor, 50, 2);
   if(this->_debug){
      Serial.print("**** Demo: Motor ");
      Serial.print(motor);
      Serial.print(" runs  at 50% in CW");
   }    
   delay(3000);
   this->brake(motor);
   delay(2000);
   
   this->rotate(motor, 80, 1);
   if(this->_debug){
      Serial.print("**** Demo: Motor ");
      Serial.print(motor);
      Serial.print(" runs  at 80% in CCW");
   }   
   delay(3000); 
   this->brake(motor);
   if(this->_debug){
      Serial.print("**** Demo: Brake applied to Motor ");
      Serial.println(motor);
   }     
   delay(2000);  
  
   this->rotate(motor, 20, 2);
  	if(this->_debug){
		Serial.print("**** Demo: Motor ");
		Serial.print(motor);
		Serial.print(" runs  at 20% in CW");				
	}
   delay(3000); 
   this->brake(motor);
  	if(this->_debug){
		Serial.print("**** Demo: Brake applied to Motor ");
		Serial.println(motor);
	}
   delay(2000);
} //DEMO



/************************************************************
**********To stop motor quickly with L298N ******************
**********if IN1 =IN2 motor 1 will brake   ******************
**********if IN3 = IN4 motor 2 will brake  ******************
*************************************************************/
void Robojax_L298N_DC_motor::brake(int motor){
	if(motor ==5){
      digitalWrite(this->_in7, LOW);
		digitalWrite(this->_in8, LOW);		
		digitalWrite(this->_in5, LOW);
		digitalWrite(this->_in6, LOW);
		digitalWrite(this->_enC, LOW);	
		digitalWrite(this->_enD, LOW);
		digitalWrite(this->_in3, LOW);
		digitalWrite(this->_in4, LOW);		
		digitalWrite(this->_in1, LOW);
		digitalWrite(this->_in2, LOW);
		digitalWrite(this->_enA, LOW);	
		digitalWrite(this->_enB, LOW);			
		
		if(this->_debug){
			Serial.println("**** ALL 4 Motors Braked");
		}				
	}else if(motor ==4){
		digitalWrite(this->_in7, LOW);
		digitalWrite(this->_in8, LOW);	
		digitalWrite(this->_enD, LOW);			
		if(this->_debug){
			Serial.println("Motor 4 Braked");
		}			
	}else if(motor ==3){
		digitalWrite(this->_in5, LOW);
		digitalWrite(this->_in6, LOW);	
		digitalWrite(this->_enC, LOW);			
		if(this->_debug){
			Serial.println("Motor 3 Braked");
		}			
	}else if(motor ==2){
		digitalWrite(this->_in3, LOW);
		digitalWrite(this->_in4, LOW);	
		digitalWrite(this->_enB, LOW);			
		if(this->_debug){
			Serial.println("Motor 2 Braked");
		}			
	}else{
		digitalWrite(this->_in1, LOW);
		digitalWrite(this->_in2, LOW);	
		digitalWrite(this->_enA, LOW);		
		if(this->_debug){
			Serial.println("Motor 1 Braked");
		}				
	}

}//stop()


/*
 * @brief converts % value from 0 to 100% to 0-255
 * @param v is integer value representing % from 0-100
 * @return will return value from 0 to 255
 * Written by Ahmad Shamshiri @ robojax.com 
 */
int Robojax_L298N_DC_motor::toPWM(int v){
#if defined(ARDUINO_ARCH_ESP32)   
		return map(v, 0,100,0,255);
#else 
		return map(v, 0,100,0,255);
#endif		
   
}//



void Robojax_L298N_DC_motor::printDebug1(int motor, int p1, int v1, 
                                                    int p2, int v2, 
                                                    int dir, int speed)
{
	if(this->_debug){
		if(dir ==1){
			Serial.print("Motor ");
			Serial.print(motor);	
			Serial.print(" CW ");						
		}else{
			Serial.print("Motor ");
			Serial.print(motor);	
			Serial.print(" CCW ");						
		}
		Serial.print("at ");
		Serial.print(speed);				
		Serial.print("%");	
		
		Serial.print(" pin ");					
          Serial.print(p1);
		if(v1 ==1){
			Serial.print(" HIGH ");					
		}else{
			Serial.print(" LOW ");						
		}

		Serial.print(" pin ");					
          Serial.print(p2);
		if(v2 ==1){
			Serial.println(" HIGH");					
		}else{
			Serial.println(" LOW");						
		}
	}
}//debug1

void Robojax_L298N_DC_motor::printDebug2(int motor1, int p1  , int v1, 
                                                     int p2  , int v2,
                                                     int dir1, int speed1,
                                         int motor2, int p3  , int v3, 
                                                     int p4  , int v4, 
                                                     int dir2, int speed2)
{

	if(this->_debug){
		if(dir1 ==1){
			Serial.print("Motor ");
			Serial.print(motor1);	
			Serial.print(" CW ");					
		}else{
			Serial.print("Motor ");
			Serial.print(motor1);	
			Serial.print(" CCW ");						
		}
		Serial.print("at ");
		Serial.print(speed1);				
		Serial.print("%");	
		
		Serial.print(" pin ");					
      Serial.print(p1);
		if(v1 ==1){
			Serial.print("HIGH");					
		}else{
			Serial.print("LOW");						
		}

		Serial.print(" pin ");					
      Serial.print(p2);
		if(v2 ==1){
			Serial.print("HIGH");
		}else{
			Serial.println("LOW");
		}
		
      
		if(dir2 ==1){
			Serial.print("Motor ");
			Serial.print(motor2);	
			Serial.print(" CW ");					
		}else{
			Serial.print("Motor ");
			Serial.print(motor2);	
			Serial.print(" CCW ");						
		}
		Serial.print("at ");
		Serial.print(speed2);				
		Serial.print("%");	
		
		Serial.print(" pin ");					
      Serial.print(p3);
		if(v3 ==1){
			Serial.print("HIGH");					
		}else{
			Serial.print("LOW");						
		}

		Serial.print(" pin ");					
      Serial.print(p4);
		if(v4 ==1){
			Serial.print("HIGH");					
		}else{
			Serial.println("LOW");						
		}
	}
}//debug2


void Robojax_L298N_DC_motor::printDebug3(int motor, int p1, int v1, 
                                                    int p2, int v2, 
                                                    int dir, int speed, int duty)
{
	if(this->_debug){
		if(dir ==1){
			Serial.print("Motor ");
			Serial.print(motor);	
			Serial.print(" CW ");						
		}else{
			Serial.print("Motor ");
			Serial.print(motor);	
			Serial.print(" CCW ");						
		}
		Serial.print("at ");
		Serial.print(speed);				
		Serial.print("%");	
		
		Serial.print(" duty ");
		Serial.print(duty);				
	
		
		Serial.print(" pin ");					
      Serial.print(p1);
		if(v1 ==1){
			Serial.print(" HIGH ");					
		}else{
			Serial.print(" LOW ");						
		}			

		Serial.print(" pin ");					
      Serial.print(p2);
		if(v2 ==1){
			Serial.println(" HIGH");					
		}else{
			Serial.println(" LOW");						
		}	
	}
}//debug3

void Robojax_L298N_DC_motor::printDebug4(int motor1, int p1, int v1, 
                                                     int p2, int v2, 
                                                     int dir1, int speed1, int duty1, 
                                         int motor2, int p3, int v3, 
                                                     int p4, int v4, 
                                                     int dir2, int speed2, int duty2)
{
	if(this->_debug){
		if(dir1 ==1){
			Serial.print("Motor ");
			Serial.print(motor1);	
			Serial.print(" CW ");					
		}else{
			Serial.print("Motor ");
			Serial.print(motor1);	
			Serial.print(" CCW ");						
		}
		Serial.print("at ");
		Serial.print(speed1);				
		Serial.print("%");	
		
		Serial.print(" duty ");
		Serial.print(duty1);				
	
		
		Serial.print(" pin ");					
      Serial.print(p1);
		if(v1 ==1){
			Serial.print("HIGH");					
		}else{
			Serial.print("LOW");						
		}			

		Serial.print(" pin ");					
      Serial.print(p2);
		if(v2 ==1){
			Serial.print("HIGH");					
		}else{
			Serial.println("LOW");						
		}	
		
     
		if(dir2 ==1){
			Serial.print("Motor ");
			Serial.print(motor2);	
			Serial.print(" CW ");					
		}else{
			Serial.print("Motor ");
			Serial.print(motor2);	
			Serial.print(" CCW ");						
		}
		Serial.print("at ");
		Serial.print(speed2);				
		Serial.print("%");	
		
		Serial.print(" duty ");
		Serial.print(duty1);				
		
		
		Serial.print(" pin ");					
      Serial.print(p3);
		if(v3 ==1){
			Serial.print("HIGH");					
		}else{
			Serial.print("LOW");						
		}			

		Serial.print(" pin ");					
      Serial.print(p4);
		if(v4 ==1){
			Serial.print("HIGH");					
		}else{
			Serial.println("LOW");						
		}	
	}
}//debug4
