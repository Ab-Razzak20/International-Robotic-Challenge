
void readSensor(){
  sensorValue1 = analogRead(analogInPin1);
  sensorValue2 = analogRead(analogInPin2);
  sensorValue3 = analogRead(analogInPin3);
  sensorValue4 = analogRead(analogInPin4);
  sensorValue5 = analogRead(analogInPin5);
  sensorValue6 = analogRead(analogInPin6);
  sensorValue0 = analogRead(analogInPin0);
  
  gridSensorValueL = analogRead(gridPinL);
  gridSensorValueR = analogRead(gridPinR);
  
  frontSensorValue0 = analogRead(frontPin0);
  frontSensorValue1 = analogRead(frontPin1);
  
  
  if(sensorValue1 > Th1)
     s1= AA;
  else s1= BB;
  
  if(sensorValue2 > Th2)
     s2= AA;
  else s2= BB;
  
  if(sensorValue3 > Th3)
     s3= AA;
  else s3= BB;
  
  if(sensorValue4 > Th4)
     s4= AA;
  else s4= BB;
  
  if(sensorValue5 > Th5)
     s5= AA;
  else s5= BB;
  
  if(sensorValue6 > Th6)
     s6= AA;
  else s6= BB;

  if(sensorValue0 > Th0)
     s0= AA;
  else s0= BB;
  
  //grid sensor
  if(gridSensorValueL > ThgL)
     gsL= AA;
  else gsL= BB;
  
  if(gridSensorValueR > ThgL)
     gsR= AA;
  else gsR= BB;
  
  //front sensor
  if(frontSensorValue0 > Thf0)
     fs0= AA;
  else fs0= BB;
  
  if(frontSensorValue1 > Thf1)
     fs1= AA;
  else fs1= BB;
  
  
/*
  Serial.print(s1);
  Serial.print("   ");
  Serial.print(s2);
  Serial.print("   ");
  Serial.print(s3);
  Serial.print("   ");
  Serial.print(s0);
  Serial.print("   ");
  Serial.print(s4);
  Serial.print("   ");
  Serial.print(s5);
  Serial.print("   ");
  Serial.print(s6);
  Serial.print("       ");
  
  Serial.print(gsL);
  Serial.print("   ");
  Serial.print(gsR);
  
  Serial.print("       ");
  Serial.print(fs0);
  Serial.print("   ");
  Serial.println(fs1);
*/
  
}
  
  
void move(int left, int right){
  
  move_L = left;
  move_R = right;
  
  if(motorSpeed != 100){
     left = (left*motorSpeed)/100;
     right = (right*motorSpeed)/100;
  }

  if(controlSpeed != 100 && controlSpeedOn == 1){
     left = (left*controlSpeed)/100;
     right = (right*controlSpeed)/100;
  }
  
  int speedA, speedB;
  
  if(right >= 0){
    speedA = right;
    analogWrite(EnA, speedA);
    digitalWrite(InA, HIGH);
    digitalWrite(InB, LOW);
  }
  else if(right < 0){
    speedA = -right;
    analogWrite(EnA, speedA);
    digitalWrite(InA, LOW);
    digitalWrite(InB, HIGH);
  }
   
  
  if(left >= 0){
    speedB = left;
    analogWrite(EnB, speedB);
    digitalWrite(InC, HIGH);
    digitalWrite(InD, LOW);
  }
  else if(left < 0){
    speedB = -left;       
    analogWrite(EnB, speedB);
    digitalWrite(InC, LOW);
    digitalWrite(InD, HIGH);
  }
  
}
  
  
void calibration(){
  
  int Th1H=0, Th2H=0, Th3H=0, Th4H=0, Th5H=0, Th6H=0, Th0H=0;
  int Th1L=1023, Th2L=1023, Th3L=1023, Th4L=1023, Th5L=1023, Th6L=1023, Th0L=1023;
  
  int ThgLH=0, ThgLL=1023, ThgRH=0, ThgRL=1023;
  
  int Thf0H=0, Thf0L=1023, Thf1H=0, Thf1L=1023;
  
  
  LED(0,1,0);
  previousMillis = millis();
  
  while(1){
     currentMillis = millis();
     if(currentMillis- previousMillis > 5000){
         break;
     }
     
     readSensor();
     
     if(sensorValue1 > Th1H){
         Th1H = sensorValue1;
     }
     if(sensorValue2 > Th2H){
         Th2H = sensorValue2;
     }
     if(sensorValue3 > Th3H){
         Th3H = sensorValue3;
     }
     if(sensorValue4 > Th4H){
         Th4H = sensorValue4;
     }
     if(sensorValue5 > Th5H){
         Th5H = sensorValue5;
     }
     if(sensorValue6 > Th6H){
         Th6H = sensorValue6;
     }
     if(sensorValue0 > Th0H){
         Th0H = sensorValue0;
     }
     
     
     if(sensorValue1 < Th1L){
         Th1L = sensorValue1;
     }
     if(sensorValue2 < Th2L){
         Th2L = sensorValue2;
     }
     if(sensorValue3 < Th3L){
         Th3L = sensorValue3;
     }
     if(sensorValue4 < Th4L){
         Th4L = sensorValue4;
     }
     if(sensorValue5 < Th5L){
         Th5L = sensorValue5;
     }
     if(sensorValue6 < Th6L){
         Th6L = sensorValue6;
     }
     if(sensorValue0 < Th0L){
         Th0L = sensorValue0;
     }


     if(gridSensorValueL > ThgLH){
         ThgLH = gridSensorValueL;
     }
     if(gridSensorValueR > ThgRH){
         ThgRH = gridSensorValueR;
     }
     
     if(gridSensorValueL < ThgLL){
         ThgLL = gridSensorValueL;
     }
     if(gridSensorValueR < ThgRL){
         ThgRL = gridSensorValueR;
     }
     

     if(frontSensorValue0 > Thf0H){
         Thf0H = frontSensorValue0;
     }
     if(frontSensorValue1 > Thf1H){
         Thf1H = frontSensorValue1;
     }
     
     if(frontSensorValue0 < Thf0L){
         Thf0L = frontSensorValue0;
     }
     if(frontSensorValue1 < Thf1L){
         Thf1L = frontSensorValue1;
     }
     
  } 
  
  Th1 = (Th1H + Th1L) / 2;
  Th2 = (Th2H + Th2L) / 2;
  Th3 = (Th3H + Th3L) / 2;
  Th4 = (Th4H + Th4L) / 2;
  Th5 = (Th5H + Th5L) / 2;
  Th6 = (Th6H + Th6L) / 2;
  Th0 = (Th0H + Th0L) / 2;

  ThgL = (ThgLH + ThgLL) / 2;
  ThgR = (ThgRH + ThgRL) / 2;

  Thf0 = (Thf0H + Thf0L) / 2;
  Thf1 = (Thf1H + Thf1L) / 2;
  
  LED(HIGH, LOW, LOW);
  delay(500);
  
  EEPROM.write(75, Th1/5);
  EEPROM.write(76, Th2/5);
  EEPROM.write(77, Th3/5);
  EEPROM.write(78, Th4/5);
  EEPROM.write(79, Th5/5);
  EEPROM.write(80, Th6/5);
  EEPROM.write(81, Th0/5);
  
  EEPROM.write(82, ThgL/5);
  EEPROM.write(83, ThgR/5);
  
  EEPROM.write(84, Thf0/5);
  EEPROM.write(85, Thf1/5);
  
  delay(100);
  LED(HIGH, HIGH, HIGH);
  
  while(1){
    //nothing
  }
}




