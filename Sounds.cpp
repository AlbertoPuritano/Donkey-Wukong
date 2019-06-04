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
        ALLEGRO_SAMPLE_INSTANCE* walkingInstance;
        ALLEGRO_SAMPLE_INSTANCE* jumpInstance;

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
        walkingInstance = al_create_sample_instance(walking);
        jumpInstance= al_create_sample_instance(jump);
	    al_attach_sample_instance_to_mixer(walkingInstance, al_get_default_mixer());
        al_attach_sample_instance_to_mixer(jumpInstance, al_get_default_mixer());
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
        if (!al_get_sample_instance_playing(walkingInstance))
         	al_play_sample_instance(walkingInstance);
    }

    void playJump()
    {
        if (!al_get_sample_instance_playing(jumpInstance))    
        al_play_sample_instance(jumpInstance);        
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
        al_destroy_sample_instance(walkingInstance);
        al_destroy_sample(walking);
        al_destroy_sample_instance(jumpInstance);
        al_destroy_sample(jump);
        al_destroy_sample(menu);
        al_uninstall_audio();
    }

};