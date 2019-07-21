#include <list>
#include <cstdlib>
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
    Entity(int a, int b,int** c);
    int getX();
    int getY();
    int getFrame();
    void setFrame(int a);
    bool isFalling();
    bool getLadderstate();
    directions getDirection();
    bool operator== (Entity* a);
};


class Player: public Entity
{
private:
    int jumpstate;
    bool morto;
    bool martello, hammered;
public:
    Player(int** c);
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Jump();
    void HandleGravity();
    void setMorto(bool m);
    bool getMorto();
    void setMartello(bool c);
    bool getMartello();
    void setHammered(bool h);
    bool getHammered();
    bool getJump();
};


class Barrel:public Entity
{
private:
    bool stop;
    bool jumped;
public:
    Barrel(int** c);
    void roll();
    void HandleGravity();
    bool getStop();
    bool getJumped();
    void setJumped(bool j);
    void nextFrame();
};


class Kong: public Entity
{
    float difficolta;
    int lancia;
public:
    Kong(int** c, float d);
    void resetFrame();
    void nextFrame();
    int getLancia();
    float getDifficolta();
};
