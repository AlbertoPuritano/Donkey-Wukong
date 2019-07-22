#include "../Headers/Game.hpp"
    Game::Game(Graphics* g,Sounds* s):SoundManager(s),GraphicManager(g),difficulty(1.0),muted(false){}
    
    int Game::runMenu(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue)
    {        
        al_flush_event_queue(queue);
        SoundManager->stopSamples();
        if (!muted)
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
                    {
                        state--;
                        if (!muted)
                            SoundManager->playPress();
                    }
                    if(event.keyboard.keycode==ALLEGRO_KEY_DOWN and state!=3)
                    {
                        state++;
                        if (!muted)
                            SoundManager->playPress();
                    }
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

            if(redraw and al_is_event_queue_empty(queue))
            {
                GraphicManager->DrawMenu(state);
                al_flip_display();
                redraw=false;
            }
        }
        SoundManager->stopSamples();
        return 0;
    }
    
    
    bool Game::runGame(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue,int& lifes,int& level,int &score)
    {
        SoundManager->stopMenu();
        if (level==3)                     //nel level 3 ci sono piu' barili
            difficulty-=0.3;
        GraphicManager->assignGrid(level);
        bool complete=false;
        unsigned hammerTime = 0;
        srand(time(0));
        SoundManager->stopSamples();
        if (!muted)
            SoundManager->startNewGame();
        list <Barrel> Barili;
        Barrel Bar(GraphicManager->grid);
        int addpunteggiomartello=0;
        int addpunteggiobarile=0;
        pair <int,int> segnaCancellazione;
        segnaCancellazione.first=0;
        segnaCancellazione.second=0;
        int frameExpl=0;   
        #define KEY_SEEN     1
        #define KEY_RELEASED 2
        unsigned char key[ALLEGRO_KEY_MAX];
        memset(key, 0, sizeof(key));
        while (lifes!=0)
        {
            #define KEY_SEEN     1
            #define KEY_RELEASED 2
            unsigned char key[ALLEGRO_KEY_MAX];
            memset(key, 0, sizeof(key));
            al_flush_event_queue(queue);
            hammerTime=0;
            Player* Play= new Player(GraphicManager->grid);
            Kong* Wukong = new Kong(GraphicManager->grid, difficulty);
            Entity* Peach= new Entity(60,220,GraphicManager->grid);
            auto temp=Barili.begin();
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
                            if (!muted)
                                SoundManager->playWalking();  
                        }
                        if(key[ALLEGRO_KEY_RIGHT])
                        {   
                            Play->MoveRight();      
                            if (!muted)
                                SoundManager->playWalking();
                        }
                        if(key[ALLEGRO_KEY_SPACE])
                        {   
                            Play->Jump();           
                            if (!muted)
                                SoundManager->playJump();       
                        }
                        if(key[ALLEGRO_KEY_ESCAPE])
                        {
                            done = true;                    
                            lifes=1;
                        }
                        if(key[ALLEGRO_KEY_TAB])
                        {
                            complete=true;          //LEVEL SKIPPER CHEAT
                            done=true;
                        }
                        if(key[ALLEGRO_KEY_LSHIFT] and Play->getMartello())
                        {
                            Play->setHammered(true);
                            hTime++;
                            if (!muted)
                                SoundManager->playHammer();
                        }
                        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                            key[i] &= KEY_SEEN;


                        Play->HandleGravity(); 
                        if(Play -> getX()/20 == 21 and Play -> getY()/20 == 17 and Play->getMartello()==false and hammerTime == 0)//prende il martello.
                            Play -> setMartello(true);    
                        if(hTime < 30)
                            hTime++;
                        else
                        {
                            hTime=0;
                            Play->setHammered(false);
                        }
                    
                        if(Play->getMartello())
                            hammerTime++;
                        if(hammerTime > 325 and Play->getMartello())
                            Play->setMartello(false);    
                        if (Wukong->getLancia() == Wukong->getFrame())
                        {    
                            Barili.push_back(Bar);
                            Wukong->nextFrame();
                        } 
                        for (auto i=Barili.begin();i!=Barili.end();i++)
                        {
       
                            i->roll();
                            i->HandleGravity();
                            if (Play->getX()/20==i->getX()/20 and Play->getY()/20==i->getY()/20)
                            {            
                                SoundManager->stopSamples();
                                if (!muted)
                                    SoundManager->playDeath();
                                Play->setMorto(true);
                                al_rest(4);
                                done=true;
                            }
                            
                            if((Play->getX()/20 == (i->getX()/20)-1 or Play->getX()/20 == (i->getX()/20)-2) and Play->getY()/20 == i->getY()/20 
                                and i->getJumped() == false and Play->getLadderstate() == false and (Play->getJump() or Play->isFalling()))
                                {
                                    score += 100;
                                    addpunteggiobarile+=4; 
                                    i->setJumped(true);
                                }
                            
                            if (i->getStop())
                            {
                                temp = i;
                                i++;
                                Barili.erase(temp);
                                
                            } 
                            if(
                            Play->getHammered() and Play->getDirection() == LEFT and (Play->getY()/20)-1==i->getY()/20 and Play->getX()/20==i->getX()/20
                            or
                            Play->getHammered() and Play->getDirection() == RIGHT and (Play->getY()/20)+1==i->getY()/20 and Play->getX()/20==i->getX()/20)
                            {
                                temp=i;
                                segnaCancellazione.first=i->getX();
                                segnaCancellazione.second=i->getY(); 
                                i++;
                                Barili.erase(temp);
                                score += 300;
                                addpunteggiomartello+=5;                                                  
                            }
                            
                        }
                        if (Play->getX()/20==Peach->getX()/20 and Play->getY()/20==Peach->getY()/20 and level!=4)  //completa il level
                        {
                            complete=true;
                            done=true;
                        }
                        if (Play->getX()/20==6 and Play->getY()/20==1 and level==4)  //completa il gioco
                        {
                            complete=true;
                            done=true;
                        }
                        redraw = true;
                        break;

                    case ALLEGRO_EVENT_KEY_DOWN:
                        key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                        break;
                    case ALLEGRO_EVENT_KEY_UP:
                        key[event.keyboard.keycode] &= KEY_RELEASED;
                        break;

                    case ALLEGRO_EVENT_DISPLAY_CLOSE:
                        done = true;
                        lifes=1;
                        break;
            
                }

                if(done)
                    break;

                if(redraw and al_is_event_queue_empty(queue))
                {
                    GraphicManager->DrawMap(false);
                    GraphicManager->DrawPeach(Peach);
                    GraphicManager->DrawStaticBarrels();
                    GraphicManager->DrawKong(Wukong);
                    GraphicManager->DrawExplosive(frameExpl);
                    if(Play->getMartello() and Play->getFrame() <= 30)
                        GraphicManager->DrawPlayerHammer(Play);                    
                    else
                        GraphicManager->DrawPlayer(Play);
                    
                    for (auto i=Barili.begin();i!=Barili.end();i++)   
                        GraphicManager->DrawBarrel(*i);
                    if(Play->getMartello()==false and hammerTime <200)
                        GraphicManager->DrawHammer();
                    GraphicManager->DrawScore(score);
                    if (addpunteggiomartello>0)
                    {
                        GraphicManager->DrawInstantScore(1,Play->getX()-9,Play->getY());
                        addpunteggiomartello--;                      
                    }
                    if (addpunteggiobarile>0)
                    {
                        GraphicManager->DrawInstantScore(2,Play->getX()-9,Play->getY());
                        addpunteggiobarile--;
                    }
                    GraphicManager->DrawDelete(segnaCancellazione.first,segnaCancellazione.second); 
                    GraphicManager->DrawLives(lifes);
                    al_flip_display();
                    redraw = false;
                }
            }
            delete Play;    delete Wukong;    delete Peach;   Barili.clear();
            if (complete)
                break;
            lifes--;
        }
        if (level==3)                 //difficoltà torna normale
            difficulty+=0.3;
        SoundManager->stopSamples();
        return complete;
    }   
    void Game::runOptions(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue)
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
                    {
                        difficulty-=0.5;
                        if (!muted)
                            SoundManager->playPress();
                    }
                    if (event.keyboard.keycode==ALLEGRO_KEY_LEFT and state!=1 and difficulty<=1)
                    {
                        difficulty+=0.5;
                        if (!muted)
                            SoundManager->playPress();
                    }
                    if (event.keyboard.keycode==ALLEGRO_KEY_UP and state!=0)
                    {
                        state--;
                        if (!muted)
                            SoundManager->playPress();
                    }
                    if (event.keyboard.keycode==ALLEGRO_KEY_DOWN and state!=1)
                    {
                        state++;
                        if (!muted)                
                            SoundManager->playPress();
                    }
                    if (event.keyboard.keycode==ALLEGRO_KEY_ENTER and state==1 or event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
                    {
                        done=true;
                        if (!muted)
                            SoundManager->playBack();
                        al_rest(0.3);
                    }
                    if (event.keyboard.keycode==ALLEGRO_KEY_M)
                    {
                        SoundManager->playPress();                        
                        if (muted)
                        {
                            muted=false;
                            SoundManager->playMenu();
                        }
                        else
                        {
                            muted=true;
                            SoundManager->stopMenu();
                        }
                    }
                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    done = true;
                    break;
            }

            if(done)
                break;

            if(redraw and al_is_event_queue_empty(queue))
            {
                GraphicManager->DrawOptions(state,difficulty);
                al_flip_display();
                redraw=false;
            }
        }
    }
    void Game::runStatic(ALLEGRO_EVENT_QUEUE* queue,int a)
    {
        al_flush_event_queue(queue);
        GraphicManager->DrawImage(a);
        if (a==2 and !muted)
            SoundManager->playMammaMia();
        al_flip_display();
        ALLEGRO_EVENT event;
        while (1)
        {
            al_wait_for_event(queue, &event);
            if (event.type==ALLEGRO_EVENT_KEY_DOWN)
            {
                if (!muted)
                {
                    SoundManager->playBack();
                    al_rest(0.3);
                }
                return;
            }
        }
    }
    void Game::runCut(ALLEGRO_EVENT_QUEUE* queue,ALLEGRO_TIMER* timer,int frame)
    {                          
        SoundManager->stopSamples();
        GraphicManager->assignGrid(0);
        ALLEGRO_EVENT event;
        al_start_timer(timer);
        bool done = false;
        bool redraw = true;
        float rests[19]={1.3,0.5,1.0,0.5,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.7,0.8,1.6,1.2,2.0};
        while (1)
        {
            al_wait_for_event(queue, &event);
            switch (event.type)
            {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    done=true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    done=true;
                    break;
                case ALLEGRO_EVENT_TIMER:
                    redraw=true;
                    break;
            }
            if (done)
                break;
            if (redraw and al_is_event_queue_empty(queue))
            {
                GraphicManager->DrawCut(frame);
                al_flip_display();
                redraw=false;
                al_rest(rests[frame]);
                frame++;
                if (frame==14 or frame==19)
                    done=true;
            }
        }
    }  