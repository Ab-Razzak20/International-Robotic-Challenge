void turn(int newDir){    
    byte state = controlSpeedOn;
    controlSpeedOn = 0;
    
    if(newDir == stop){

//        while(1){
//            readSensor();
//            if(s1==0 && s6==0 && gsL==0 && gsR==0){
//                break;
//            }
//            followLine();
//        }

        if(dontBreak == 0){
            move(-150,-150);
            delay(200);
        }
        move(0, 0);

        LED(LOW, LOW, LOW);

        controlSpeedOn = state;
        justTurned = 0;
        return;
    }
    
    
    if(currentDir == newDir){
        controlSpeedOn = state;
        justTurned = 0;
        return;
    }
    
    justTurned = 1;

//    move(-150,-150);
//    delay(200);
    
//    noInterrupts();
//    int pp = rpm;
//    interrupts();
//    pp = 255 - pp*255/maxRPM;
        
    int pp = 0;
    int nn = -190;
        
    pp = -20 +(400 - rpm) / 1.4;
    nn = - (185 + (rpm - 150) / 2) - 50;
        
    if(pp > 255)        pp = 255;
    else if(pp < -255)  pp = -255;
    if(nn > 255)        nn = 255;
    else if(nn < -255)  nn = -255;
        
    if(dryRunProgress == 1 && (currentDir == W || currentDir == S)){
        pp = pp-50;
        nn = -205;
    }
    
//    if(rpm < 300){
//        pp = 30;
//        LED(1,1,1);
//    }
//    if(rpm < 250){
//        pp = 120;
//        nn = -160;
//        LED(1,1,0);
//    }
//    if(rpm < 150){
//        pp = 90;
//        nn = -150;
//        LED(1,0,0);
//    }
    
    //Turn Right......
    if(currentDir - newDir == -1 || currentDir - newDir == 3){
        
        move(pp, nn);
        delay(170);
        
        previousMillis = millis();                        //stucked detection
        while(1){
            readSensor();
            if(fs0 == 0){
                break;
            }
           
            currentMillis = millis();                      //stucked detection
            if(currentMillis - previousMillis > 3000){     //stucked detection
                move(255, -255);                           //stucked detection
            }                                              //stucked detection
        }
         
        previousMillis = millis();                        //stucked detection
        while(1){
            readSensor();
            if(fs0 == 1){
                currentDir = newDir;
                                   
                move(-250, 250);
                delay(90);
               // lineCorrection();
                move(100,100);
                delay(20);
                move(0,0);
            
                while(1){
                    readSensor();
                    if(s1==0 || s6==0){
                        break;
                    }
                    followLine();
                }

                controlSpeedOn = state;
                return;
            }
             
            currentMillis = millis();                      //stucked detection
            if(currentMillis - previousMillis > 3000){     //stucked detection
                move(255, -255);                           //stucked detection
            }                                              //stucked detection
        }
    }    
        
    //Turn Left........
    else if(currentDir - newDir == 1 || currentDir - newDir == -3){
         
        move(nn, pp);
        delay(200);
         
        previousMillis = millis();                        //stucked detection
        while(1){
            readSensor();
            if(fs0 == 0){
                break;
            } 
           
            currentMillis = millis();                      //stucked detection
            if(currentMillis - previousMillis > 3000){     //stucked detection
                move(-255, 255);                           //stucked detection
            }                                              //stucked detection
        }
        
        previousMillis = millis();                        //stucked detection
        while(1){
            readSensor();
            if(fs0 == 1){
                currentDir = newDir;
                      
                move(250, -250);
                delay(90);
              //  lineCorrection();
                move(100,100);
                delay(20);
                move(0,0);
                      
                while(1){
                    readSensor();
                    if(s1==0 || s6==0){
                        break;
                    }
                    followLine();
                }

                controlSpeedOn = state;
                return;
            }
            
            currentMillis = millis();                      //stucked detection
            if(currentMillis - previousMillis > 3000){     //stucked detection
                move(-255, 255);                           //stucked detection
            }                                              //stucked detection
        }
    }
    
    
    
    // U turn.....
    else if (currentDir - newDir == 2 || currentDir - newDir == -2){

       move(-150,-150);
       delay(70);
       
       if(currentX==0 && currentDir==W){
           uTurnR();
           currentDir = newDir;

           controlSpeedOn = state;
           return;
       }
    
       else if(currentX==0 && currentDir==S){
           uTurnL();
           currentDir = newDir;

           controlSpeedOn = state;
           return;
       }
       
       else if(currentX==maxX && currentDir==W){
           uTurnL();
           currentDir = newDir;

           controlSpeedOn = state;
           return;
       }
    
       else if(currentX==maxX && currentDir==S){
           uTurnR();
           currentDir = newDir;

           controlSpeedOn = state;
           return;
       }
       
       
       
       else if(currentY==0 && currentDir==D){
           uTurnL();
           currentDir = newDir;

           controlSpeedOn = state;
           return;
       }
       
       else if(currentY==0 && currentDir==A){
           uTurnR();
           currentDir = newDir;

           controlSpeedOn = state;
           return;
       }
       
       else if(currentY==maxY && currentDir==D){
           uTurnR();
           currentDir = newDir;

           controlSpeedOn = state;
           return;
       }
       
       else if(currentY==maxY && currentDir==A){
           uTurnL();
           currentDir = newDir;

           controlSpeedOn = state;
           return;
       }
        
        
       else {
           uTurnR();
           currentDir = newDir;

           controlSpeedOn = state;
           return;
       }
     
    }

    controlSpeedOn = state;
}



void uTurnR(){   
   move(140, -170);
   uTurn_cp();

   move(-250, 200);
   delay(80);
   while(1){
       readSensor();
       if(gsL==0 || gsR==0){
           break;
       }
       followLine();
   }
   move(0,0);
   return;   
}

void uTurnL(){
   move(-170, 140);
   uTurn_cp();

   
   move(200, -250);
   delay(80);
   while(1){
       readSensor();
       if(gsL==0 || gsR==0){
           break;
       }
       followLine();
   }
   move(0,0);
   return;  
}


void uTurn_cp(){
   delay(70);
   while(1){
      readSensor();
      if(fs0 == 0){
         break;
      }
   }
   
   while(1){
      readSensor();
      if((fs0 == 1) && (s1==0 || s2==0 || s5==0 || s6==0)){
         break;
      }
   }
   
   delay(70);
   
   while(1){
      readSensor();
      if(fs0 == 0){
         break;
      } 
   }
   
   while(1){
       readSensor();
       if((fs0==1) && (s1==0 || s2==0 || s5==0 || s6==0)){
           return;
       }
   }
}





void lineCorrection(){
        
    previousMillis = millis();
    long pmls = millis();
    long cmls;
        
    while(1){
        readSensor();
        
        int corr_L = s1 + s2 + s3;
        int corr_R = s4 + s5 + s6;
        
        cmls = millis();
        
        if(corr_L > corr_R){
            move(-180,180);
            pmls = millis();
        }
        else if(corr_L < corr_R){
            move(180,-180);
            pmls = millis();
        }
        else if(corr_L == corr_R && cmls - pmls > 40){
            break;
        }
        
        currentMillis = millis();
        if(currentMillis - previousMillis > 200){
            break;
        }
    }

    move(0,0);

}




