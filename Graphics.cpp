#include <fstream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include "Entities.cpp"
using namespace std;
const int h=560;
const int l=500;

class Graphics
{
private:
    int scaleW;
    int scaleH;
    int scaleX;
    int scaleY;
    ALLEGRO_DISPLAY * display=NULL;
    ALLEGRO_BITMAP * buffer=NULL;
    ALLEGRO_BITMAP* bitmap=NULL;
    int x;
    int y;
public:
    int** griglia = NULL;
    Graphics (){}
    Graphics (ALLEGRO_DISPLAY* display,ALLEGRO_BITMAP* buffer,int scaleX, int scaleY,int scaleW,int scaleH)
    {
        this->scaleH = scaleH;
        this->scaleW = scaleW;
        this->scaleX = scaleX;
        this->scaleY = scaleY;
        this->buffer = buffer;
        this->display = display;
        ifstream fileinput;
        fileinput.open("level1.txt");
        if (!fileinput)
            cout<<"could not initialize level 1"<<endl;
        fileinput>> x >> y;
        griglia= new int* [x];
        for (int i=0;i<x;i++)
            griglia[i]=new int [y];
        for (int i=0;i<x;i++)
            for (int j=0;j<y;j++)
                fileinput>>griglia[i][j];
        fileinput.close();
    }
    
    
    void DrawMap ()
    {
        al_set_target_bitmap(buffer);
        al_clear_to_color(al_map_rgb(0,0,0));
        for (int i=0;i<x;i++)
        {
            for (int j=0;j<y;j++)
            {
                switch (griglia[i][j])
                {
                    case 1:
                    bitmap= al_load_bitmap("scala.png");
                    al_draw_bitmap(bitmap,j*20,i*20,0);
                    al_destroy_bitmap(bitmap);
                    break;
                    case 2:
                    bitmap= al_load_bitmap("ground.png");
                    al_draw_bitmap(bitmap,j*20,i*20,0);
                    al_destroy_bitmap(bitmap);
                    break;
                }
            }
        }
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h,scaleX, scaleY, scaleW, scaleH,0);
    }
    
    
    void DrawPlayer(Player* Play)
    {
        al_set_target_bitmap(buffer);
        bitmap=al_load_bitmap("mario.png");
        al_draw_bitmap(bitmap,Play->getY(),Play->getX(),0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h,scaleX, scaleY, scaleW, scaleH,0);
    }


    void DrawKong(Kong* Wukong)
    {
        al_set_target_bitmap(buffer);
        if (Wukong->getFrame()>0 and Wukong->getFrame()<=10)
            bitmap= al_load_bitmap("kong1.png");
        else if (Wukong->getFrame()>10 and Wukong->getFrame()<=20)
            bitmap= al_load_bitmap("kong2.png");
        else if (Wukong->getFrame()>20 and Wukong->getFrame()<=30)
            bitmap= al_load_bitmap("kong3.png");
        else if (Wukong->getFrame()>30 and Wukong->getFrame()<=40)
            bitmap= al_load_bitmap("kong4.png");
        else
            bitmap= al_load_bitmap("kong5.png");
        al_draw_bitmap(bitmap, Wukong->getY(), Wukong->getX(), 0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
        if (Wukong->getFrame()<52)
            Wukong->nextFrame();
        else
            Wukong->resetFrame();
    } 


    void DrawStaticBarrels()
    {
        al_set_target_bitmap(buffer);  
        bitmap=al_load_bitmap("barrel_standing.png");
        al_draw_bitmap(bitmap,33, 99,0);
        al_draw_bitmap(bitmap,33, 120,0);
        al_draw_bitmap(bitmap,10, 99,0);
        al_draw_bitmap(bitmap,10, 120,0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h,scaleX, scaleY, scaleW, scaleH,0);
        
    }
    ~Graphics()
    {
        for (int i=0;i<x;i++)
            delete griglia[i];
        delete [] griglia;
    }
};
