#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include "Graphics.cpp"
#include "Sounds.cpp"
#include <list>
using namespace std;

void must_init(bool test, const char *description)
{
    if(test) 
        return;

    cout<<"coudlnt initialize"<<description;
    exit(1);
}


int main()
{
    srand(time(0));
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    //SoundManager

    must_init(al_install_audio(), "sound");
    must_init(al_init_acodec_addon(), "Codec");
    must_init(al_reserve_samples(1),"Sample");
    Sounds SoundManager;   

    
   
    

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_BITMAP* buffer=al_create_bitmap(l,h);
    ALLEGRO_DISPLAY* display = al_create_display(l,h);
    must_init(display, "display");
    int windowHeight = al_get_display_height(display);
    int windowWidth = al_get_display_width(display);
    float sx = windowWidth / float(h);
    float sy = windowHeight / float(l);
    int scale = min(sx, sy);
    int scaleW = l * scale;
    int scaleH = h * scale;
    int scaleX = (windowWidth - scaleW) / 2;
    int scaleY = (windowHeight - scaleH) / 2;
    must_init(al_init_image_addon(), "image addon");
    must_init(buffer, "buffer");
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0,0,0));
   
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
 //   cout<<sx<<" "<<sy<<" "<<scaleW<<" "<<scaleH<<" "<<scaleX<<" "<<scaleY<<endl;
    Graphics GraphicManager(display,buffer,scaleX,scaleY,scaleW,scaleH);
    Player* Play= new Player(GraphicManager.griglia);
    Kong* Wukong = new Kong(GraphicManager.griglia);
    list <Barrel> Barili;
    Barrel Bar(GraphicManager.griglia);
    auto temp=Barili.begin();
    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    #define KEY_SEEN     1
    #define KEY_RELEASED 2
    int ciao=0;
    bool porcodio = false;
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    SoundManager.startNewGame();
 //   SoundManager.backGround();
    while(1)
    {
        al_wait_for_event(queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if(key[ALLEGRO_KEY_UP])
                    {   Play->MoveUp();        if(Play->getLadderstate()) SoundManager.walking();    }
                if(key[ALLEGRO_KEY_DOWN])
                    {   Play->MoveDown();      if(Play->getLadderstate()) SoundManager.walking();   }
                if(key[ALLEGRO_KEY_LEFT])
                    {   Play->MoveLeft();       SoundManager.walking();   }
                if(key[ALLEGRO_KEY_RIGHT])
                    {   Play->MoveRight();      SoundManager.walking();   }
                if(key[ALLEGRO_KEY_SPACE])
                    {   Play->Jump();           SoundManager.jump();       }
                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
                al_start_timer(timer);
                #define KEY_SEEN     1
                #define KEY_RELEASED 2
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            if (Wukong->getFrame()==81)
                Barili.push_back(Bar);
            if (porcodio)
            ciao++;
            if (ciao==75)
                done=true;
            for (auto i=Barili.begin();i!=Barili.end();i++)
            {
                i->roll();
                i->HandleGravity();
                if (Play->getX()/20==i->getX()/20 and Play->getY()/20==i->getY()/20)
                {
                    SoundManager.playDeath();
                    porcodio=true;
                }
                if (i->getStop())
                {
                    temp=i;
                    i++;
                    Barili.erase(temp);
                }
            }
            Play->HandleGravity();
            GraphicManager.DrawMap();
            GraphicManager.DrawStaticBarrels();
            GraphicManager.DrawKong(Wukong);
            for (auto i: Barili)   
                GraphicManager.DrawBarrel(i);
            GraphicManager.DrawPlayer(Play);
            al_flip_display();

            redraw = false;
        }
    }
    delete Play;  delete Wukong;
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);


    return 0;
}