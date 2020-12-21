void writeEEPROM(){
    byte i, j;
    int address=0;
    
    for(j=0; j<=maxY; j++){
        for(i=0; i<=maxX; i++){          
            EEPROM.write(address, pos[i][j]);
            address++;
        }
    }
    
    EEPROM.write(60, block);
}



void readEEPROM(){
    byte i, j;
    int address=0;
    
    for(j=0; j<=maxY; j++){
        for(i=0; i<=maxX; i++){
            pos[i][j] = EEPROM.read(address);
            address++;
        }
    }
    
    block = EEPROM.read(60);
}


void clearEEPROM(){
   int i;
   for (i = 0; i < 63; i++){
      EEPROM.write(i, 0);
   }
}



void readThreshold(){
    Th1 = EEPROM.read(75) * 6;
    Th2 = EEPROM.read(76) * 5;
    Th3 = EEPROM.read(77) * 4;
    Th4 = EEPROM.read(78) * 4;
    Th5 = EEPROM.read(79) * 5;
    Th6 = EEPROM.read(80) * 6;
    Th0 = EEPROM.read(81) * 4;

    ThgL = EEPROM.read(82) * 4;
    ThgR = EEPROM.read(83) * 3;

    Thf0 = EEPROM.read(84) * 5;
    Thf1 = EEPROM.read(85) * 5;

/*
    Serial.print(Th1);
    Serial.print("   ");
    Serial.print(Th2);
    Serial.print("   ");
    Serial.print(Th3);
    Serial.print("   ");
    Serial.print(Th0);
    Serial.print("   ");
    Serial.print(Th4);
    Serial.print("   ");
    Serial.print(Th5);
    Serial.print("   ");
    Serial.print(Th6);
    Serial.print("       ");
    
    Serial.print(ThgL);
    Serial.print("   ");
    Serial.print(ThgR);
    Serial.print("       ");

    Serial.print(Thf0);
    Serial.print("   ");
    Serial.println(Thf1);
*/
}


void LED(byte ii, byte jj, byte kk){  
    digitalWrite(led1, ii);  //Red
    digitalWrite(led2, jj);  //Yellow
    digitalWrite(led3, kk);  //green 

    if(ii==1 || jj==1 || kk==1){
        led = 1;
    }
    else led = 0;
}




void grabber(byte servoNo, int val){
  
   int currentVal, i;
   
   if(servoNo == 1){     
      currentVal = servo.read();
      
      if(val > currentVal){
         for(i = currentVal; i <= val; i++){                                  
            servo.write(i);              
            delay(15);
         }         
      }
      
      else if(val < currentVal){
         for(i = currentVal; i >= val; i--){                                  
            servo.write(i);              
            delay(15);
         }         
      }
      
      else servo.write(val); 
   }
   
   
   
   else if(servoNo == 2){ 
      int val2 = 180-val+20;
      if(val2>180){
          val2 = 180;  
      }
      servoL.write(val2);
      servoR.write(val);      
   }
}




void depositeBox(){

    servoIR.write(150);
    
    controlSpeed = 90;
    
    int cnt1, cnt2;
    cnt1 = rotationCount;
    
    while(1){
        readSensor();
        followLine();
    
        cnt2 = rotationCount;
        
        if(distanceIR() >= 22 && distanceIR() < 30 && cnt2-cnt1 > 16 ){
            break;
        }
        
    }
    
    move(-250,-250);
    delay(200);
    move(0,0);
    
    move(-100,-100);
    while(1){
        if(distanceIR() < 30){
            delay(20);
            break;
        }
    }
    while(1){
        if(distanceIR() > 33){
            move(100,100);
            delay(30);
            move(0,0);
            break;
        }
    }

    controlSpeed = 50;
    
    while(1){
        readSensor();
        followLine();

        if(distanceIR() >= 22 && distanceIR() < 30){
            move(-100,-100);
            delay(70);
            move(0,0);
            break;
        }
        
    }

    servoIR.write(2);

    controlSpeed = 100;

      grabber(finger, 70);
      delay(200);
      servo.write(152);
      delay(150);
      grabber(finger, 58);
      delay(40);

      grabber(arm, 22);
      delay(100);
    
      move(-100, -100);
      delay(400);
      
      move(180,-140);
      delay(360);
      move(-140, 120);
      delay(320);
      move(180,-140);
      delay(130);
      move(0,0);
      delay(200);


    grabber(finger, 75);
    delay(150);
    servo.write(152);
    delay(100);
    grabber(finger, 58);
    
    
}



int distanceIR(){
    int dstnsIR = 0, i;
    
    for(i = 0; i< 1; i++){
       dstnsIR = dstnsIR + analogRead(13);
       delayMicroseconds(1);
    }

    dstnsIR = dstnsIR / 10;

    return dstnsIR;
}





void passDepositZone(){

    servoIR.write(150);
    
    controlSpeed = 70;

    while(1){
        readSensor();
        followLine();

        if(gsL == 1 && gsR == 1){
            break;
        }
        
        int snr = sonarFront.ping_cm();
        if(snr <= 30  && snr > 0){
            move(-100, -100);
            delay(50);
            move(0,0);  
        }

        if(distanceIR() >= 22 && distanceIR() < 30){
            move(-150, -150);
            
            while(1){
                if(distanceIR() > 33){
                    delay(200);
                    move(100,100);
                    delay(30);
                    move(0,0);

                    while(1){
                        snr = sonarFront.ping_cm();
                        if(snr <= 30  && snr > 0){
                            break;
                        }
                    }

                    while(1){
                        snr = sonarFront.ping_cm();
                        if( ! (snr <= 30  && snr > 0)){
                            break;
                        }
                    }
                    
                    break;
                }
            }
        }

    }

    currentDir = D;
    turn(W);
}


