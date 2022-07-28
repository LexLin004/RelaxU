// this header is needed for Bluetooth Serial -> works ONLY on ESP32
#include "BluetoothSerial.h" 
// this header is needed for motor driver
#include "Robojax_L298N_DC_motor.h"
 
// definition of the delaytime between button on and button off
#define DELAY 1000  // delay is in milliseconds, so 1000ms corresponds to 1s

// init Class:
BluetoothSerial ESP_BT; 
//s
#define motor1 1 // do not change
#define motor2 2 // do not change
#define motor3 3 // do not change
#define motor4 4 // do not change
// motor 1 settings
#define CHA 0
#define ENA 13 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 12
#define IN2 14
// motor 2 settings
#define IN3 27
#define IN4 26
#define ENB 25
#define CHB 1
// motor 3 settings
#define CHC 2
#define ENC 19
#define IN5 18
#define IN6 5
// motor 4 settings
#define IN7 17
#define IN8 16
#define END 4
#define CHD 3
// for 4 motors
Robojax_L298N_DC_motor motor(IN1, IN2, ENA, CHA, IN3, IN4, ENB, CHB, IN5, IN6, ENC, CHC, IN7, IN8, END, CHD);
void motorStatusPlus(int motor1Speed, int motor2Speed, int motor3Speed, int motor4Speed);
void motorStatusMinus(int motor1Speed, int motor2Speed, int motor3Speed, int motor4Speed);
void motorStatusChange(int motor1StopState,int motor2StopState,int motor3StopState,int motor4StopState,
                       int motor1Speed, int motor1Direction,int motor2Speed, int motor2Direction,
                       int motor3Speed, int motor3Direction,int motor4Speed, int motor4Direction);
// Parameters for Bluetooth interface and timing
int incoming;                           // variable to store byte received from phone 
unsigned long now;                      // variable to store current "time" using millis() function

//general setting
const int CCW = 2;  // do not change
const int CW  = 1;  // do not change

// motor 1 settings
int       motor1Direction = CW;//default direction of rotation
const int motor1changeStep = 5;// 10 is 10% every time button is pushed
int       motor1Speed = 40;// variable holding the light output vlaue (initial value) 40 means 40%
const int motor1MinimumSpeed=40;
const int motor1MaximumSpeed=100;
int       motor1StopState=HIGH;//Stope state of motor (HIGH means STOP) and LOW means Start
// motor 2 settings
int       motor2Direction = CW;//default direction of rotation
const int motor2changeStep = 5;// 10 is 10% every time button is pushed
int       motor2Speed = 40;// variable holding the light output vlaue (initial value) 40 means 40%
const int motor2MinimumSpeed=40;
const int motor2MaximumSpeed=100;
int       motor2StopState=HIGH;//Stope state of motor (HIGH means STOP) and LOW means Start
// motor 3 settings
int       motor3Direction = CW;//default direction of rotation
const int motor3changeStep = 5;// 10 is 10% every time button is pushed
int       motor3Speed = 40;// variable holding the light output vlaue (initial value) 40 means 40%
const int motor3MinimumSpeed=40;
const int motor3MaximumSpeed=100;
int       motor3StopState=HIGH;//Stope state of motor (HIGH means STOP) and LOW means Start
// motor 4 settings
int       motor4Direction = CW;//default direction of rotation
const int motor4changeStep = 5;// 10 is 10% every time button is pushed
int       motor4Speed = 40;// variable holding the light output vlaue (initial value) 40 means 40%
const int motor4MinimumSpeed=40;
const int motor4MaximumSpeed=100;
int       motor4StopState=HIGH;//Stope state of motor (HIGH means STOP) and LOW means Start


