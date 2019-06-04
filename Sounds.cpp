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
        ALLEGRO_SAMPLE_ID walkingid;        	
        ALLEGRO_SAMPLE_INSTANCE *sampleInstance = NULL;

    public:
    Sounds()
    {
        al_reserve_samples(5);
        newgame = al_load_sample("Assets/Audio/newgame.wav");
        death = al_load_sample("Assets/Audio/morte.wav");
        mammamia = al_load_sample("Assets/Audio/MammaMiaPizzeria.wav");
        walking = al_load_sample("Assets/Audio/walking.wav");
        jump = al_load_sample("Assets/Audio/jump.wav");
        menu= al_load_sample("Assets/Audio/menu.wav");
        sampleInstance = al_create_sample_instance(walking);
	    al_attach_sample_instance_to_mixer(sampleInstance, al_get_default_mixer());
    }

    void startNewGame()
    {
        al_play_sample(newgame, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }

    void playDeath()
    {
        al_play_sample(death, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }

    void playMammaMia()
    {
        al_play_sample(mammamia, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }

    void playWalking()
    {
        if (!al_get_sample_instance_playing(sampleInstance))
         	al_play_sample_instance(sampleInstance);
    }

    void playJump()
    {
        al_play_sample(jump, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }
    void playMenu()
    {
        al_play_sample(menu,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    }
    void stopsounds(){al_stop_samples();}
    ~Sounds()
    {
        al_destroy_sample(newgame);
        al_destroy_sample(death);
        al_destroy_sample(mammamia);
        al_destroy_sample_instance(sampleInstance);
        al_destroy_sample(walking);
        al_destroy_sample(jump);
        al_destroy_sample(menu);
        al_uninstall_audio();
    }

};