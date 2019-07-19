#ifndef SOUNDS_H
#define SOUNDS_H
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;
class Sounds
{
    private:
        ALLEGRO_SAMPLE* newgame;
        ALLEGRO_SAMPLE* death;
        ALLEGRO_SAMPLE* mammamia;
        ALLEGRO_SAMPLE* walking;
        ALLEGRO_SAMPLE* jump;
        ALLEGRO_SAMPLE* menu;
        ALLEGRO_SAMPLE* hammer;
        ALLEGRO_SAMPLE_INSTANCE* walkingInstance;
        ALLEGRO_SAMPLE_INSTANCE* jumpInstance;
        ALLEGRO_SAMPLE_INSTANCE* hammerInstance;
        ALLEGRO_SAMPLE_INSTANCE* menuInstance;

    public:
    Sounds();
    void startNewGame();
    void playHammer();
    void playDeath();
    void playMammaMia();
    void playWalking();
    void playJump();
    void playMenu();
    void stopSamples();
    void stopMenu();
    ~Sounds();
};
#endif