#include "Sounds.cpp"
#include "Graphics.cpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <ctime>
#include <list>
#include <iostream>

class Game
{
private:
    Sounds* SoundManager=NULL;
    Graphics* GraphicManager=NULL;
    float difficulty;
public:
    Game(Graphics* g,Sounds* s):SoundManager(s),GraphicManager(g),difficulty(1.0){}
    
    int runMenu(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue)
    {        
        SoundManager->stopsounds();
        SoundManager->playMenu();
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
                    if (event.keyboard.keycode==ALLEGRO_KEY_ENTER and state==1)
                        return 2;
                    if (event.keyboard.keycode==ALLEGRO_KEY_ENTER and state==2)
                        return 3;
                    if (event.keyboard.keycode==ALLEGRO_KEY_ENTER and state==3)
                        done=true;
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
        SoundManager->stopsounds();
        return 0;
    }
    
    
    bool runGame(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue,int& vite,int& livello)
    {
        GraphicManager->assegnaGriglia(livello);
        GraphicManager->DrawHammer();
        bool complete=false;
        unsigned hammerTime = 0;
        srand(time(0));
        SoundManager->stopsounds();
        SoundManager->startNewGame();
        list <Barrel> Barili;
        Barrel Bar(GraphicManager->griglia);
        while (vite!=0)
        {
            hammerTime=0;
            Player* Play= new Player(GraphicManager->griglia);
            Kong* Wukong = new Kong(GraphicManager->griglia, difficulty);
            Entity* Peach= new Entity(60,220,GraphicManager->griglia);
            auto temp=Barili.begin();
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
                        {   
                           Play->MoveUp();
                        }
                        if(key[ALLEGRO_KEY_DOWN])
                        {   
                            Play->MoveDown();         
                        }
                        if(key[ALLEGRO_KEY_LEFT])
                        {   
                            Play->MoveLeft();      
                            SoundManager->playWalking();  
                        }
                        if(key[ALLEGRO_KEY_RIGHT])
                        {   
                            Play->MoveRight();      
                            SoundManager->playWalking();
                        }
                        if(key[ALLEGRO_KEY_SPACE])
                        {   
                            Play->Jump();           
                            SoundManager->playJump();       
                        }
                        if(key[ALLEGRO_KEY_ESCAPE])
                        {
                            done = true;                    
                            vite=1;
                        }
                        if (key[ALLEGRO_KEY_ENTER])
                        {
                            complete=true;          //LEVEL SKIPPER CHEAT
                            done=true;
                        }
                        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                            key[i] &= KEY_SEEN;
                        
                        Play->HandleGravity(); 
                        if(Play -> getX()/20 == 21 && Play -> getY()/20 == 17 && Play->getMartello()==false && hammerTime == 0)//prende il martello.
                            Play -> setMartello(true);    
                        

                     /*   if (Play->getFrame()>=0 and Play->getFrame()<=15 && Play->getMartello())
                            for(auto i = Barili.begin(); i != Barili.end(); i++)
                                if(Play->getX()/20==i->getX()/20 and (Play->getY()/20)-1==i->getY()/20)
                                    {//mario verso sx
                                        GraphicManager->DeleteBarrel(i->getX()/20, i->getY()/20);
                                        temp=i;
                                        i++;
                                        Barili.erase(temp); 
                                    }

                        else if (Play->getFrame()>=16 and Play->getFrame()<=30 && Play->getMartello())
                            for(auto i = Barili.begin(); i != Barili.end(); i++)
                                if(Play->getX()/20==i->getX()/20 and (Play->getY()/20)+1==i->getY()/20)
                                    {
                                        GraphicManager->DeleteBarrel(i->getX()/20, i->getY()/20);
                                        temp=i;
                                        i++;
                                        Barili.erase(temp);
                                    }*/
                      /*  if(Play->getMartello())
                            hammerTime++;*/
                        if(hammerTime > 200 && Play->getMartello())
                            Play->setMartello(false);    
                        if (Wukong->getLancia() == Wukong->getFrame())
                            Barili.push_back(Bar);
                        for (auto i=Barili.begin();i!=Barili.end();i++)
                        {
                            if (i->getStop() 
                            or 
                            Play->getMartello() and Play->getFrame()>=15 and Play->getFrame()<=30 and (Play->getY()/20)-1==i->getY()/20 and Play->getX()/20==i->getX()/20
                            or
                            Play->getMartello() and Play->getFrame()<15 and (Play->getY()/20)+1==i->getY()/20 and Play->getX()/20==i->getX()/20)
                            {
                                Play->setHammered(true);
                                temp=i;
                                i++;
                                Barili.erase(temp);
                                
                            
                            }
                            
                            i->roll();
                            i->HandleGravity();
                            if (Play->getX()/20==i->getX()/20 and Play->getY()/20==i->getY()/20)
                            {            
                                SoundManager->stopsounds();
                                SoundManager->playDeath();
                                Play->setMorto(true);
                                al_rest(3.2);
                                done=true;
                            }
                        }
                        if (Play->getX()/20==Peach->getX()/20 and Play->getY()/20==Peach->getY()/20)
                        {
                            complete=true;
                            done=true;
                        }

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
                        vite=1;
                        break;
            
                }

                if(done)
                    break;

                if(redraw && al_is_event_queue_empty(queue))
                {
                    GraphicManager->DrawMap();
                    GraphicManager->DrawPeach(Peach);
                    GraphicManager->DrawStaticBarrels();
                    GraphicManager->DrawKong(Wukong);
                    GraphicManager->DrawPlayer(Play);                    
                    for (auto i: Barili)   
                        GraphicManager->DrawBarrel(i);
                    al_flip_display();
                    redraw = false;
                }
         Play->setHammered(false);       
            }
            vite--;
            delete Play;    delete Wukong;    delete Peach;   Barili.clear();
            if (complete)
                break;
        }
        SoundManager->stopsounds();
        return complete;
    }   
    void runOptions(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue)
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
                    if (event.keyboard.keycode==ALLEGRO_KEY_RIGHT and state!=1 and difficulty>=1)
                        difficulty-=0.5;
                    if (event.keyboard.keycode==ALLEGRO_KEY_LEFT and state!=1 and difficulty<=1)
                        difficulty+=0.5;
                    if (event.keyboard.keycode==ALLEGRO_KEY_UP and state!=0)
                        state--;
                    if (event.keyboard.keycode==ALLEGRO_KEY_DOWN and state!=1)
                        state++;
                    if (event.keyboard.keycode==ALLEGRO_KEY_ENTER and state==1 or event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
                        done=true;
                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    done = true;
                    break;
            }

            if(done)
                break;

            if(redraw && al_is_event_queue_empty(queue))
            {
                GraphicManager->DrawOptions(state,difficulty);
                al_flip_display();
                redraw=false;
            }
        }
    }
    void runCredits(ALLEGRO_EVENT_QUEUE* queue)
    {
        GraphicManager->DrawCredits();
        al_flip_display();
        ALLEGRO_EVENT event;
        while (1)
        {
            al_wait_for_event(queue, &event);
            if (event.type==ALLEGRO_EVENT_KEY_DOWN)
                return;
        }
    }
};  