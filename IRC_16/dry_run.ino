
void dry_run(){
   dry_run_breakPoint = 0;
   dryRunProgress = 1;
   motorSpeed = 100;


   while(1){
      readSensor();
      followLine();
      nodeDetection();

      if(dry_run_breakPoint == 1){
          LED(0,1,0);

          pos[3][6] = 1;

          clearEEPROM();
          writeEEPROM();
          LED(1,1,1);

          dryRunProgress = 0;
          return;
      }
   }
}



void nodeDetection(){

   if(gsL==1 && gsR==1){

       delay(10);
       readSensor();

       if(nodeTmp == 0){
            X=0;
            Y=0;

            nodeTmp = 1;
       }
       else if(nodeTmp==1){
            if(currentDir==W){
                Y++;
            }
            else if(currentDir==D){
                X++;
            }
            else if(currentDir==S){
                Y--;
            }
            else if(currentDir==A){
                X--;
            }

            if(X == 3 && Y == 6){
                Y = 7;
            }
       }



       if(s3==0 || s0==0 || s4==0){
           pos[X][Y] = 0;

           LED(0,0,1);
          // tone(buzzer, 2500, 100);

           //---------block detection----------
           if(Y <= 3 && fs1 == 1){
               while(1){
                   readSensor();
                   if(gsL==0 && gsR==0){
                       break;
                   }
                   followLine();
               }

               previousMillis = millis();
               while(1){
                   readSensor();
                   if(fs1==1){
                      pos[X][Y] = 1;
                      block = conI(X, Y);
                      LED(0,1,0);
                     // tone(buzzer, 500, 400);

                      while(1){
                          readSensor();
                          followLine();
                          if(fs1 == 0){
                              break;
                          }
                      }

                      break;
                   }

                   followLine();

                   currentMillis = millis();
                   if(currentMillis- previousMillis > 60){
                      break;
                   }
               }
           }
       }


       else if (s3==1 && s0==1 && s4==1){
           pos[X][Y] = 1;
     //      LED(0,0,1);
       }


       if(X == 2 && Y == 0 && currentDir == S){
           dry_run_breakPoint = 1;
           turn(stop);
           return;
       }
       else if(Y==maxY && X==0){
           turn(D);
       }
       else if(Y==maxY && X==1){
           turn(S);
       }
       else if(Y==0 && X==1){
           turn(D);
       }
       else if(Y==0 && X==2){
           turn(D);
       }
       else if(Y==0 && X==3){
           turn(W);
       }
       else if(Y==maxY && X==3){
           turn(A);
       }
       else if(Y==maxY && X==2){
           turn(S);
       }


       if(justTurned == 1 && (currentDir == D)){
           controlSpeed = 60;
       }
       else controlSpeed = 100;

       if((Y == maxY-1 && currentDir == W) || (Y == 1 && currentDir == S) || (X==2 && Y==0) || (X==3 && Y==5) ){

            if(X==3 && Y==5){
                while(1){
                   readSensor();
                   followLine();
                   if(s2==0 && s3==0 && s0==0 && s4==0 && s5==0){
                       break;
                   }
                }

                while(1){
                   readSensor();
                   followLine();
                   if(s2==1 || s3==1 || s0==1 || s4==1 || s5==1){
                       delay(40);
                       break;
                   }
                }
            }

            move(-255,-255);
            delay(40);

            controlSpeed = 45 + (200 - rpm) / 5;
            move(0,0);

            if(controlSpeed < 40){
                controlSpeed = 40;
            }

       }



       //pass intersection........

       while(1){
           readSensor();
           if(gsL==0 && gsR==0){
               break;
           }
           followLine();
       }

       previousMillis = millis();
       while(1){
           readSensor();
           followLine();

           currentMillis = millis();
           if(currentMillis- previousMillis > 70){
              break;
           }
       }
   }


   else if(gsL==0 && gsR==0 && led==1){
       LED(0,0,0);
   }

}


