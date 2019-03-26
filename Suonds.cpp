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
    void playDeath()
    {
         sounds = al_load_sample("morte.wav");
        al_play_sample(sounds, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }
    ~Sounds()
    {
        al_destroy_sample(sounds);
    }
};