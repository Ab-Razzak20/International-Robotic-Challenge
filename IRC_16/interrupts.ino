void getRPM(){
    c1 = millis();
    rpm = 60000/(4*(c1-c2));
    c2 = millis();

    rotationCount++;

//    if(setRPM < 100){
//        int rpm_percent = rpm*100/maxRPM;
//        int rpm_diff = rpm_percent - setRPM;
//
//        if(abs(rpm_diff) > 5){
//            controlSpeed = setRPM - rpm_diff*4;
//        }
//        else controlSpeed = setRPM;
//
//        if(controlSpeed > 100){
//            controlSpeed = 100;
//        }
//        else if(controlSpeed < 30){
//            controlSpeed = 30;
//        }
//    }
//
//    else if (setRPM == 100 && controlSpeed != 100){
//        controlSpeed = 100;
//    }
//
//    move(move_L, move_R);

    //make it risk free...
    if(rpm < 0 || rpm > 800){
        rpm = 270;
    }

}



