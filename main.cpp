#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include "Graphics.cpp"
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
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY* display = al_create_display(l,h);
    must_init(display, "display");
    ALLEGRO_BITMAP* buffer=al_create_bitmap(l,h);
    int windowHeight = al_get_display_height(display);
    int windowWidth = al_get_display_width(display);
    float sx = windowWidth / float(l);
    float sy = windowHeight / float(h);
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

    Graphics GraphicManager(display,buffer,scaleX,scaleY,scaleW,scaleH);
    Player* Play= new Player(GraphicManager.griglia);
    Kong* Wukong = new Kong(GraphicManager.griglia);
    Barrel* Bar=new Barrel(GraphicManager.griglia);
    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    while(1)
    {
        al_wait_for_event(queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if(key[ALLEGRO_KEY_UP])
                    Play->MoveUp();
                if(key[ALLEGRO_KEY_DOWN])
                    Play->MoveDown();
                if(key[ALLEGRO_KEY_LEFT])
                    Play->MoveLeft();
                if(key[ALLEGRO_KEY_RIGHT])
                    Play->MoveRight();
                if(key[ALLEGRO_KEY_SPACE])
                    Play->Jump();
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
            Bar->roll();
            Bar->HandleGravity();
            Play->HandleGravity();
            if (Play->getX()/20==Bar->getX()/20 and Play->getY()/20==Bar->getY()/20)
                done=true;
            GraphicManager.DrawMap();
            GraphicManager.DrawStaticBarrels();
            GraphicManager.DrawKong(Wukong);
            GraphicManager.DrawBarrel(Bar);
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