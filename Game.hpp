#include "Sounds.cpp"
#include "Graphics.cpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <ctime>
#include <list>
#include <iostream>

class Game
{
private:
    Sounds* SoundManager;
    Graphics* GraphicManager;
    float difficulty;
    int hTime = 0;
    bool muted;
public:
    Game(Graphics* g,Sounds* s);
    int runMenu(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue);
    
    bool runGame(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue,int& vite,int& livello,int &score); 
    void runOptions(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue);
    void runStatic(ALLEGRO_EVENT_QUEUE* queue,int a);
    void runCut(ALLEGRO_EVENT_QUEUE* queue,ALLEGRO_TIMER* timer,int frame);
};