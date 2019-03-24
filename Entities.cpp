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
    void resetFrame(){frame=1;}
    void nextFrame(){frame++;}
};


class Player: public Entity
{
public:
    Player(int** c):Entity(520,180,c){}
    void MoveUp()
    {
        if ((x/20)-1<=0)
            return;
        if (griglia[(x/20)-1][y/20]==1)
        {
            x-=10;
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
        if ((x/20)+1<=27 and griglia[(x/20)+1][y/20]==1)
        {
            x+=10;
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
};
