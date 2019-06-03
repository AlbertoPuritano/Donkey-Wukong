#include <list>
const int h=560;
const int l=500;
const int hMat=560/20-1;
const int lMat=500/20-1;
//le X sono le Y. CAMBIALE!
enum directions { RIGHT = 0, LEFT};

class Entity
{
protected:
    int x;
    int y;
    int** griglia=NULL;
    int frame;
    bool falling;
    bool ladderstate;
    directions direction;
public:
    Entity(int a, int b,int** c):x(a),y(b),griglia(c),frame(0),falling(false),ladderstate(false), direction(RIGHT){}         //coordinate in pixel dell'entità e puntatore della matrice su cui deve muoversi
    int getX(){return x;}
    int getY(){return y;}
    int getFrame(){return frame;}
    void setFrame(int a){frame=a;}
    bool isFalling() {return falling;}
    bool getLadderstate() {return ladderstate;}
    directions getDirection(){return direction;}
    bool operator== (Entity* a)
    {
        return (a->getX()==x and a->getY()==y);
    }
};


class Player: public Entity
{
private:
    int jumpstate;
    bool morto;
    bool martello, hammered;
public:
    Player(int** c):Entity(520,180,c),jumpstate(0), morto(false), martello(false), hammered(false){}
    void MoveUp()
    {      
        if (morto or falling or jumpstate>0 or martello)
            return;
        if(griglia[(x/20)][y/20]==1 or griglia[x/20][y/20]==2 and griglia[(x/20)-1][y/20]==0 or ladderstate)
        {
            if (!ladderstate)
            {
                ladderstate=true;
                x/=20;
                y/=20;
                x*=20;
                y*=20;
                direction=RIGHT;
            }
            x-=2;
            
            //ANIMAZIONI
            if (frame<30 or frame>35)
                frame=31;
            else
                frame++;
        }
    }
    void MoveDown()
    {        
        if (morto or falling or jumpstate>0 or martello)
            return;
        if (griglia[x/20][y/20]==1 and griglia[(x/20)+1][y/20]==2)
            ladderstate=false;
        if(griglia[x/20][x/20]==0 and griglia[(x/20)+1][y/20]==2 and griglia[(x/20)+2][y/20]==1 and griglia[(x/20)+3][y/20]==1 or ladderstate)
        {
            if (!ladderstate)
            {
                ladderstate=true;
                x/=20;
                y/=20;
                x*=20;
                y*=20;
            }
            x+=2;
           
            
            //ANIMAZIONI
            if (frame<30 or frame>35)
                frame=31;
            else
                frame++;        
        }                     
    }
    void MoveLeft()
    {
        if (morto or hammered)
            return;
        if (falling and griglia[(x/20)+1][y/20]==0 and griglia[(x/20)+2][y/20]==0 and griglia[(x/20)+3][y/20]==0) //per evitare che
            return;                                                                                               //si muova troppo        
        if (ladderstate or (y/20)-1<0 or griglia[x/20][(y/20)-1]==2)                                              //durante la caduta   
            return;
        direction = LEFT;
            y-=3;
        if (ladderstate and griglia[x/20][(y/20)-1]==0)
            ladderstate=false;
        
        
        //ANIMAZIONI
        if (!falling)
        {
            if (jumpstate==0)
            {
                if (frame>29)
                    frame=21;
                else if (frame<15)
                    frame=16;
                else
                    frame++;
            }
            else if(martello)
            {
                frame = 16;
                return;
            }
            else
                frame=38;
        }
        else if(martello)
        {
            frame = 16;
            return;
        }
        else
            frame=40;
    }
    void MoveRight() 
    {
        if(morto or hammered)
            return;
        if (falling and griglia[(x/20)-1][y/20]==0 and griglia[(x/20)-2][y/20]==0 and griglia[(x/20)-3][y/20]==0) //per evitare che
            return;                                                                                               //si muova troppo         
        if (ladderstate or (y/20)+1>lMat or griglia[x/20][(y/20)+1]==2)                                             //durante la caduta
            return;
        if (ladderstate and griglia[x/20][(y/20)+1]==0)
            ladderstate=false;
        direction = RIGHT;
        y+=3;
        
        
        //ANIMAZIONI
        if (!falling)
        {
            if (jumpstate==0)
            {
                if (frame==15)
                    frame=6;
                else if (frame>15)
                    frame=0;
                else
                    frame++;
            }
            else if(martello)
                frame = 0;
            else
                frame=37;
        }
        else if(martello)
            frame = 0;
        else
            frame=39;
    }
    void Jump()
    {
        if(morto || martello)
            return;
        if (falling or jumpstate>0 or ladderstate)
            return;
        jumpstate=1;
    }
    void HandleGravity()
    {  
        if (falling and jumpstate==0)
        {
            ladderstate=false;
            if (griglia[(x/20)+1][y/20]==2 or griglia[(x/20)+1][(y/20)+1]==2)
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
            if (jumpstate==11)
            {
                jumpstate=0;
                falling=true;
                return;
            }
        }
        if (griglia[(x/20)+1][((y+19)/20)]==0 and jumpstate==0 and direction == RIGHT) //se sotto ha il vuoto
            falling=true;
        else if (griglia[(x/20)+1][(y/20)+1]==0 and jumpstate==0 and direction == LEFT)
            falling=true;
    }

    void setMorto(bool m){morto = m;}
    bool getMorto(){return morto;}
    void setMartello(bool c){martello = c;}
    bool getMartello(){return martello;}
    void setHammered(bool h){hammered = h;}
    bool getHammered(){return hammered;}
    bool getJump(){return jumpstate>0;}


};


class Barrel:public Entity
{
private:
    bool stop;
    bool jumped;
public:
    Barrel(int** c):Entity(120,110,c),stop(false),jumped(false){};
    void roll()
    {
        if (falling or stop)
            return;
        if (direction==RIGHT)
        {    
            y+=5;
            if ((y/20)+1>lMat or griglia[x/20][(y+20)/20]==2)
                direction=LEFT;
        }
        else
        {
            y-=5;
            if ((y/20)-1<0 or griglia[x/20][(y-20)/20]==2)
                direction=RIGHT;
        }
    }
    void HandleGravity()
    {
        if (x/20==26 and y/20==2)
            stop=true;
        if (falling)
        {
            x+=4;
            if (griglia[(x/20)+1][y/20]==2)
            {
                falling=false;
            }
            return; 
        }
        else if (griglia[(x/20)+1][y/20]==0)
        {
            falling=true;
            if (direction==RIGHT)
                direction=LEFT;
            else
            {    direction=RIGHT; y-=13;}
            return;
        }           
        if ((x/20)+2<=hMat and griglia[(x/20)+2][y/20]==1)
        {
            int a=rand()%100;            
            if (a>=75)
            {
                x/=20;
                x*=20;
                y/=20;
                y*=20;
                x+=16;
                falling=true;
                if (direction==RIGHT)
                    direction=LEFT;
                else
                    direction=RIGHT;
            }
        }
    }
    bool getStop(){return stop;}
    bool getJumped(){return jumped;}
    void setJumped(bool j){jumped = j;}
    void nextFrame(){frame++;}
};


class Kong: public Entity
{
    float difficolta;
    int lancia;
public:
    Kong(int** c, float d):Entity(80,60,c), difficolta(d), lancia(81*d){};
    void resetFrame(){frame=1;}
    void nextFrame()
    {
        if (frame<difficolta*100)
            frame++;
        else
            frame = 1;        
    }
    int getLancia(){return lancia;}
    float getDifficolta(){return difficolta;}

};