void followLine(){

  if(s3==0 && s4==1 && aL==1){
      lineMaxR = 0;
      aL=0;
      aR=1; 
  }
  if(s3==1 && s4==0 && aR==1){
      lineMaxL = 0;
      aL=1;
      aR=0; 
  }
  
  if(linePos < 0 && abs(linePos) > lineMaxL){      
         lineMaxL = abs(linePos);
  }
  else if(linePos > 0 && abs(linePos) > lineMaxR){      
         lineMaxR = abs(linePos);
  }




  if(s1==0 && s2==0 && s3==0 && s0==1 && s4==0 && s5==0 && s6==0){
      linePos = 0;
      move(255, 255);
      
      smActivator == 0;
  }
  else if(s1==0 && s2==0 && s3==1 && s4==1 && s5==0 && s6==0){
      linePos = 0;
      move(255, 255);
      
      smActivator == 0;
  }
  
  else if(s1==0 && s2==0 && s3==1 && s4==0 && s5==0 && s6==0){
      if(linePos > -1){
          fastDecL1();
      }
      else if(linePos < -1){
          smothL();
      }
      
      linePos = -1;
      move(180,255);
  }
  else if(s1==0 && s2==1 && s3==1 && s4==0 && s5==0 && s6==0){
      if(linePos > -2){
          fastDecL();
      }
      else if(linePos < -2){
          smothL();
      }
      
      linePos = -2;
      move(100, 250);
  }   
  else if(s1==0 && s2==1 && s3==0 && s4==0 && s5==0 && s6==0){
      if(linePos > -3){
          fastDecL();
      }
      else if(linePos < -3){
          smothL();
      }
      
      linePos = -3;
      move(30, 180);
  }   
  else if(s1==1 && s2==1 && s3==0 && s4==0 && s5==0 && s6==0){
      if(linePos > -4){
          fastDecL();
      }
      linePos = -4;
      move(-40, 170);
  }   
  else if(s1==1 && s2==0 && s3==0 && s4==0 && s5==0 && s6==0){
      if(linePos > -5){
          fastDecL();
      }
      linePos = -5;
      move(-50, 160);
  }
  
  
  //-----------------
  else if(s1==0 && s2==0 && s3==0 && s4==1 && s5==0 && s6==0){
      if(linePos < 1){
          fastDecR1();
      }
      else if(linePos > 1){
          smothR();
      }
      
      linePos = 1;
      move(255, 180);
  }
  else if(s1==0 && s2==0 && s3==0 && s4==1 && s5==1 && s6==0){
      if(linePos < 2){
          fastDecR();
      }
      else if(linePos > 2){
          smothR();
      }
      
      linePos = 2;
      move(250, 100);
  }
  else if(s1==0 && s2==0 && s3==0 && s4==0 && s5==1 && s6==0){
      if(linePos < 3){
          fastDecR();
      }
      else if(linePos > 3){
          smothR();
      }
      
      linePos = 3;
      move(180, 30);
  }
  else if(s1==0 && s2==0 && s3==0 && s4==0 && s5==1 && s6==1){
      if(linePos < 4){
          fastDecR();
      }
      linePos = 4;
      move(170, -40);
  }
  else if(s1==0 && s2==0 && s3==0 && s4==0 && s5==0 && s6==1){
      if(linePos < 5){
          fastDecR();
      }
      linePos = 5;
      move(160, -50);
  }
  
  //3 sensor
  else if(s1==0 && s2==1 && s3==1 && s4==1 && s5==0 && s6==0){
      if(linePos > -1){
          fastDecL();
      }
      linePos = -1;
      move(130, 255);
  }
  else if(s1==0 && s2==0 && s3==1 && s4==1 && s5==1 && s6==0){
      if(linePos < 1){
          fastDecR();
      }
      linePos = 1;
      move(255, 130);
  }
  
  else if(s1==1 && s2==1 && s3==1 && s4==0 && s5==0 && s6==0){
      if(linePos > -3){
          fastDecL();
      }      
      linePos = -3;
      move(20, 255);
  }
  else if(s1==0 && s2==0 && s3==0 && s4==1 && s5==1 && s6==1){
      if(linePos < 3){
          fastDecR();
      }
      linePos = 3;
      move(255, 20);
  }

  

  //reverse color......
  else if(s1==1 && s2==1 && s3==1 && s0==0 && s4==1 && s5==1 && s6==1){
      move(255, 255);
  }
  else if(s1==1 && s2==1 && s3==0 && s4==0 && s5==1 && s6==1){
      move(255, 255);
  }
  
  else if(s1==1 && s2==1 && s3==0 && s4==1 && s5==1 && s6==1){
      move(210,255);
  }
  else if(s1==1 && s2==1 && s3==1 && s4==0 && s5==1 && s6==1){
      move(255, 210);
  }



  else{
      move(150, 150);
  }
  
  if(s1==1 && s6==1){
      move(200, 200);
  }
  
}



void fastDecL(){
    move(-255,0);
    delay(10);
    smActivator = 1;
    fdActivator = 1;
}
void fastDecR(){
    move(0,-255);
    delay(10);
    smActivator = 1;
    fdActivator = 1;
}

void fastDecL1(){
    if(fdActivator = 1){
        move(-255,0);
        delay(10);
        fdActivator = 0;
    }
}
void fastDecR1(){
    if(fdActivator = 1){
        move(0,-255);
        delay(10);
        fdActivator = 0;
    }
}

void smothL(){
    if(smActivator == 1){
        move(255,-100);
        delay(7);
    }
}
void smothR(){
    if(smActivator == 1){
        move(-100,255);
        delay(7);
    }
}




