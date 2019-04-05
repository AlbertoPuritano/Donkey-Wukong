#include "Sounds.cpp"
#include "Graphics.cpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <list>
#include <iostream>

class Game
{
private:
    Sounds* SoundManager=NULL;
    Graphics* GraphicManager=NULL;
    
public:
    Game(Graphics* g,Sounds* s):SoundManager(s),GraphicManager(g){}
    
    unsigned runMenu(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue)
    {
        int state=0;
        bool done = false;
        bool redraw = true;
        ALLEGRO_EVENT event;
        al_start_timer(timer);
        while(1)
        {
            al_wait_for_event(queue, &event);
            switch(event.type)
            {
                case ALLEGRO_EVENT_TIMER:
                    redraw = true;
                    break;
                case ALLEGRO_EVENT_KEY_CHAR:
                    if(event.keyboard.keycode==ALLEGRO_KEY_UP and state!=0)
                            state--;
                    if(event.keyboard.keycode==ALLEGRO_KEY_DOWN and state!=3)
                            state++;
                    if (event.keyboard.keycode==ALLEGRO_KEY_ENTER and state==0)
                        return 1;
                    if (event.keyboard.keycode==ALLEGRO_KEY_ENTER and state==3)
                        return 0;
                    if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
                            done = true;
                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    done = true;
                    break;
            }

            if(done)
                break;

            if(redraw && al_is_event_queue_empty(queue))
            {
                GraphicManager->DrawMenu(state);
                al_flip_display();
                redraw=false;
            }
        }
        return 0;
    }
    
    
    void runGame(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, float difficolta)
    {
        Player* Play= new Player(GraphicManager->griglia);
        Kong* Wukong = new Kong(GraphicManager->griglia, difficolta);
        list <Barrel> Barili;
        Barrel Bar(GraphicManager->griglia);
        auto temp=Barili.begin();
        bool done = false;
        bool redraw = true;
        ALLEGRO_EVENT event;

        al_start_timer(timer);
        #define KEY_SEEN     1
        #define KEY_RELEASED 2
        int ciao=0;
        unsigned char key[ALLEGRO_KEY_MAX];
        memset(key, 0, sizeof(key));
        SoundManager->startNewGame();
 //       SoundManager.backGround();
        while(1)
        {
            al_wait_for_event(queue, &event);
            switch(event.type)
            {
                case ALLEGRO_EVENT_TIMER:
                    if(key[ALLEGRO_KEY_UP])
                        {   Play->MoveUp();        if(Play->getLadderstate()) SoundManager->walking();    }
                    if(key[ALLEGRO_KEY_DOWN])
                        {   Play->MoveDown();      if(Play->getLadderstate()) SoundManager->walking();   }
                    if(key[ALLEGRO_KEY_LEFT])
                        {   Play->MoveLeft();       SoundManager->walking();   }
                    if(key[ALLEGRO_KEY_RIGHT])
                        {   Play->MoveRight();      SoundManager->walking();   }
                    if(key[ALLEGRO_KEY_SPACE])
                        {   Play->Jump();           SoundManager->jump();       }
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
                if (Wukong->getLancia() == Wukong->getFrame())
                    Barili.push_back(Bar);
                if (Play->getMorto())
                    ciao++;
                if (ciao==75)
                    done=true;
                for (auto i=Barili.begin();i!=Barili.end();i++)
                {
                    i->roll();
                    i->HandleGravity();
                    if (Play->getX()/20==i->getX()/20 and Play->getY()/20==i->getY()/20)
                    {            
                        SoundManager->playDeath();
                        Play->setMorto();
                    }
                    if (i->getStop())
                    {
                        temp=i;
                        i++;
                        Barili.erase(temp);
                    }
                }
                Play->HandleGravity();
                GraphicManager->DrawMap();
                GraphicManager->DrawStaticBarrels();
                GraphicManager->DrawKong(Wukong);
                for (auto i: Barili)   
                    GraphicManager->DrawBarrel(i);
                GraphicManager->DrawPlayer(Play);
                al_flip_display();

                redraw = false;
            }
        }
        delete Play;  delete Wukong;
    }  
};  