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
    bool morto;
public:
    Player(int** c):Entity(520,180,c),jumpstate(0), morto(false){}
    void MoveUp()
    {
        if(morto)
            return;       
        if (falling or jumpstate>0)
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
        if(morto)
            return;        
        if (falling or jumpstate>0)
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
        if(morto)
            return;
        if (falling and griglia[(x/20)+1][y/20]==0 and griglia[(x/20)+2][y/20]==0 and griglia[(x/20)+3][y/20]==0) //per evitare che
            return;                                                                                               //si muova troppo        
        if (ladderstate or (y/20)-1<0 or griglia[x/20][(y/20)-1]==2)                                              //durante la caduta   
            return;
            
            y-=3;
        if (ladderstate and griglia[x/20][(y/20)-1]==0)
            ladderstate=false;
        
        
        //ANIMAZIONI
        if (!falling)
        {
            if (jumpstate==0)
            {
                if (frame<15 or frame>29) // <3
                    frame=18;
                else
                    frame++;
            }
            else
                frame=38;
        }
        else
            frame=40;
    }
    void MoveRight() 
    {
        if(morto)
            return;
        if (falling and griglia[(x/20)-1][y/20]==0 and griglia[(x/20)-2][y/20]==0 and griglia[(x/20)-3][y/20]==0) //per evitare che
            return;                                                                                               //si muova troppo         
        if (ladderstate or (y/20)+1>24 or griglia[x/20][(y/20)+1]==2)                                             //durante la caduta
            return;
        if (ladderstate and griglia[x/20][(y/20)+1]==0)
            ladderstate=false;
        y+=3;
        
        
        //ANIMAZIONI
        if (!falling)
        {
            if (jumpstate==0)
            {
                if (frame>=15)
                    frame=0;
                else
                    frame++;
            }
            else
                frame=37;
        }
        else
            frame=39;
    }
    void Jump()
    {
        if(morto)
            return;
        if (falling or jumpstate>0 or ladderstate)
            return;
        jumpstate=1;
    }
    void HandleGravity()
    {
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
            x-=4;
            jumpstate++;
            if (jumpstate==8)
            {
                jumpstate=0;
                falling=true;
                return;
            }
        }
    }

    void setMorto(){morto = true;}
    bool getMorto(){return morto;}


};


class Barrel:public Entity
{
private:
    bool dx;
    bool stop;
public:
    Barrel(int** c):Entity(120,110,c),dx(true),stop(false){};
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
        if ((x/20)+2<=27 and griglia[(x/20)+2][y/20]==1)
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
                if (dx)
                    dx=false;
                else
                    dx=true;
            }
        }
    }
    bool getStop(){return stop;}
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
