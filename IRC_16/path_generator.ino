void printPos(){
    int i, j;
    Serial.println("ready........");
    
    for(j = maxY; j >= 0; j--){
        for(i=0; i<= maxX; i++){
            Serial.print(workingPos[i][j]);
            Serial.print(" ");
        }
        Serial.print("\n");
    }

    Serial.print(block);
}


void printPath(){
    int i,j;
    
    for(i=0; path[i] != 120; i++){
        Serial.print(path[i]);
        Serial.print(" ");
    }
    
    Serial.println("");
    
}


//void setPos(){
//
//    int i, j;
//
//    for(i=0; i<4; i++){
//        for(j=0; j<8; j++){
//            workingPos[i][j] = 1;
//        }
//    }
//
//    workingPos[0][4] = 0;
//    workingPos[1][4] = 0;
//    workingPos[2][4] = 0;
//    workingPos[3][4] = 0;
//
//    workingPos[0][1] = 0;
//    workingPos[2][1] = 0;
//    workingPos[1][1] = 0;
//
//    target = 22;
//    startPosition=30;
//}





void generatePath(){

    if(startPosition == target){
        path[0] = startPosition;
        path[1] = 120;
        return;
    }

    int i=0, j=0, k=0, temp1=0, length=0, length2=0, length3=0, x=0, y=0, lastStarted=0, breakPoint=0;
    byte pos_temp[10][10];
    byte cal[30][30];

    for(i=0; i<10; i++){
       for(j=0; j<10; j++){
          pos_temp[i][j] = workingPos[i][j];
       }
    }

    i=0;
    j=0;

  //  setPos();


    cal[0][0]= started;
    cal[0][1]= 0;              //number or turns
    cal[0][2]= startPosition;
    cal[0][3]= 120;
    cal[1][0]= notStarted;

    for(lastStarted=0; cal[lastStarted+1][0] == started; lastStarted++){
        // nothing
    }

    while(1){
        
        length = lastStarted + 1;

        cal[length][0] = notStarted;


        //sorting............................
        int temp[30];
        int sort_i, sort_j, sort_k;

        for(sort_k=1; sort_k < lastStarted+1; sort_k++){
            for(sort_i=1; sort_i < lastStarted+1; sort_i++){
                if(cal[sort_i][1] < cal[sort_i-1][1]){
                    for(sort_j=0; sort_j<30; sort_j++){
                        temp[sort_j] = cal[sort_i-1][sort_j];
                    }
                    for(sort_j=0; sort_j<30; sort_j++){
                        cal[sort_i-1][sort_j] = cal[sort_i][sort_j];
                    }
                    for(sort_j=0; sort_j<30; sort_j++){
                        cal[sort_i][sort_j] = temp[sort_j];
                    }
                }
            }
        }

/*
    int ii, jj;
    for(jj=0; cal[jj][0] != 2; jj++){
        printf("%d:\t", jj);
        for(ii=0; cal[jj][ii-1] != 120; ii++){
            printf("%2d ", cal[jj][ii]);
        }
        printf("\n");
    }
    printf("\n");
*/




        for(i=0; i<length; i++){
            if(cal[i][0] == stopped){
                continue;
            }

            for(length2=0; cal[i][length2+1] != 120; length2++){
                // nothing
            }

            x = conX(cal[i][length2]);
            y = conY(cal[i][length2]);

            pos_temp[x][y] = 0;

            k=0;

            if(pos_temp[x][y-1] == 1){
                cal[i][length2+1] = conI(x, y-1);
                cal[i][length2+2] = 120;
                pos_temp[x][y-1] = 0;
                k=1;
            }

            if(pos_temp[x+1][y] == 1){
                if(k==1){
                    lastStarted++;
                    cal[lastStarted][0] = started;

                    for(j=0; j <= length2; j++){
                        cal[lastStarted][j] = cal[i][j];
                    }
                    cal[lastStarted][length2+1] = conI(x+1, y);
                    cal[lastStarted][length2+2] = 120;
                }

                else if(k==0){
                    cal[i][length2+1] = conI(x+1, y);
                    cal[i][length2+2] = 120;
                }
                pos_temp[x+1][y] = 0;
                k=1;
            }

            if(pos_temp[x][y+1] == 1){
                if(k==1){
                    lastStarted++;
                    cal[lastStarted][0] = started;

                    for(j=0; j <= length2; j++){
                        cal[lastStarted][j] = cal[i][j];
                    }
                    cal[lastStarted][length2+1] = conI(x, y+1);
                    cal[lastStarted][length2+2] = 120;
                }

                else if(k==0){
                    cal[i][length2+1] = conI(x, y+1);
                    cal[i][length2+2] = 120;
                }
                pos_temp[x][y+1] = 0;
                k=1;
            }

            if(pos_temp[x-1][y] == 1){
                if(k==1){
                    lastStarted++;
                    cal[lastStarted][0] = started;

                    for(j=0; j <= length2; j++){
                        cal[lastStarted][j] = cal[i][j];
                    }
                    cal[lastStarted][length2+1] = conI(x-1, y);
                    cal[lastStarted][length2+2] = 120;
                }

                else if(k==0){
                    cal[i][length2+1] = conI(x-1, y);
                    cal[i][length2+2] = 120;
                }
                pos_temp[x-1][y] = 0;
                k=1;
            }

            if(k==0){
                cal[i][0] = stopped;
            }




            //TURN COUNTING....................................
            char lastChange, newChange;
            int count = 0, count_i;

            int x1, x2, y1, y2;
            x1 = conX(cal[i][2]);
            y1 = conY(cal[i][2]);
            x2 = conX(cal[i][3]);
            y2 = conY(cal[i][3]);

            if(currentDir == W || currentDir == S){
                lastChange = 'y';
            }
            else if(currentDir == A || currentDir == D){
                lastChange = 'x';
            }
            else lastChange = 'x';

            for(count_i=2; cal[i][count_i+1] != 120; count_i++){
                x1 = conX(cal[i][count_i]);
                y1 = conY(cal[i][count_i]);
                x2 = conX(cal[i][count_i+1]);
                y2 = conY(cal[i][count_i+1]);

                if(x1 == x2 && y1 != y2){
                    newChange = 'y';
                }
                else if(x1 != x2 && y1 == y2){
                    newChange = 'x';
                }

                if(lastChange != newChange){
                    count++;
                    lastChange = newChange;
                }
            }
            cal[i][1] = count;

        }



        for(i=0; i<lastStarted+1; i++){
            for(length3=0; cal[i][length3+1] != 120; length3++){
                // nothing
            }

            if(cal[i][length3] == target){
                breakPoint = 1;
                break;
            }
        }

        if(breakPoint == 1){
            break;
        }


    }

    targetX = conX(target);
    targetY = conY(target);

    for(k=0, j=2; j<=length3; j++, k++){
        path[k] = cal[i][j];
    }
    path[k] = 120;



/*    for(i=0; i<=length3-1; i++){
        printf("%d  ", path[i]);
    }

    printf("\n\nlast = %d\n\n", lastStarted);


    int ii, jj;
    for(jj=0; cal[jj][0] != 2; jj++){
        printf("%d:\t", jj);
        for(ii=0; cal[jj][ii-1] != 120; ii++){
            printf("%2d ", cal[jj][ii]);
        }
        printf("\n");
    }


    printf("\n\n");
    */
}


