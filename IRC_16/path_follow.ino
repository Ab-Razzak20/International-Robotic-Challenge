void followPath(){
  node_i = 0;
  followPath_breakPoint = 0;
  
  readSensor();
  if((s1==1 && s6==1) || (gsL==1 && gsR==1)){
     while(1){
        readSensor();
        followLine();
        if(s1==0 || s6==0){
            delay(50);
            break;
        }
     }
  }


  while(1){  
     readSensor();
     followLine();
     followNode();
     
     if(followPath_breakPoint == 1){
         return; 
     }
  }
}


void followNode(){
   int x, y, x1, y1;
   
   if((s1==1 && s6==1) || (gsL==1 && gsR==1)){

       int tmp_addr = 100 + node_i;
       EEPROM.write(tmp_addr, rpm/5);


//       if (setRPM != 100 && nextTurn(node_i) != 1){
//           noInterrupts();
//           setRPM = 100;
//           controlSpeed = 100;
//           interrupts();
//       }

       if(controlSpeed != 100 && nextTurn(node_i) != 1){
             controlSpeed = 100;
       }

       
       x= conX(path[node_i]);
       y= conY(path[node_i]);
       
       x1= conX(path[node_i + 1]);
       y1= conY(path[node_i + 1]);
       
       currentX = x;
       currentY = y;
       nextX = x1;
       nextY = y1;
       
       currentPos = path[node_i];
       
       
    //   LED(1,1,1);

       //block turn......
//       if(currentPos == block){
//           if(gsL==0 || gsR==0){
//              while(1){
//                  readSensor();
//                  if(gsL==1 && gsR==1){
//                      break;
//                  }
//                  followLine();
//              }
//           }
//           
//           while(1){
//               readSensor();
//               if(gsL==0 && gsR==0){
//                  break;
//               }
//               followLine();
//           }
//
//           delay(20);
//
//           readSensor();
//           if(fs1 == 1){
//               while(1){
//                  readSensor();
//                  if(fs1 == 0){
//                      break;
//                  }
//                  followLine();
//               }
//           }
//           
//           while(1){
//               readSensor();
//               if(s1==1 && s6==1){
//                  break;
//               }
//               followLine();
//           }
//           
//       }
       while(1){
           readSensor();
           followLine();
           if(fs1==0 && gsL==0 && gsR==0){
               break;
           }
       }
      

       if(path[node_i + 1 + stop_i] == 120){
           followPath_breakPoint = 1;
           turn(stop);
           return;
       }
       else if(x1-x == 0 && y1-y == 1){
           turn(W);
       }
       else if(x1-x == 1 && y1-y == 0){
           turn(D);
       }
       else if(x1-x == 0 && y1-y == -1){
           turn(S);
       }
       else if(x1-x == -1 && y1-y == 0){
           turn(A);
       }


//      if(justTurned == 1){
//          LED(1,1,1);
//          while(1){
//              readSensor();
//              followLine();
//          }
//      }
//      else LED (0,0,0);
      

       if(nextTurn(node_i) == 1){
       
            if(justTurned == 0){                                  
                 controlSpeed = 50;
                 previousMillis = millis();
                 while(1){
                     readSensor();
                     followLine();
                     
                     currentMillis = millis();
                     if(currentMillis- previousMillis > 30){
                        break; 
                     }
                 }
                             
                 if(rpm > 270){
                     move(-255,-255);
                     delay(10);
                   //  LED(1,0,1);
                 }
            }
             
//            controlSpeed = 50;
//            if(rpm < 220){
//                controlSpeed = 70;
//            }

            controlSpeed = 60 + (300 - rpm) / 5;
            if(justTurned == 1){
                controlSpeed = 100;
            }
            if(controlSpeed < 55){
                controlSpeed = 55;
            }
            move(move_L, move_R);
       }
       

       while(1){
           readSensor();
           if(s1==0 && s6==0 && gsL==0 && gsR==0){
               break;
           }
           followLine();
       }
       
       previousMillis = millis();
       while(justTurned == 0){
           readSensor();
           followLine();
           
           currentMillis = millis();
           if(currentMillis- previousMillis > 40){
              break; 
           }
       }
       
       node_i++;
       
       
//       //edge speed slow down
//       if((nextX==0 && currentDir==A) || (nextX==4 && currentDir==D) || (nextY==0 && currentDir==S) || (nextY==8 && nextX != 0 && nextX != 4 && currentDir==W) || (nextY==9 && currentDir==W)){
//          while(1){
//             readSensor();
//             followLine();
//             
//             if(gs0==1){
//                controlSpeed = 50;
//                tone(buzzer, 2500, 200);
//             }
//             else if(gs1==1 || gs5==1){
//                controlSpeed = 100;
//                break; 
//             }            
//          } 
//       }

   }
   
   else if(s1==0 && s6==0 && led==1){
     //  LED(0,0,0);
   }
  
}



