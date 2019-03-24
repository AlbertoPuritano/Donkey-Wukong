class Entity
{
protected:
    int x;
    int y;
    int** griglia=NULL;
    int frame;
public:
    Entity(int a, int b,int** c):x(a),y(b),griglia(c),frame(1){}         //coordinate in pixel dell'entità e puntatore della matrice su cui deve muoversi
    int getX(){return x;}
    int getY(){return y;}
    int getFrame(){return frame;}
    void setFrame(int a){frame=a;}
};


class Player: public Entity
{
private:
    int falling;
public:
    Player(int** c):Entity(520,180,c),falling(false){}
    void MoveUp()
    {
        if (falling>0)
            return;
        if ((x/20)-1>=0 and griglia[(x/20)-1][y/20]==1)
        {
            x-=5;
            return;
        }
        else if (griglia[(x/20)-1][y/20]==2)
        {
            x/=20;
            x-=2;
            x*=20;
        }
    }
    void MoveDown()
    {
        if (falling>0)
            return;
        if ((x/20)+1<=27 and griglia[(x/20)+1][y/20]==1)
        {
            x+=5;
            return;
        }
        else if ((x/20)+2<=27 and griglia[(x/20)+1][y/20]==2 and griglia[(x/20)+2][y/20]==1)
        {
            x/=20;
            x+=2;
            x*=20;
        }
    }
    void MoveLeft()
    {
        if ((x/20)+1<=27 and (y/20)-1>=0 and griglia [(x/20)][(y/20)-1]!=2 and griglia[(x/20)+1][y/20]!=1 and griglia[(x/20)+1][(y/20)-1]==2)
            y-=5;
    }
    void MoveRight()
    {
        if ((x/20)+1<=27 and (y/20)+1 <=24 and griglia [(x/20)][(y/20)+1]!= 2 and griglia[(x/20)+1][y/20]!=1 and griglia[(x/20)+1][(y/20)+1]==2)
            y+=5;
    }
    int isFalling(){return falling;}
    void Jump()
    {
        if (griglia[x/20][y/20]!= 1 and falling==0)
            falling=1;
    }
    void HandleFall()
    {
        switch(falling)
        {
            case 0:
                return;
            case 1:
                x-=8;
                falling++;
                break;
            case 2:
                x-=8;
                falling++;
                break;
            case 3:
                x-=5;
                falling++;
                break;
            case 4:
                x-=5;
                falling++;
                break;
            case 5:
                x+=5;
                falling++;
                break;
            case 6:
                x+=5;
                falling++;
                break;
            case 7:
                x+=8;
                falling++;
                break;
            case 8:
                x+=8;
                falling++;
                break;
            case 9:
                falling=0;
                return;
        }
    }

};


class Barrel:public Entity
{
public:
    Barrel(int** c):Entity(40,80,c){};
};


class Kong: public Entity
{
public:
    Kong(int** c):Entity(80,60,c){};
    void resetFrame(){frame=1;}
    void nextFrame(){frame++;}
};
