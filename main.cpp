#include "Game.cpp"
#include <stdio.h>

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

    must_init(al_install_audio(), "sound");
    must_init(al_init_acodec_addon(), "Codec");
     
    must_init(al_init_font_addon(),"font");
    must_init(al_init_ttf_addon(), "ttf");
    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "fonts");
    ALLEGRO_FONT* fontpunteggio=al_load_ttf_font("Assets/Fonts/slkscr.ttf", 30, 0);
    must_init(fontpunteggio,"fontpunteggio");


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
    if (!al_hide_mouse_cursor(display))
        cout<<"couldn't hide mouse cursor";
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    Graphics* GraphicManager= new Graphics(display,buffer,scaleX,scaleY,scaleW,scaleH,font,fontpunteggio);
    Sounds* SoundManager=new Sounds;
    Game GameManager(GraphicManager,SoundManager);
    
    int scelta=-1;
    int vite=3;
    int livello=1;
    int score=0;
    while (scelta!=0)
    {
        al_flush_event_queue(queue);
        scelta=GameManager.runMenu(timer,queue);
        switch (scelta)
        {
            case 0:
                break;
            case 1: 
                al_flush_event_queue(queue);
                vite=3;
                livello=1;
                score=0;
                while (vite!=0)
                {
                    if (GameManager.runGame(timer,queue,vite,livello,score));
                        livello++;
                    if (livello==4)
                        break;
                }
                if (livello==4)
                    GameManager.runStatic(queue,1);
                else
                    GameManager.runStatic(queue,2);
                break;
            case 2:
                al_flush_event_queue(queue);
                GameManager.runOptions(timer,queue);
                break;
            case 3:
                al_flush_event_queue(queue);
                GameManager.runStatic(queue,0);
                break;
        }
    }

    

    
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    delete GraphicManager;
    delete SoundManager;

    return 0;
}