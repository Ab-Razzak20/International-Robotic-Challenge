#include <EEPROM.h>
#include <Servo.h>
#include <NewPing.h>

Servo servoL, servoR, servo, servoIR;

#define TRIGGER_PIN1  26 
#define ECHO_PIN1     24 
#define MAX_DISTANCE1 30

NewPing sonarFront(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1);

const byte analogInPin1 = A8;
const byte analogInPin2 = A10;
const byte analogInPin3 = A9;
const byte analogInPin4 = A3;
const byte analogInPin5 = A1;
const byte analogInPin6 = A0;
const byte analogInPin0 = A4;  //Zero means Mid sensor

const byte gridPinR = A2;
const byte gridPinL = A11;

const byte frontPin0 = A5; 
const byte frontPin1 = A12;


const byte EnA = 7, EnB = 6;  //***dont change***
const byte InA = 37, InB = 35, InC = 41, InD = 39;


const byte led1 = 30, led2 = 32, led3 = 34;
const byte sw1=36, sw2=38, sw3=40;

const byte buzzer = 8;

int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorValue5 = 0;
int sensorValue6 = 0;
int sensorValue0 = 0;

int gridSensorValueL = 0;
int gridSensorValueR = 0;

int frontSensorValue0 = 0;
int frontSensorValue1 = 0;

const byte AA= 0, BB= 1;

//threshold
int Th1, Th2, Th3, Th4, Th5, Th6, Th0;
int ThgL, ThgR;
int Thf0, Thf1;

byte s1, s2, s3, s0, s4, s5, s6;
byte gsL, gsR;
byte fs0, fs1;

//setups......
byte motorSpeed = 100;     //-----parcent(primary)----
byte controlSpeed = 100, controlSpeedOn = 1;
volatile int setRPM = 100;          //-----percent-------------

int maxRPM = 400;
byte maxX=3, maxY=7;


//variables.....
const byte A=1, W=2, D=3, S=4, stop=5;
byte currentDir = W;

int currentX, currentY, nextX, nextY, currentPos = 0;
int linePos = 0, lineMaxR = 0, aR=1, aL=1, lineMaxL = 0, dry_run_breakPoint, nodeTmp = 0, led, node_i, followPath_breakPoint, stop_i= 0, move_L=100, move_R=100, finger = 2, arm = 1;
int justTurned = 0, smActivator = 0, fdActivator = 0, dryRunProgress = 0, dontBreak=0;


//for path generation......
int targetX, targetY;

byte pos[10][10];
byte X, Y;
int block;

byte workingPos[10][10];
//byte cal[30][30];

int path[30];

//int path[30] = {0, 1, 2, 3, 4, 14, 13, 12,2, 3,13,12,11,10, 120};
//int path[30] = {0,1,2,3,4,14,13,12,11,10,120};

const int started = 1, notStarted = 2, stopped = 3, reached = 5;
int  startPosition=0, target = 33;
//-----------

long previousMillis = 0;
int interval = 50;
long currentMillis;



//all interupts.
volatile long c1=0, c2=0, rpm, rotationCount = 0;;



