#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;
class Sounds
{
    private:
        ALLEGRO_SAMPLE *sounds;
    
    public:
    Sounds(): sounds(NULL){    /*must_init(sounds, "sounds"); */ };

    void startNewGame()
    {
        sounds = al_load_sample("newgame.wav");
        al_play_sample(sounds, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }

    void playDeath()
    {
        al_destroy_sample(sounds);
         sounds = al_load_sample("morte.wav");
        al_play_sample(sounds, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }

    void backGround()
    {
        sounds = al_load_sample("bacmusic.wav");
        al_play_sample(sounds, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    }

    void walking()
    {
        sounds = al_load_sample("walking.wav");
        al_play_sample(sounds, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }

    void jump()
    {
        sounds = al_load_sample("jump.wav");
        al_play_sample(sounds, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }

    ~Sounds()
    {
        al_destroy_sample(sounds);
    }
};