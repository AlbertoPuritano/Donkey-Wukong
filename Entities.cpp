#include <iostream>
#include <random> 
using namespace std;
class Entity
{
protected:
    int x;
    int y;
    int** griglia=NULL;
    int frame;
    bool falling;
    bool ladderstate;
public:
    Entity(int a, int b,int** c):x(a),y(b),griglia(c),frame(0),falling(false),ladderstate(false){}         //coordinate in pixel dell'entità e puntatore della matrice su cui deve muoversi
    int getX(){return x;}
    int getY(){return y;}
    int getFrame(){return frame;}
    void setFrame(int a){frame=a;}
    bool isFalling() {return falling;}
    bool getLadderstate() {return ladderstate;}
    bool operator== (Entity* a)
    {
        return (a->getX()==x and a->getY()==y);
    }
};


class Player: public Entity
{
private:
    int jumpstate;
public:
    Player(int** c):Entity(520,180,c),jumpstate(0){}
    void MoveUp()
    {
        if((griglia[(x/20)][y/20] == 1 && griglia[(x/20) -1][y/20] == 1) ||(griglia[(x/20)][y/20] == 1 && griglia[(x/20)-1][y/20] == 2)
            || (griglia[x/20][y/20] == 2 && griglia[(x/20) - 1][y/20] == 0)){
        x-=2;
        ladderstate=true;
        if (frame<6 or frame>=7)
            frame=6;
        else
            frame++;
        }

        if((x/20) + 2 <= 27 &&griglia[x/20][y/20] == 0 && griglia[(x/20) + 2][y/20] == 1)
        {
        x-=2;
        ladderstate=true;
        if (frame<6 or frame>=7)
            frame=6;
        else
            frame++;
        }
    }
    void MoveDown()
    {
        if (griglia[x/20][y/20]==1 and griglia[(x/20)+1][y/20]==2)
            ladderstate=false;
        if(griglia[x / 20][x / 20] == 0 && griglia[(x / 20) + 1][y / 20] == 2 && griglia[(x / 20) + 2][y / 20] == 1)
        {x+=2;
        ladderstate=true;   
        if (frame<6 or frame>=7)
            frame=6;
        else
            frame++;        }
        if(griglia[(x / 20) + 1][y/20] == 1)
        {
            x+=2;
        ladderstate=true;   
        if (frame<6 or frame>=7)
            frame=6;
        else
            frame++;        
        }
        
             

    }
    void MoveLeft()
    {
        if (ladderstate)
            return;
        if ((y/20)-1<0 or griglia[x/20][(y/20)-1]==2 and griglia[x/20][(y/20)]==1 or
            griglia[x/20][(y/20) + 1 ] == 2 or griglia[x/20][(y/20) - 1] == 2 )
            return;
            
        if (falling or jumpstate>0)
            y-=3;
        else
            y-=4;
        if (ladderstate and griglia[x/20][(y/20)-1]==0)
            ladderstate=false;
        if (jumpstate==0)
        {
            if (frame<3 or frame>=5) // <3
                frame=3;
            else
                frame++;
        }
        else
            frame=9;
    }
    void MoveRight() 
    {
        if (ladderstate)
            return;
        if ((y/20)+1>24 or griglia[x/20][(y/20)+1]==2 and griglia[x/20][(y/20)]==1)
            return;
        if (falling or jumpstate>0)
            y+=3;
        else
            y+=4;
        if (ladderstate and griglia[x/20][(y/20)+1]==0)
            ladderstate=false;
        if (jumpstate==0)
        {
            if (frame>=2)
                frame=0;
            else
                frame++;
        }
        else
            frame=8;
    } 
    void Jump()
    {
        if (falling or jumpstate>0 or ladderstate)
            return;
        jumpstate=1;
    }
    void HandleGravity()
    {
       // if (griglia[(x/20)+1][y/20]==2)     
       //     ladderstate=false;
        if (griglia[(x/20)+1][y/20]==0 and jumpstate==0) //se sotto ha il vuoto
            falling=true;
        if (falling and jumpstate==0)
        {
            ladderstate=false;
            if (griglia[(x/20)+1][y/20]==2)
            {
                falling=false;
                return;
            }
            x+=4;
        }
        if (!falling and jumpstate>0)
        {
            x-=3;
            jumpstate++;
            if (jumpstate==12)
            {
                jumpstate=0;
                falling=true;
                return;
            }
        }
    }


};


class Barrel:public Entity
{
private:
    bool dx;
    bool stop;
public:
    Barrel(int** c):Entity(120,200,c),dx(true),stop(false){};
    void roll()
    {
        if (falling or stop)
            return;
        if (dx)
            y+=5;
        else
            y-=5;
    }
    void HandleGravity()
    {
        if (x/20==26 and y/20==2)
            stop=true;
        if (falling)
        {
            x+=4;
            if (griglia[(x/20)+1][y/20]==2)
                falling=false;
            return; 
        }
        else if (griglia[(x/20)+1][y/20]==0)
        {
            falling=true;
            if (dx)
                dx=false;
            else
                dx=true;
            return; 
        }   
     //   random_device rd;
     //   mt19937 mt(rd());
     //   uniform_real_distribution<double> dist(1.0, 100.0);
     //   int a=dist(mt);
        srand(time(0));
        int a=rand()%100;
        if ((x/20)+2<=27 and griglia[(x/20)+2][y/20]==1 and a>=75)
        {
            x+=16;
            falling=true;
            if (dx)
                dx=false;
            else
                dx=true;
        }
    }
};


class Kong: public Entity
{
public:
    Kong(int** c):Entity(80,60,c){};
    void resetFrame(){frame=1;}
    void nextFrame(){frame++;}
};
