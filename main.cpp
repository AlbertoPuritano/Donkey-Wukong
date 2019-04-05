#include "Game.cpp"

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
    Graphics* GraphicManager= new Graphics(display,buffer,scaleX,scaleY,scaleW,scaleH);
    Sounds* SoundManager=new Sounds;
    Game GameManager(GraphicManager,SoundManager);
    

    switch (GameManager.runMenu(timer,queue))
    {
        case 0:
            break;
        case 1:
            al_flush_event_queue(queue);
            GameManager.runGame(timer,queue, 0.5);
            break;
    }

    

    
    
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    delete GraphicManager;
    delete SoundManager;

    return 0;
}