void setup() {
   Serial.begin(57600);   
   
   servo.attach(44);   //***dont change***44,
   servoL.attach(45);  //***dont change***45
   servoR.attach(46);  //***dont change***46
   servoIR.attach(12);
   
   
   pinMode(EnA, OUTPUT);
   pinMode(EnB, OUTPUT);
   
   pinMode(InA, OUTPUT);
   pinMode(InB, OUTPUT);
   pinMode(InC, OUTPUT);
   pinMode(InD, OUTPUT);
  
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   pinMode(led3, OUTPUT);

   pinMode(analogInPin1, INPUT);
   pinMode(analogInPin2, INPUT);  
   pinMode(analogInPin3, INPUT);
   pinMode(analogInPin4, INPUT);
   pinMode(analogInPin5, INPUT);  
   pinMode(analogInPin6, INPUT);
   pinMode(analogInPin0, INPUT);
   pinMode(gridPinR, INPUT);
   pinMode(gridPinL, INPUT);
   pinMode(frontPin0, INPUT);
   pinMode(frontPin1, INPUT);
   pinMode(A13, INPUT);

   pinMode(sw1, INPUT);
   pinMode(sw2, INPUT);
   pinMode(sw3, INPUT);

   pinMode(18, INPUT);
   attachInterrupt(digitalPinToInterrupt(18), getRPM, RISING);
    
    move(0,0);

    servoIR.write(2);
    delay(100);
    servo.write(142);
    grabber(finger, 58);
    delay(50);
    LED(0,0,0);
}   
    
    
void loop() {
    
    readThreshold();
    delay(400);
    
    //----------------buttons---------------------------
    byte button1, button2, button3;
    delay(10);
    button1 = digitalRead(sw1);
    button2 = digitalRead(sw2);
    button3 = digitalRead(sw3);
    
    //calibration...
    if(button1 == HIGH && button2 == HIGH && button3 == HIGH){
       LED(1, 1, 1);
       delay(1000);
       calibration();     
    }
    
    //Dry Run...
    else if(button1 == HIGH && button2 == HIGH){
       LED(1, 1, 0);
       delay(1500);
    
       dry_run();
    
       LED(0,1,0);
       clearEEPROM();
       writeEEPROM();
       LED(1,1,1); 
       while(1){
           //nothing
       }
    }   
    

    else if(button2 == HIGH){
       LED(0, 1, 0);
       delay(500);

       readEEPROM();
        
       goto cp2;
    }   

    else if(button3 == HIGH){
       LED(0, 0, 3);
       delay(500);

       readEEPROM();
    
       goto cp3;
    }




//    while(1){
//      Serial.println(rotationCount);
//      delay(100);
//    }
    
//    grabber(finger, 90);
//    delay(10);
//    servo.write(25);
//  
//    delay(1000);
//    grabber(finger, 57);
//    delay(70);
//    servo.write(142);
//    delay(600);
//    grabber(finger, 70);
//    delay(100);
//    servo.write(152);
//    delay(50);
//    grabber(finger, 58);

    
//    grabber(finger, 70);
//    delay(150);
//    servo.write(150);
//    delay(150);
//    grabber(finger, 58);
//    servoIR.write(150);

  

//    while(1){}
//
//    while(1){
//        Serial.println(distanceIR());
//        delay(100); 
//    }


 //***************************************//
 //-----main control starts from here-----//
 //***************************************//

    readEEPROM();
    pos[3][6] = 1;


    //------step 1---------
    
    int i, j;
    for(i=0; i<10; i++){
       for(j=0; j<10; j++){
          workingPos[i][j] = pos[i][j];
       }
    }
    workingPos[0][4] = 0;
    workingPos[1][4] = 0;
    workingPos[2][4] = 0;
    workingPos[3][4] = 0;
    
    
    
    startPosition = 0;
    currentDir = W;
    target = block;    
    generatePath();    
     stop_i = 1;  // stop before 'sotp_i' nodes from target
     justTurned = 1;
     dontBreak = 1;
    followPath();
        
    if(nextX-currentX == 0 && nextY-currentY == 1){
        turn(W);
    }
    else if(nextX-currentX == 1 && nextY-currentY == 0){
        turn(D);
    }
    else if(nextX-currentX == 0 && nextY-currentY == -1){
        turn(S);
    }
    else if(nextX-currentX == -1 && nextY-currentY == 0){
        turn(A);
    }
    
    if(justTurned == 0){
        filter();
    }
    move(-200,-200);
    delay(100);
    move(0,0);

    
//    lineCorrection();

    controlSpeed = 80;
    lineCorrection();
    
    grabber(finger, 140);
    delay(10);
    servo.write(25);

    while(1){
        readSensor();
        followLine();

        int snr = sonarFront.ping_cm();
        if((snr <= 4  && snr > 1) || (s2==1 && s5==1)){
            move(-100, -100);
            delay(50);
            
            move(0,0);
            break;
        }
    }

    grabber(finger, 57);
    delay(110);
    servo.write(142);
    delay(1000);
    grabber(finger, 70);
    delay(100);
    servo.write(152);
    delay(50);
    grabber(finger, 58);
    
    controlSpeed = 100;



    //-------step 2------------

    startPosition = block;
    target = 31;    
    generatePath();
     stop_i = 0;  // stop before 'sotp_i' nodes from target
     justTurned = 1;
     dontBreak = 1;
    followPath();

    turn(D);
    
    if(justTurned == 0){
        filter();
    }
    move(-100,-100);
    delay(100);
    move(0,0);


    //--------step 3 (passing through the extention)-----------

    
    
    passDepositZone();

    cp2:
 
    depositeBox();

    delay(200);

    controlSpeed = 50;
    
    while(1){
        readSensor();
        followLine();
        if(gsL==1 && gsR==1){
            break;
        }
    }
    while(1){
        readSensor();
        followLine();
        if(gsL==0 && gsR==0){
            break;
        }
    }

    currentDir = W;
    turn(A);

    cp3:

    while(1){
        readSensor();
        followLine();
        if(gsL==1 && gsR==1){
            break;
        }
    }
    while(1){
        readSensor();
        followLine();
        if(gsL==0 && gsR==0){
            break;
        }
    }

    delay(150);

    move(-255,-255);
    delay(200);
    move(0,0);

    int stt = motorSpeed;
    motorSpeed = 70;
    if(pos[3][5] == 1){
        turn(W);
        startPosition = 35;
    }

    else {
        turn(S);
        startPosition = 34;
    }
    motorSpeed = stt;

    lineCorrection();
    move(-200,-200);
    delay(160);
    move(0,0);


    //--------step 4-----------

    for(i=0; i<10; i++){
       for(j=0; j<10; j++){
          workingPos[i][j] = pos[i][j];
       }
    }
    
    workingPos[0][3] = 0;
    workingPos[1][3] = 0;
    workingPos[2][3] = 0;
    workingPos[3][3] = 0;
 
    
    //startPosition is defined in passExtension;
    target = 36;                    //common point
    generatePath();    
     stop_i = 1;  // stop before 'sotp_i' nodes from target
     justTurned = 1;
     dontBreak = 1;
    followPath();

    if(nextX-currentX == 0 && nextY-currentY == 1){
        turn(W);
    }
    else if(nextX-currentX == 1 && nextY-currentY == 0){
        turn(D);
    }
    else if(nextX-currentX == 0 && nextY-currentY == -1){
        turn(S);
    }
    else if(nextX-currentX == -1 && nextY-currentY == 0){
        turn(A);
    }
    
    if(justTurned == 0){
        filter();
    }
    move(-200,-200);
    delay(100);
    move(0,0);

    while(1){
        readSensor();
        followLine();
        if(s1==0 && s2==0 && s3==0 && s0==0 && s4==0 && s5==0 && s6==0){
            break;
        }
    }
    while(1){
        readSensor();
        followLine();
        if(s1==1 || s2==1 || s3==1 || s0==1 || s4==1 || s5==1 || s6==1){
            break;
        }
    }
    while(1){
        readSensor();
        followLine();
        if(s1==0 && s2==0 && s3==0 && s0==0 && s4==0 && s5==0 && s6==0){
            break;
        }
    }
    while(1){
        readSensor();
        followLine();
        if(s1==1 || s2==1 || s3==1 || s0==1 || s4==1 || s5==1 || s6==1){
            break;
        }
    }
    
    move(-200,-200);
    delay(60);
    move(0,0);

    turn(A);
    
    move(-200,-200);
    delay(300);
    move(0,0);
    
    //common point reached.....
    
    LED(0,1,0);

    while(1){
        readSensor();
        if(gsL == 1 && gsR == 1){
            LED(1,1,1);
            delay(3000);

            
            
            while(1){
                readSensor();
                if(gsL == 0 && gsR == 0){
                    move(0,0);
                    break;
                }
                followLine();
            }

            break;
        }
    }



    //-----------final step-------------

    startPosition = 26;
    target = 7;    
    generatePath();    
     stop_i = 0;  // stop before 'sotp_i' nodes from target
     justTurned = 1;
     dontBreak = 0;


    currentX = 2;
    currentY = 6;

    nextX = conX(path[1]);
    nextY = conY(path[1]);
    

    if(nextX-currentX == 0 && nextY-currentY == 1){
        turn(W);
    }
    else if(nextX-currentX == 1 && nextY-currentY == 0){
        turn(D);
    }
    else if(nextX-currentX == 0 && nextY-currentY == -1){
        turn(S);
    }
    else if(nextX-currentX == -1 && nextY-currentY == 0){
        turn(A);
    }

    for(i = 0; i < 20; i++){
       path[i] = path[i+1];
    }
     
    followPath();

    move(100, 100);
    delay(300);
    move(0,0);

    LED(1,0,1);
    
    while(1){
       // readSensor();
       // followLine();
    }

//    while(1){
//        Serial.println(rpm);
//        delay(1000);
//    }
    
}



void filter(){

   previousMillis = millis();
   while(justTurned == 0){
       readSensor();
       followLine();
       
       currentMillis = millis();
       if(currentMillis- previousMillis > 40){
          break; 
       }
   }
   
   while(1){
       readSensor();
       if(s1==0 && s6==0 && gsL==0 && gsR==0){
           break;
       }
       followLine();
   }
    
}


