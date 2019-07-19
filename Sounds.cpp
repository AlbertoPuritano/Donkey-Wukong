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
    Sounds()
    {
        al_reserve_samples(10);
        newgame = al_load_sample("Assets/Audio/newgame.wav");
        death = al_load_sample("Assets/Audio/morte.wav");
        mammamia = al_load_sample("Assets/Audio/MammaMiaPizzeria.wav");
        walking = al_load_sample("Assets/Audio/walking.wav");
        jump = al_load_sample("Assets/Audio/jump.wav");
        menu= al_load_sample("Assets/Audio/menu.wav");
        hammer=al_load_sample("Assets/Audio/hammer.wav");
        walkingInstance = al_create_sample_instance(walking);
        jumpInstance= al_create_sample_instance(jump);
        hammerInstance=al_create_sample_instance(hammer);
        menuInstance=al_create_sample_instance(menu);
	    al_attach_sample_instance_to_mixer(walkingInstance, al_get_default_mixer());
        al_attach_sample_instance_to_mixer(jumpInstance, al_get_default_mixer());
        al_attach_sample_instance_to_mixer(hammerInstance, al_get_default_mixer());
        al_attach_sample_instance_to_mixer(menuInstance,al_get_default_mixer());
    }

    void startNewGame()
    {
        al_play_sample(newgame, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }
    void playHammer()
    {
        if (!al_get_sample_instance_playing(hammerInstance))
         	al_play_sample_instance(hammerInstance);
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
        if (!al_get_sample_instance_playing(menuInstance))   
            al_play_sample_instance(menuInstance);
    }
    void stopSamples(){al_stop_samples();}
    void stopMenu()
    {
        if (al_get_sample_instance_playing(menuInstance))
            al_stop_sample_instance(menuInstance);
    }
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
        al_destroy_sample_instance(hammerInstance);
        al_destroy_sample(hammer);
        al_uninstall_audio();
    }

};