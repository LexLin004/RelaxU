# RelaxU Massager Tape

## Introduction
RelaxU Massager Tape can be controlled using an Android phone via Bluetooth. The massager consists of 4 brushed DC motors. The motors and controlled by L298N board and ESP32 board. The whole product is powered by a 120W, 12V-10A, AC to DC power adapter. The maximum power consumption of the product is about 50 watts.

## Background
I believe the following scenarios have occurred to everyone in this room.
Sitting in the lab or libraries or study rooms for hours and hours studying for exams or debugging,
or after a long flight, and when you stand up you feel that your legs are swelling and your back is stiff.
Or like this: you finally get off from your work out and feel out of breathe and tenderness in your muscle.
At these moments you feel exhausted and just want to lie down and rest. 
But if you don’t take actions, your muscles are going to ache tomorrow, 
the day after tomorrow and maybe even longer. More severely, the tiredness is secretly accumulating
in your body leading to muscle strain and sub-health, which is pretty common nowadays.
So what can we do? Study and exercises are inescapable, but a massager can stretch and relax your muscle for you.

# Final Product
![image](https://user-images.githubusercontent.com/102601885/181481010-d28b8b9a-a149-427b-8706-2db4baf93ada.png)
![image](https://user-images.githubusercontent.com/102601885/181481028-7d4a8469-8344-4869-bb12-83e36e37c373.png)
![image](https://user-images.githubusercontent.com/102601885/181481042-bf9b73d8-f633-4e46-9efc-54dd61f958a1.png)

# Circuit Design
![image](https://user-images.githubusercontent.com/102601885/181480991-824338b8-391b-4f8b-8a91-31e52ab21b71.png)

# App Design
## Introduction Pages
![image](https://user-images.githubusercontent.com/102601885/181486269-8877639a-1762-4036-8684-f86170861610.png)

## Bluetooth choose
![image](https://user-images.githubusercontent.com/102601885/181481167-8f926f3e-d2f2-48ff-afdc-e54b63d9efc6.png)

## Home Page (Select the position you want to massage.)
![image](https://user-images.githubusercontent.com/102601885/181481175-60e12692-698d-4b96-99d5-6c7736177819.png)

## Mode Page (Select mode and adjust the strength level)
![image](https://user-images.githubusercontent.com/102601885/181486433-3b81198d-e3b3-4c29-ac0e-ca170fdd79e4.png)

## Info Page (gives brief intro of what type of massage we are trying to offer and some tips.)
![image](https://user-images.githubusercontent.com/102601885/181481688-228a0f7a-5813-49d5-972f-a74f524a4282.png)


## Modes provided by the application
#### Intensity: 0(Stop) ~ 100(Highest)
###Arm:
Mode 1: Motor1: 70, Motor2: 90, Motor3: 90; Vibrate 20s, Stop 2s, Duration: 10min
Mode 2: Motor1: 70, Motor2: 50, Motor3: 70; Vibrate 2min, All motor speed  +5; Duration: 10min;
Mode 3: Motor1: 40, Motor2: 40, Motor3: 40; Duration: 10min
### Leg:
Mode 1: Motor1: 85, Motor2: 100, Motor3: 100, Motor4: 85; Vibrate 20s, Stop 2s, Duration: 10min
Mode 2: Motor1: 70, Motor2: 50  , Motor3: 70   , Motor4: 70; Vibrate 2min, All motor speed  +5, Duration: 10min
Mode 3: Motor1: 55, Motor2: 55  , Motor3: 55   , Motor4: 55; Duration: 10min
### Waist:
Mode 1: Motor1: 80, Motor2: 80  , Motor3: 80   , Motor4: 80; Vibrate 20s, Stop 2s, Duration: 10min
Mode 2: Motor1: 50, Motor2: 50  , Motor3: 50   , Motor4: 50; Vibrate 2min, All motor speed  +5, Duration: 10min

## Mode explanation
Mode1 is trying to simulate the sports massage that focuses on a specialized position rather than the entire body. It alternate the vibration direction every 20 seconds and stops to imitate finger pressing and kneading on muscles after exercises. This type of massage can help to prevent injuries by reducing fatigue and tension throughout the body.

Mode 2 offers the deep tissue massage: a massage using slow friction and deep pressure that is used to help with persistent muscle tension, pain and aches. Deep tissue massage provides many benefits including: Lowering of blood pressure, Relief of chronic muscle pain and stiffness, Loosening of painful knots in muscles, Relief of sore muscles. Those working at a desk and sitting most of the day can benefit from a deep tissue massage.
After a session of mode 2: deep tissue massage, we suggest having a cup of water to stay hydrated. This will help to flush any metabolic waste from muscle tissues. It's also common to experience tenderness for a day or two after the massage.

Mode3 is the lymphatic massage which stimulates the lymphatic system of the body and reduce swelling. It is slower and lighter and provides gentle stretching of the skin. Traditionally, a lymphatic massage is used in a medical setting to help reduce swelling after surgery or to help with fluid build-up. But now you can use it to reduce swelling when wake up in the morning or sitting for a long time during the day. It may take a few sessions to notice results with a lymphatic massage and it may even be prescribed by your doctor.