int positionAndModeReg;
int time_arm_mode1_20s;
int time_arm_mode1_22s;
int time_arm_mode1_1200s;
int arm_mode_all_strength_plus;
int arm_mode_all_strength_minus;
int leg_mode_all_strength_plus;
int leg_mode_all_strength_minus;
int waist_mode_all_strength_plus;
int waist_mode_all_strength_minus;
int time_arm_mode2_300s;
int time_arm_mode2_1200s;
int time_arm_mode3_1200s;
int time_leg_mode1_20s;
int time_leg_mode1_22s;
int time_leg_mode1_1200s;
int time_leg_mode2_300s;
int time_leg_mode2_1200s;
int time_leg_mode3_1200s;
int time_waist_mode1_20s;
int time_waist_mode1_22s;
int time_waist_mode1_1200s;
int time_waist_mode2_300s;
int time_waist_mode2_1200s;
int modeAndBottom;

void setup() {
  Serial.begin(19200);
  ESP_BT.begin("MassagerRelaxU");        // Name of your Bluetooth interface -> will show up on your phone
  motor.begin();
}
//状态调整模块
void motorStatusChange(int motor1StopState,int motor2StopState,int motor3StopState,int motor4StopState,
                       int motor1Speed, int motor1Direction, int motor2Speed, int motor2Direction,
                       int motor3Speed, int motor3Direction, int motor4Speed, int motor4Direction)
{
  if(motor1StopState ==HIGH){
    motor.brake(motor1);  
  }else{
     motor.rotate(motor1, motor1Speed, motor1Direction);//run motor1 at motor1Speed% speed in motor1Direction 
  }
  
  if(motor2StopState ==HIGH){
    motor.brake(motor2);   
  }else{
     motor.rotate(motor2, motor2Speed, motor2Direction);//run motor2 at motor2Speed% speed in motor2Direction 
  }
  
  if(motor3StopState ==HIGH){
    motor.brake(motor3);  
  }else{
    motor.rotate(motor3, motor3Speed, motor3Direction);//run motor2 at motor2Speed% speed in motor2Direction 
  }

  if(motor4StopState ==HIGH){
    motor.brake(motor4);  
  }else{
    motor.rotate(motor4, motor4Speed, motor4Direction);//run motor2 at motor2Speed% speed in motor2Direction 
  }
}
//整体加速
void motorStatusPlus(){
  if(motor1Speed<=100){
    motor1Speed = motor1Speed+5;
  }
  if(motor2Speed<=100){
    motor2Speed = motor2Speed+5;
  }      
  if(motor3Speed<=100){
    motor3Speed = motor3Speed+5;
  }
  if(motor4Speed<=100){
    motor4Speed = motor4Speed+5;
  }
}
//整体减速
void motorStatusMinus(){
  if(motor1Speed>=0){
    motor1Speed = motor1Speed-5;
  }
  if(motor2Speed>=0){
    motor2Speed = motor2Speed-5;
  }      
  if(motor3Speed>=0){
    motor3Speed = motor3Speed-5;
  }
  if(motor4Speed>=0){
    motor4Speed = motor4Speed-5;
  }
}
//主模块
void loop() {
  //Serial.print("positionAndModeReg is ");
  //Serial.println(positionAndModeReg);
  now = millis();                       // Store current time
  
  // ARM MODE1 *************************************************************************************
  if ((positionAndModeReg==110) and now > time_arm_mode1_1200s + 600000){ 
    //Serial.println("enter ARM MODE1 if 1");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    time_arm_mode1_20s   = 0;
    time_arm_mode1_22s   = 0;
    time_arm_mode1_1200s = 0;
    ESP_BT.write(110); //app接收到110之后，将arm mode1按钮显示灰色(按摩10min)
    positionAndModeReg = 0;
    //Serial.print("arm MODE1 timeout - value: 0");
  } else if((positionAndModeReg==110) and now > time_arm_mode1_20s + 20000) {//20s停止
    //Serial.println("enter ARM MODE1 if 2");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    if(arm_mode_all_strength_plus){
      motorStatusPlus();
      arm_mode_all_strength_plus=0;
      //Serial.println("ready to return 111 for changing arm mode1 + to gray");
      ESP_BT.write(111); //app接收到111之后，将arm mode1 + 按钮显示灰色
    }
    if(arm_mode_all_strength_minus){
      motorStatusMinus();
      arm_mode_all_strength_minus = 0;
      //Serial.println("ready to return 112 for changing arm mode1 - to gray");
      ESP_BT.write(112); //app接收到112之后，将arm mode1 - 按钮显示灰色
    }
    if ((positionAndModeReg==110) and now > time_arm_mode1_22s + 22000){
      time_arm_mode1_20s = now;
      time_arm_mode1_22s  = now;
      motor1StopState = 0;
      motor2StopState = 0;
      motor3StopState = 0;
      motor4StopState = 1;
      if(motor1Direction == CW){
        motor1Direction = CCW;
        motor2Direction = CCW;
        motor3Direction = CCW;
      } else {
        motor1Direction = CW;
        motor2Direction = CW;
        motor3Direction = CW;
      }
    }
  } else if (positionAndModeReg==110){
    //Serial.println("enter ARM MODE1 if 3");
    if(arm_mode_all_strength_plus){
      motorStatusPlus();
      arm_mode_all_strength_plus=0;
      //Serial.println("ready to return 111 for changing arm mode1 + to gray");
      ESP_BT.write(111); //app接收到111之后，将arm mode1 + 按钮显示灰色
    }
    if(arm_mode_all_strength_minus){
      motorStatusMinus();
      arm_mode_all_strength_minus = 0;
      //Serial.println("ready to return 112 for changing arm mode1 - to gray");
      ESP_BT.write(112); //app接收到112之后，将arm mode1 - 按钮显示灰色
    }
  } // *************************************************************************************

  // ARM MODE2 *************************************************************************************
  if ((positionAndModeReg==120) and now > time_arm_mode2_1200s + 600000){
    //Serial.println("enter ARM MODE2 if 1");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    time_arm_mode2_300s  = 0;
    time_arm_mode2_1200s = 0;
    ESP_BT.write(120); //app接收到120之后，将arm mode2按钮显示灰色
    positionAndModeReg = 0;
    //Serial.print("arm MODE2 timeout - value: 0");
  } else if((positionAndModeReg==120) and now > time_arm_mode2_300s + 120000) {
    //Serial.println("enter ARM MODE2 if 2");
    if(motor1Speed < 100){
      motor1Speed = motor1Speed+5;
      motor3Speed = motor3Speed+5;
    } else {
      motor1Speed = motor1Speed;
      motor3Speed = motor3Speed;
    }
    if(motor2Speed < 100){
      motor2Speed = motor2Speed+5;
    } else {
      motor2Speed = motor2Speed;
    }
    if(arm_mode_all_strength_plus){
      motorStatusPlus();
      arm_mode_all_strength_plus=0;
      //Serial.println("ready to return 111 for changing arm mode2 + to gray");
      ESP_BT.write(111); //app接收到121之后，将arm mode2 + 按钮显示灰色
    }
    if(arm_mode_all_strength_minus){
      motorStatusMinus();
      arm_mode_all_strength_minus = 0;
      //Serial.println("ready to return 112 for changing arm mode2 - to gray");
      ESP_BT.write(112); //app接收到122之后，将arm mode2 - 按钮显示灰色
    }
    time_arm_mode2_300s = now;
  } else if (positionAndModeReg==120){
    //Serial.println("enter ARM MODE2 if 3");
    if(arm_mode_all_strength_plus){
      motorStatusPlus();
      arm_mode_all_strength_plus=0;
      //Serial.println("ready to return 111 for changing arm mode2 + to gray");
      ESP_BT.write(111); //app接收到121之后，将arm mode2 + 按钮显示灰色
    }
    if(arm_mode_all_strength_minus){
      motorStatusMinus();
      arm_mode_all_strength_minus = 0;
      //Serial.println("ready to return 112 for changing arm mode2 - to gray");
      ESP_BT.write(112); //app接收到122之后，将arm mode2 - 按钮显示灰色
    }
  } // *************************************************************************************

  // ARM MODE3
  if ((positionAndModeReg==130) and now > time_arm_mode3_1200s + 600000){
    //Serial.println("enter ARM MODE3 if 1");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    time_arm_mode3_1200s = 0;
    ESP_BT.write(130); //app接收到130之后，将arm mode3按钮显示灰色
    positionAndModeReg = 0;
    //Serial.print("arm MODE3 timeout - value: 0");
  } else if (positionAndModeReg==130){
    //Serial.println("enter ARM MODE3 if 2");
    if(arm_mode_all_strength_plus){
      motorStatusPlus();
      arm_mode_all_strength_plus=0;
      //Serial.println("ready to return 111 for changing arm mode3 + to gray");
      ESP_BT.write(111); //app接收到131之后，将arm mode3 + 按钮显示灰色
    }
    if(arm_mode_all_strength_minus){
      motorStatusMinus();
      arm_mode_all_strength_minus = 0;
      //Serial.println("ready to return 112 for changing arm mode3 - to gray");
      ESP_BT.write(112); //app接收到132之后，将arm mode3 - 按钮显示灰色
    }
  } // *************************************************************************************

  // LEG MODE1
  if ((positionAndModeReg==210) and now > time_leg_mode1_1200s + 600000){
    //Serial.println("enter LEG MODE1 if 1");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    time_leg_mode1_20s   = 0;
    time_leg_mode1_22s   = 0;
    time_leg_mode1_1200s = 0;
    ESP_BT.write(210); //app接收到210之后，将 leg mode1按钮显示灰色
    positionAndModeReg = 0;
    //Serial.print("leg MODE1 timeout - value: 0");
  } else if((positionAndModeReg==210) and now > time_leg_mode1_20s + 20000) {
    //Serial.println("enter LEG MODE1 if 2");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    if(leg_mode_all_strength_plus){
      motorStatusPlus();
      leg_mode_all_strength_plus=0;
      //Serial.println("ready to return 211 for changing leg mode1 + to gray");
      ESP_BT.write(211); //app接收到211之后，将 leg mode1 + 按钮显示灰色
    }
    if(leg_mode_all_strength_minus){
      motorStatusMinus();
      leg_mode_all_strength_minus = 0;
      //Serial.println("ready to return 212 for changing leg mode1 - to gray");
      ESP_BT.write(212); //app接收到212之后，将 leg mode1 - 按钮显示灰色
    }
    if ((positionAndModeReg==210) and now > time_leg_mode1_22s + 22000){
      time_leg_mode1_20s = now;
      time_leg_mode1_22s  = now;
      motor1StopState = 0;
      motor2StopState = 0;
      motor3StopState = 0;
      motor4StopState = 0;
      if(motor1Direction == CW){
        motor1Direction = CCW;
        motor2Direction = CCW;
        motor3Direction = CCW;
        motor4Direction = CCW;
      } else {
        motor1Direction = CW;
        motor2Direction = CW;
        motor3Direction = CW;
        motor4Direction = CW;
      }
    }
  } else if (positionAndModeReg==210){
    //Serial.println("enter LEG MODE1 if 3");
    if(leg_mode_all_strength_plus){
      motorStatusPlus();
      leg_mode_all_strength_plus=0;
      //Serial.println("ready to return 211 for changing leg mode1 + to gray");
      ESP_BT.write(211); //app接收到211之后，将 leg mode1 + 按钮显示灰色
    }
    if(leg_mode_all_strength_minus){
      motorStatusMinus();
      leg_mode_all_strength_minus = 0;
      //Serial.println("ready to return 212 for changing leg mode1 - to gray");
      ESP_BT.write(212); //app接收到212之后，将 leg mode1 - 按钮显示灰色
    }
  } // *************************************************************************************

  // LEG MODE2
  if ((positionAndModeReg==220) and now > time_leg_mode2_1200s + 600000){
    //Serial.println("enter LEG MODE2 if 1");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    time_leg_mode2_300s = 0;
    time_leg_mode2_1200s = 0;
    ESP_BT.write(220); //app接收到220之后，将leg mode2按钮显示灰色
    positionAndModeReg = 0;
    //Serial.print("leg MODE2 timeout - value: 0");
  } else if((positionAndModeReg==220) and now > time_leg_mode2_300s + 120000) {
    //Serial.println("enter LEG MODE2 if 2");
    if(motor1Speed < 100){
      motor1Speed = motor1Speed+5;
      motor3Speed = motor3Speed+5;
      motor4Speed = motor4Speed+5;
    } else {
      motor1Speed = motor1Speed;
      motor3Speed = motor3Speed;
      motor4Speed = motor4Speed;
    }
    if(motor2Speed < 100){
      motor2Speed = motor2Speed+5;
    } else {
      motor2Speed = motor2Speed;
    }
    if(leg_mode_all_strength_plus){
      motorStatusPlus();
      leg_mode_all_strength_plus=0;
      //Serial.println("ready to return 211 for changing leg mode2 + to gray");
      ESP_BT.write(211); //app接收到221之后，将 leg mode2 + 按钮显示灰色
    }
    if(leg_mode_all_strength_minus){
      motorStatusMinus();
      leg_mode_all_strength_minus = 0;
      //Serial.println("ready to return 212 for changing leg mode2 - to gray");
      ESP_BT.write(212); //app接收到222之后，将 leg mode2 - 按钮显示灰色
    }
    time_leg_mode2_300s = now;
  } else if (positionAndModeReg==220){
    //Serial.println("enter LEG MODE2 if 3");
    if(leg_mode_all_strength_plus){
      motorStatusPlus();
      leg_mode_all_strength_plus=0;
      //Serial.println("ready to return 211 for changing leg mode2 + to gray");
      ESP_BT.write(211); //app接收到221之后，将 leg mode2 + 按钮显示灰色
    }
    if(leg_mode_all_strength_minus){
      motorStatusMinus();
      leg_mode_all_strength_minus = 0;
      //Serial.println("ready to return 212 for changing leg mode2 - to gray");
      ESP_BT.write(212); //app接收到222之后，将 leg mode2 - 按钮显示灰色
    }
  } // *************************************************************************************

  // LEG MODE3
  if ((positionAndModeReg==230) and now > time_leg_mode3_1200s + 600000){
    //Serial.println("enter LEG MODE3 if 1");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    time_leg_mode3_1200s = 0;
    ESP_BT.write(230); //app接收到230之后，将 leg mode3按钮显示灰色
    positionAndModeReg = 0;
    //Serial.print("leg MODE3 timeout - value: 0");
  } else if (positionAndModeReg==230){
    //Serial.println("enter LEG MODE3 if 2");
    if(leg_mode_all_strength_plus){
      motorStatusPlus();
      leg_mode_all_strength_plus=0;
      //Serial.println("ready to return 211 for changing leg mode3 + to gray");
      ESP_BT.write(211); //app接收到231之后，将 leg mode3 + 按钮显示灰色
    }
    if(leg_mode_all_strength_minus){
      motorStatusMinus();
      leg_mode_all_strength_minus = 0;
      //Serial.println("ready to return 212 for changing leg mode3 - to gray");
      ESP_BT.write(212); //app接收到232之后，将 leg mode3 - 按钮显示灰色
    }
  } // *************************************************************************************

  // WAIST MODE1
  if ((positionAndModeReg==70) and now > time_waist_mode1_1200s + 600000){
    //Serial.println("enter WAIST MODE1 if 1");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    time_waist_mode1_20s   = 0;
    time_waist_mode1_22s   = 0;
    time_waist_mode1_1200s = 0;
    ESP_BT.write(70); //app接收到310之后，将 waist mode1 按钮显示灰色
    positionAndModeReg = 0;
    //Serial.print("waist MODE1 timeout - value: 0");
  } else if((positionAndModeReg==70) and now > time_waist_mode1_20s + 20000) {
    //Serial.println("enter WAIST MODE1 if 2");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    if(waist_mode_all_strength_plus){
      motorStatusPlus();
      waist_mode_all_strength_plus=0;
      ESP_BT.write(71); //app接收到71之后，将 waist mode1 + 按钮显示灰色
      //Serial.println("ready to return 71 for changing waist mode1 + to gray");
    }
    if(waist_mode_all_strength_minus){
      motorStatusMinus();
      waist_mode_all_strength_minus = 0;
      //Serial.println("ready to return 72 for changing waist mode1 - to gray");
      ESP_BT.write(72); //app接收到312之后，将 waist mode1 - 按钮显示灰色
    }
    if ((positionAndModeReg==70) and now > time_waist_mode1_22s + 22000){
      time_waist_mode1_20s = now;
      time_waist_mode1_22s = now;
      motor1StopState = 0;
      motor2StopState = 0;
      motor3StopState = 0;
      motor4StopState = 0;
    }
  } else if (positionAndModeReg==70){
    //Serial.println("enter WAIST MODE1 if 3");
    if(waist_mode_all_strength_plus){
      motorStatusPlus();
      waist_mode_all_strength_plus=0;
      //Serial.println("ready to return 311 for changing waist mode1 + to gray");
      ESP_BT.write(71); //app接收到311之后，将 waist mode1 + 按钮显示灰色
    }
    if(waist_mode_all_strength_minus){
      motorStatusMinus();
      waist_mode_all_strength_minus = 0;
      //Serial.println("ready to return 312 for changing waist mode1 - to gray");
      ESP_BT.write(72); //app接收到312之后，将 waist mode1 - 按钮显示灰色
    }
  } // *************************************************************************************

  // WAIST MODE2
  if ((positionAndModeReg==80) and now > time_waist_mode2_1200s + 600000){
    //Serial.println("enter WAIST MODE2 if 1");
    motor1StopState = 1;
    motor2StopState = 1;
    motor3StopState = 1;
    motor4StopState = 1;
    time_waist_mode2_300s  = 0;
    time_waist_mode2_1200s = 0;
    ESP_BT.write(80); //app接收到320之后，将 waist mode2按钮显示灰色
    positionAndModeReg = 0;
    //Serial.print("waist MODE2 timeout - value: 0");
  } else if ((positionAndModeReg==80) and now > time_waist_mode2_300s + 120000) {
    //Serial.println("enter WAIST MODE2 if 2");
    if(motor1Speed < 100){
      motor1Speed = motor1Speed+5;
      motor2Speed = motor2Speed+5;
      motor3Speed = motor3Speed+5;
      motor4Speed = motor4Speed+5;
    } else {
      motor1Speed = motor1Speed;
      motor2Speed = motor2Speed;
      motor3Speed = motor3Speed;
      motor4Speed = motor4Speed;
    }
    if(waist_mode_all_strength_plus){
      motorStatusPlus();
      waist_mode_all_strength_plus=0;
      //Serial.println("ready to return 311 for changing waist mode2 + to gray");
      ESP_BT.write(71); //app接收到321之后，将 waist mode2 + 按钮显示灰色
    }
    if(waist_mode_all_strength_minus){
      motorStatusMinus();
      waist_mode_all_strength_minus = 0;
      //Serial.println("ready to return 312 for changing waist mode2 - to gray");
      ESP_BT.write(72); //app接收到322之后，将 waist mode2 - 按钮显示灰色
    }
    time_waist_mode2_300s = now;
  } else if (positionAndModeReg==80){
    //Serial.println("enter WAIST MODE2 if 3");
    if(waist_mode_all_strength_plus){
      motorStatusPlus();
      waist_mode_all_strength_plus=0;
      //Serial.println("ready to return 311 for changing waist mode2 + to gray");
      ESP_BT.write(71); //app接收到321之后，将 waist mode2 + 按钮显示灰色
    }
    if(waist_mode_all_strength_minus){
      motorStatusMinus();
      waist_mode_all_strength_minus = 0;
      //Serial.println("ready to return 312 for changing waist mode2 - to gray");
      ESP_BT.write(72); //app接收到322之后，将 waist mode2 - 按钮显示灰色
    }
  } // **********************************************************************************
  motorStatusChange(motor1StopState,motor2StopState,motor3StopState,motor4StopState,
                      motor1Speed, motor1Direction,
                      motor2Speed, motor2Direction,
                      motor3Speed, motor3Direction,
                      motor4Speed, motor4Direction);
  
  // -------------------- Receive Bluetooth signal ----------------------
  if (ESP_BT.available()){
    incoming = ESP_BT.read(); //Read what we receive and store in "incoming"
    //Serial.print(incoming);
    //Serial.println(" from if block");
    modeAndBottom = incoming;

  /*
     Arm   Mode 1 (motor1上臂高处70，motor2 & motor3上臂内外 90, 震动20s停2s并且切换方向，共20分钟)
     Arm   Mode 2 (motor1 & motor3 从70开始，motor2从50开始，每5分钟 整体强度+5，共20分钟)
     Arm   Mode 3 (motor1 & motor2 & motor3 全部40)//这个会不会太低
     
     Leg   Mode 1 (motor1 * motor4 85，motor2 & motor3 100, 震动20s停2s并且切换方向，共20分钟)
     Leg   Mode 2 (motor1 & motor4 & motor3 从70开始，motor2从50开始，每5分钟 整体强度+5，共20分钟)
     Leg   Mode 3 (motor1 & motor2 & motor3 & motor4 全部55)
     
     Waist Mode 1 (motor1 & motor2 & motor3 & motor4 强度60，每20s停2s)
     Waist Mode 2 (motor1 & motor4 相同方向 强度50， motor2 & motor3 相反方向 强度50，每5分钟，整体强度+5，共20分钟)
   */
    
    switch (modeAndBottom) {
      case 0:
        positionAndModeReg = modeAndBottom;
        //Serial.println(incoming);
        motor1StopState = 1;
        motor2StopState = 1;
        motor3StopState = 1;
        motor4StopState = 1;
        //Serial.println("ready to return 0 for changing mode to gray");
        ESP_BT.write(0); //app接收到0之后，将 对应mode 按钮显示灰色
        break;
      case 70:   // waist mode1 default //70
        positionAndModeReg = modeAndBottom;
        //Serial.println(incoming);
        time_waist_mode1_20s   = now;
        time_waist_mode1_22s   = now; // 22s计时工具，为了达成2s休息计时存在
        time_waist_mode1_1200s = now; // 20min
        motor1StopState = 0;
        motor2StopState = 0;
        motor3StopState = 0;
        motor4StopState = 0;
        motor1Speed     = 80;
        motor2Speed     = 80;
        motor3Speed     = 80;
        motor4Speed     = 80;
        motor1Direction = CW;
        motor2Direction = CW;
        motor3Direction = CW;
        motor4Direction = CW;
        break;
      case 80:  // waist mode2 default //80
        positionAndModeReg = modeAndBottom;
        //Serial.println(incoming);
        time_waist_mode2_300s  = now; // 5min
        time_waist_mode2_1200s = now; // 20min
        motor1StopState = 0;
        motor2StopState = 0;
        motor3StopState = 0;
        motor4StopState = 0;
        motor1Speed     = 50;
        motor2Speed     = 50;
        motor3Speed     = 50;
        motor4Speed     = 50;
        motor1Direction = CW;
        motor2Direction = CCW;
        motor3Direction = CCW;
        motor4Direction = CW;
        break;
      case 71://71
      case 81://81
        //Serial.println(incoming);
        waist_mode_all_strength_plus = 1;
        break;
      case 72://72
      case 82: //82
        //Serial.println(incoming);
        waist_mode_all_strength_minus = 1;
        break;
      case 110: //arm mode1 default
        positionAndModeReg = modeAndBottom;
        //Serial.print("positionAndModeReg in case110 is ");
        //Serial.println(positionAndModeReg);
        //Serial.println(incoming);
        time_arm_mode1_20s   = now;
        time_arm_mode1_22s   = now; // 22s计时工具，为了达成2s休息计时存在
        time_arm_mode1_1200s = now; // 20min
        motor1StopState = 0;
        motor2StopState = 0;
        motor3StopState = 0;
        motor4StopState = 1;
        motor1Speed     = 70;
        motor2Speed     = 90;
        motor3Speed     = 90;
        //motor4Speed     =
        motor1Direction = CW;
        motor2Direction = CW;
        motor3Direction = CW;
        //motor4Direction =
        break;
      case 120:  //arm mode2 default
        positionAndModeReg = modeAndBottom;
        //Serial.println(incoming);
        time_arm_mode2_300s   = now;
        time_arm_mode2_1200s = now; // 20min
        motor1StopState = 0;
        motor2StopState = 0;
        motor3StopState = 0;
        motor4StopState = 1;
        motor1Speed     = 70;
        motor2Speed     = 50;
        motor3Speed     = 70;
        //motor4Speed     =
        motor1Direction = CW;
        motor2Direction = CW;
        motor3Direction = CW;
        //motor4Direction =
        break;
      case 130:  //arm mode3 default
        positionAndModeReg = modeAndBottom;
        //Serial.println(incoming);
        time_arm_mode3_1200s = now; // 20min
        motor1StopState = 0;
        motor2StopState = 0;
        motor3StopState = 0;
        motor4StopState = 1;
        motor1Speed     = 40;
        motor2Speed     = 40;
        motor3Speed     = 40;
        //motor4Speed     =
        motor1Direction = CW;
        motor2Direction = CW;
        motor3Direction = CW;
        //motor4Direction =
        break;
      case 111:
      case 121:
      case 131: 
        //Serial.println(incoming);
        arm_mode_all_strength_plus = 1;
        break;
      case 112:
      case 122:
      case 132:  
        //Serial.println(incoming);
        arm_mode_all_strength_minus = 1;
        break;
      case 210:  // leg mode1 default
        positionAndModeReg = modeAndBottom;
        //Serial.println(incoming);
        time_leg_mode1_20s   = now;
        time_leg_mode1_22s   = now; // 22s计时工具，为了达成2s休息计时存在
        time_leg_mode1_1200s = now; // 20min
        motor1StopState = 0;
        motor2StopState = 0;
        motor3StopState = 0;
        motor4StopState = 0;
        motor1Speed     = 85;
        motor2Speed     = 100;
        motor3Speed     = 100;
        motor4Speed     = 85;
        motor1Direction = CW;
        motor2Direction = CW;
        motor3Direction = CW;
        motor4Direction = CW;
        break;
      case 220:  // leg mode2 default
        positionAndModeReg = modeAndBottom;
        //Serial.println(incoming);
        time_leg_mode2_300s  = now; // 5min
        time_leg_mode2_1200s = now; // 20min
        motor1StopState = 0;
        motor2StopState = 0;
        motor3StopState = 0;
        motor4StopState = 0;
        motor1Speed     = 70;
        motor2Speed     = 50;
        motor3Speed     = 70;
        motor4Speed     = 70;
        motor1Direction = CW;
        motor2Direction = CW;
        motor3Direction = CW;
        motor4Direction = CW;
        break;
      case 230:  // leg mode3 default
        positionAndModeReg = modeAndBottom;
        //Serial.println(incoming);
        time_leg_mode3_1200s = now; // 20min
        motor1StopState = 0;
        motor2StopState = 0;
        motor3StopState = 0;
        motor4StopState = 0;
        motor1Speed     = 55;
        motor2Speed     = 55;
        motor3Speed     = 55;
        motor4Speed     = 55;
        motor1Direction = CW;
        motor2Direction = CW;
        motor3Direction = CW;
        motor4Direction = CW;
        break;
      case 211:
      case 221:
      case 231: 
        //Serial.println(incoming);
        leg_mode_all_strength_plus = 1;
        break;
      case 212:
      case 222:
      case 232:  
        //Serial.println(incoming);
        leg_mode_all_strength_minus = 1;
        break;
      case 255:   // 全停
        positionAndModeReg = modeAndBottom;
        //Serial.println(incoming);
        motor1StopState = 1;
        motor2StopState = 1;
        motor3StopState = 1;
        motor4StopState = 1;
        //Serial.println("ready to return 255 for changing stop to gray");
        ESP_BT.write(255); //app接收到0之后，将 对应mode 按钮显示灰色
        break;
      default:
        //Serial.print(incoming);
        //Serial.println("from default in switchcase");
        break;
    }
    motorStatusChange(motor1StopState,motor2StopState,motor3StopState,motor4StopState,
                      motor1Speed, motor1Direction,
                      motor2Speed, motor2Direction,
                      motor3Speed, motor3Direction,
                      motor4Speed, motor4Direction);
  }
}
