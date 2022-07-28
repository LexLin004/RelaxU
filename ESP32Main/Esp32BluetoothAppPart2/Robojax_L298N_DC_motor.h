#ifndef Robojax_L298N_DC_motor_H
#define Robojax_L298N_DC_motor_H

#include "Arduino.h"


class Robojax_L298N_DC_motor
{
public:

    //Arduino board single motor
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA);
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, boolean debug);	
	
	//ESP32 single motor
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int CHA);
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int CHA, boolean debug);		
	
	//Arduino dual motor- ESP
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA,int IN3,int IN4,int ENB);	
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA,int IN3,int IN4,int ENB, boolean debug);	
	
	//ESP32 dual motor
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int CHA, int IN3, int IN4,int ENB, int CHB);	
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int CHA, int IN3, int IN4,int ENB, int CHB, boolean debug);		
	
    Robojax_L298N_DC_motor(int IN1, int IN2, int ENA, int IN3, int IN4, int ENB, int IN5, int IN6, int ENC, int IN7, int IN8, int END);
    Robojax_L298N_DC_motor(int IN1, int IN2, int ENA, int IN3, int IN4, int ENB, int IN5, int IN6, int ENC, int IN7, int IN8, int END, boolean debug);

    Robojax_L298N_DC_motor(int IN1, int IN2, int ENA, int CHA, int IN3, int IN4, int ENB, int CHB, 
                           int IN5, int IN6, int ENC, int CHC, int IN7, int IN8, int END, int CHD);
    Robojax_L298N_DC_motor(int IN1, int IN2, int ENA, int CHA, int IN3, int IN4, int ENB, int CHB, 
                           int IN5, int IN6, int ENC, int CHC, int IN7, int IN8, int END, int CHD, boolean debug);
    
    /**
     * control motor
     */
    void rotate(int motor, int value, int dir);
   /**
    * Initializes the L298D motor driver
    */
   void begin();
   

   /*
   * brake the motor
   
   */
   void brake(int motor);
  
   /*
   * single motor demo
   
   */
   void demo(int motor);
	
private:

   /*
   * debug print
   */
   void printDebug1(int motor, int p1, int v1, int p2, int v2, int dir, int speed);
   void printDebug2(int motor1, int p1, int v1, int p2, int v2, int dir1, int speed1, int motor2, int p3, int v3, int p4, int v4, int dir2, int speed2) ;

   void printDebug3(int motor, int p1, int v1, int p2, int v2, int dir, int speed, int duty);
   void printDebug4(int motor1, int p1, int v1, int p2, int v2, int dir1, int speed1, int duty1, int motor2, int p3, int v3, int p4, int v4, int dir2, int speed2, int duty2) ;
  
   int _in1, _in2, _enA, _in3, _in4,  _enB, _pwmBit, _chA, _chB;
   int _in5, _in6, _enC, _in7, _in8,  _enD, _chC, _chD;
   boolean _debug = false;
   boolean _dual;
   boolean _quar;
   int _resulotion =12;
   int _frequency = 5000;
   int _bits = pow(2,_resulotion);
   
 
   int toPWM(int v);   
};

#endif