int conI(int x, int y){
    return x*10+y;
}

int conX(int I){
    return I/10;
}
int conY(int I){
    return I%10;
}


int totalTurn(){
    char lastChange, newChange;
    int count = 0, count_i;

    int x1, x2, y1, y2;
    x1 = conX(path[0]);
    y1 = conY(path[0]);
    x2 = conX(path[1]);
    y2 = conY(path[1]);

    if(currentDir == W || currentDir == S){
        lastChange = 'y';
    }
    else if(currentDir == A || currentDir == D){
        lastChange = 'x';
    }

    for(count_i=0; path[count_i+1] != 120; count_i++){
        x1 = conX(path[count_i]);
        y1 = conY(path[count_i]);
        x2 = conX(path[count_i+1]);
        y2 = conY(path[count_i+1]);
        if(x1 == x2 && y1 != y2){
            newChange = 'y';
        }
        else if(x1 != x2 && y1 == y2){
            newChange = 'x';
        }

        if(lastChange != newChange){
            count++;
            lastChange = newChange;
        }
        //printf("%d ", count_i);
    }

    //printf("\n\ncount = %d\n", count);
    return count;
}


int nextTurn(int index){

    int count=0;
    int x1, x2, y1, y2;
    char initChange, newChange;

    x1 = conX(path[index]);
    y1 = conY(path[index]);
    x2 = conX(path[index+1]);
    y2 = conY(path[index+1]);

    if(x1 == x2 && y1 != y2){
        initChange = 'y';
    }
    else if(x1 != x2 && y1 == y2){
        initChange = 'x';
    }


    while(1){

        x1 = conX(path[index+count]);
        y1 = conY(path[index+count]);
        x2 = conX(path[index+count+1]);
        y2 = conY(path[index+count+1]);


        if(path[index+count+1] == 120){
            newChange = 'z';
        }
        else if(x1 == x2 && y1 != y2){
            newChange = 'y';
        }
        else if(x1 != x2 && y1 == y2){
            newChange = 'x';
        }


        if(initChange != newChange){
            break;
        }

        if(count>10){
            count = 120;
            break;
        }

        count++;
    }

    return count;
}





