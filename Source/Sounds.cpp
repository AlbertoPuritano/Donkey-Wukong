#include "../Headers/Sounds.hpp"
    Sounds::Sounds()
    {
        al_reserve_samples(10);
        newgame = al_load_sample("../Assets/Audio/newgame.wav");
        death = al_load_sample("../Assets/Audio/morte.wav");
        mammamia = al_load_sample("../Assets/Audio/MammaMiaPizzeria.wav");
        walking = al_load_sample("../Assets/Audio/walking.wav");
        jump = al_load_sample("../Assets/Audio/jump.wav");
        menu= al_load_sample("../Assets/Audio/menu.wav");
        hammer=al_load_sample("../Assets/Audio/hammer.wav");
        walkingInstance = al_create_sample_instance(walking);
        jumpInstance= al_create_sample_instance(jump);
        hammerInstance=al_create_sample_instance(hammer);
        menuInstance=al_create_sample_instance(menu);
	    al_attach_sample_instance_to_mixer(walkingInstance, al_get_default_mixer());
        al_attach_sample_instance_to_mixer(jumpInstance, al_get_default_mixer());
        al_attach_sample_instance_to_mixer(hammerInstance, al_get_default_mixer());
        al_attach_sample_instance_to_mixer(menuInstance,al_get_default_mixer());
    }

    void Sounds::startNewGame()
    {
        al_play_sample(newgame, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }
    void Sounds::playHammer()
    {
        if(al_get_sample_instance_playing(walkingInstance))
                al_stop_sample_instance(walkingInstance);
        if (!al_get_sample_instance_playing(hammerInstance))
         	al_play_sample_instance(hammerInstance);
    }
    void Sounds::playDeath()
    {
        al_play_sample(death, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }

    void Sounds::playMammaMia()
    {
        al_play_sample(mammamia, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }

    void Sounds::playWalking()
    {
        if (!al_get_sample_instance_playing(walkingInstance))
         	al_play_sample_instance(walkingInstance);
    }

    void Sounds::playJump()
    {
     //   if(al_get_sample_instance_playing(walkingInstance))
                {al_stop_sample_instance(walkingInstance);cout << " ho stoppato";}
        if (!al_get_sample_instance_playing(jumpInstance))   
            al_play_sample_instance(jumpInstance);        
    }
    void Sounds::playMenu()
    {
        if (!al_get_sample_instance_playing(menuInstance))   
            al_play_sample_instance(menuInstance);
    }
    void Sounds::stopSamples(){al_stop_samples();}
    void Sounds::stopMenu()
    {
        if (al_get_sample_instance_playing(menuInstance))
            al_stop_sample_instance(menuInstance);
    }
    void Sounds::pauseMenu()
    {
        al_set_sample_instance_playing(menuInstance,false);
    }
    void Sounds::resumeMenu()
    {
        al_set_sample_instance_playing(menuInstance,true);
    }
    Sounds::~Sounds()
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