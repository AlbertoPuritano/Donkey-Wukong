#ifndef ENTITIES_H
#define ENTITIES_H
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
    int** grid=NULL;
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
    bool dead;
    bool hammer, hammered;
public:
    Player(int** c);
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Jump();
    void HandleGravity();
    void setDead(bool m);
    bool getDead();
    void setHammer(bool c);
    bool getHammer();
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
    float difficulty;
    int launch;
public:
    Kong(int** c, float d);
    void resetFrame();
    void nextFrame();
    int getLaunch();
    float getDifficulty();
};
#endif