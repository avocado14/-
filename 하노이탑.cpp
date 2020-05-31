#include<bangtal.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>


SceneID scene1;
ObjectID puzzle[7],startbutton, restartbutton;
TimerID timer1;

const char* image[7] = {
    "image/0.png","image/1.png","image/2.png","image/3.png","image/4.png","image/5.png","image/6.png"
};
int position[3] = { 190,440,690 };
int yposition[7] = { 400,350,300,250,200,150,100};
int puzzlex[7] = { 190,190,190,190,190,190,190 };
int puzzley[7]= { 400,350,300,250,200,150,100 };
int exist[7][3] = {
{ 1,0,0 },
{ 1, 0, 0 },
{ 1, 0, 0 },
{ 1, 0, 0 },
{ 1, 0, 0 },
{ 1, 0, 0 },
{ 1, 0, 0 }
};
int howtomove[128][3];
int v = 0;
bool moving;

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y);
    if (shown) {
        showObject(object);
    }
    return(object);
}







void move1(int j, int to, int a) {
    locateObject(puzzle[j], scene1, puzzlex[j], puzzley[j]);
    exist[a][to] = 1;
    
   
}

void move(int from, int to)
{
    
    for (int i = 0; i < 7; i++) {
        if (exist[i][from ] != 0) {
            for (int j = 0; j < 7; j++) {
                if (puzzlex[j] == position[from] && puzzley[j] == yposition[i]) {
                    //j 가 from 가장 위에
                    for (int a = 6;a>=0 ; a--) {
                        if (exist[a][to] == 0) {                           
                            puzzlex[j] = position[to];
                            puzzley[j] = yposition[a];
                            //startTimer(timer1);                            
                            move1(j, to, a);
                            break;
                        }
                    }
                    break;
                }
                else {}
                    //showMessage ("오류");
            }
            exist[i][from ] = 0;
            break;
        }
    }       
}




void check(int to) {
        for (int i = 0; i < 7; i++) {
            if (exist[i][to] == 1) {
                exist[i][to];
                showMessage("끝");
            }

        }
}


void hanoi(int n, int from, int by, int to)
{
   // from = from1, by = by1, to = to1;
    
        if (n == 1) {
            howtomove[v][0] = v;
            howtomove[v][1] = from;
            howtomove[v][2] = to;
            v++;
            //move(from, to);
           //
            //0,1,2       
        }
        else
        {
            hanoi(n - 1, from, to, by);
            //move(from, to);//0,1,2        
            howtomove[v][0] = v;
            howtomove[v][1] = from;
            howtomove[v][2] = to;
            v++;
            hanoi(n - 1, by, from, to);
        }

}



void timerCallback(TimerID timer) {
    if (timer == timer1) {  

        move(howtomove[v][1], howtomove[v][2]);
        v++;
        setTimer(timer1, 0.5f);
        startTimer(timer1);
        //moving = true;
    }
    else {}
}
void startanimation() {
    v = 0;
    startTimer(timer1);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    if (object == startbutton) {
        //startTimer(timer1);
        hanoi(7, 0, 1, 2);
        // moving = false;
    }
    if (object == restartbutton) {
        startanimation();
    }
}

int main() {

    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);

    scene1 = createScene("게임화면", "image/Untitled-1.png");


   startbutton = createObject("image/시작.png", scene1,1000, 500, true);
   restartbutton = createObject("image/시작.png", scene1, 1000, 200, true);
   for (int i = 0; i < 7; i++) {
       puzzle[i] = createObject(image[i], scene1, puzzlex[i],puzzley[i], true);
   }
    

    timer1 = createTimer(1.0f);
    
    startGame(scene1);
   
}

