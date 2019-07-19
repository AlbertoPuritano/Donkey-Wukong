#include "../Headers/Entities.hpp"

    Entity::Entity(int a, int b,int** c):x(a),y(b),grid(c),frame(0),falling(false),ladderstate(false), direction(RIGHT){}         //coordinate in pixel dell'entità e puntatore della matrice su cui deve muoversi
    int Entity::getX(){return x;}
    int Entity::getY(){return y;}
    int Entity::getFrame(){return frame;}
    void Entity::setFrame(int a){frame=a;}
    bool Entity::isFalling() {return falling;}
    bool Entity::getLadderstate() {return ladderstate;}
    directions Entity::getDirection(){return direction;}
    bool Entity::operator== (Entity* a)
    {
        return (a->getX()==x and a->getY()==y);
    }


    Player::Player(int** c):Entity(520,180,c),jumpstate(0), dead(false), hammer(false), hammered(false){}
    void Player::MoveUp()
    {      
        if (dead or falling or jumpstate>0 or hammer or x-1<0)
            return;
        if(grid[(x/20)][y/20]==1 or grid[x/20][y/20]==2 and grid[(x/20)-1][y/20]==0 or ladderstate)
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
    void Player::MoveDown()
    {        
        if (dead or falling or jumpstate>0 or hammer)
            return;
        if (grid[x/20][y/20]==1 and grid[(x/20)+1][y/20]==2)
            ladderstate=false;
        if(grid[x/20][x/20]==0 and grid[(x/20)+1][y/20]==2 and grid[(x/20)+2][y/20]==1 and grid[(x/20)+3][y/20]==1 or ladderstate)
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
    void Player::MoveLeft()
    {
        if (dead or hammered)
            return;
        if (falling and grid[(x/20)+1][y/20]==0 and grid[(x/20)+2][y/20]==0 and grid[(x/20)+3][y/20]==0) //per evitare che
            return;                                                                                               //si muova troppo        
        if (ladderstate or (y/20)-1<0 or grid[x/20][(y/20)-1]==2)                                              //durante la caduta   
            return;
        direction = LEFT;
            y-=3;
        if (ladderstate and grid[x/20][(y/20)-1]==0)
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
            else if(hammer)
            {
                frame = 16;
                return;
            }
            else
                frame=38;
        }
        else if(hammer)
        {
            frame = 16;
            return;
        }
        else
            frame=40;
    }
    void Player::MoveRight() 
    {
        if(dead or hammered)
            return;
        if (falling and grid[(x/20)-1][y/20]==0 and grid[(x/20)-2][y/20]==0 and grid[(x/20)-3][y/20]==0) //per evitare che
            return;                                                                                               //si muova troppo         
        if (ladderstate or (y/20)+1>lMat or grid[x/20][(y/20)+1]==2)                                             //durante la caduta
            return;
        if (ladderstate and grid[x/20][(y/20)+1]==0)
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
            else if(hammer)
                frame = 0;
            else
                frame=37;
        }
        else if(hammer)
            frame = 0;
        else
            frame=39;
    }
    void Player::Jump()
    {
        if(dead or hammer)
            return;
        if (falling or jumpstate>0 or ladderstate)
            return;
        jumpstate=1;
    }
    void Player::HandleGravity()
    {  
        if (falling and jumpstate==0)
        {
            ladderstate=false;
            if (grid[(x/20)+1][y/20]==2 or grid[(x/20)+1][(y/20)+1]==2 and grid[x/20][(y/20)+1]==0)
            {
                falling=false;
                return;
            }
            x+=4;
        }
        if (!falling and jumpstate>0)
        {
            if (grid[x/20][y/20]!=2)
                x-=3;
            jumpstate++;
            if (jumpstate==11)
            {
                jumpstate=0;
                falling=true;
                return;
            }
        }
        /*if (grid[x/20][y/20]==2 and jumpstate>0 and grid[(x/20)+1][y/20]==0)
        {    falling=true; x+=9; jumpstate=0;}   //se rimane bloccato sul blocco*/
        if (grid[(x/20)+1][((y+19)/20)]==0 and jumpstate==0 and direction == RIGHT) //se sotto ha il vuoto
            falling=true;
        else if (grid[(x/20)+1][(y/20)+1]==0 and jumpstate==0 and direction == LEFT)
            falling=true;
    }

    void Player::setDead(bool m){dead = m;}
    bool Player::getDead(){return dead;}
    void Player::setHammer(bool c){hammer = c;}
    bool Player::getHammer(){return hammer;}
    void Player::setHammered(bool h){hammered = h;}
    bool Player::getHammered(){return hammered;}
    bool Player::getJump(){return jumpstate>0;}





    Barrel::Barrel(int** c):Entity(120,110,c),stop(false),jumped(false){};
    void Barrel::roll()
    {
        if (falling or stop)
            return;
        if (direction==RIGHT)
        {    
            y+=5;
            if ((y/20)+1>lMat or grid[x/20][(y+20)/20]==2)
                direction=LEFT;
        }
        else
        {
            y-=5;
            if ((y/20)-1<0 or grid[x/20][(y-20)/20]==2)
                direction=RIGHT;
        }
    }
    void Barrel::HandleGravity()
    {
        if (x/20==26 and y/20==2)
            stop=true;
        if (falling)
        {
            x+=4;
            if (grid[(x/20)+1][y/20]==2)
            {
                falling=false;
            }
            return; 
        }
        else if (grid[(x/20)+1][y/20]==0)
        {
            falling=true;
            if (direction==RIGHT)
                direction=LEFT;
            else
            {    
                direction=RIGHT; 
                y-=13;
            }
            return;
        }           
        if ((x/20)+2<=hMat and grid[(x/20)+2][y/20]==1)
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
    bool Barrel::getStop(){return stop;}
    bool Barrel::getJumped(){return jumped;}
    void Barrel::setJumped(bool j){jumped = j;}
    void Barrel::nextFrame(){frame++;}


    Kong::Kong(int** c, float d):Entity(80,60,c), difficulty(d), launch(81*d){};
    void Kong::resetFrame(){frame=1;}
    void Kong::nextFrame()
    {
        if (frame<difficulty*100)
            frame++;
        else
            frame = 1;        
    }
    int Kong::getLaunch(){return launch;}
    float Kong::getDifficulty(){return difficulty;}