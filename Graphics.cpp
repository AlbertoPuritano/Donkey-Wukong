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
        fileinput.open("Assets/Maps/level1.txt");
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
                        bitmap= al_load_bitmap("Assets/Bitmaps/Tiles/scala.png");
                        al_draw_bitmap(bitmap,j*20,i*20,0);
                        al_destroy_bitmap(bitmap);
                    break;
                        case 2:
                        bitmap= al_load_bitmap("Assets/Bitmaps/Tiles/ground.png");
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
        if (Play->getFrame()>=0 and Play->getFrame()<=5)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/right1.png");
        else if (Play->getFrame()>=6 and Play->getFrame()<=10)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/right2.png");
        else if (Play->getFrame()>=11 and Play->getFrame()<=15)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/right3.png");
        else if (Play->getFrame()>=16 and Play->getFrame()<=20)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/left1.png");
        else if (Play->getFrame()>=21 and Play->getFrame()<=25)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/left2.png");
        else if (Play->getFrame()>=26 and Play->getFrame()<=30)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/left3.png");
        else if (Play->getFrame()>=31 and Play->getFrame()<=33)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/climb1.png");
        else if (Play->getFrame()>=34 and Play->getFrame()<=36)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/climb2.png");
        else if (Play->getFrame()==37)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/jumpr.png");
        else if (Play->getFrame()==38)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/jumpl.png");
        else if (Play->getFrame()==39)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/rightfall.png");
        else if (Play->getFrame()==40)
            bitmap=al_load_bitmap("Assets/Bitmaps/Player/leftfall.png");
        al_draw_bitmap(bitmap,Play->getY(),Play->getX(),0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h,scaleX, scaleY, scaleW, scaleH,0);
    }


    void DrawKong(Kong* Wukong)
    {
        al_set_target_bitmap(buffer);
        if (Wukong->getFrame()>0 and Wukong->getFrame()<=Wukong->getDifficolta()*20)
            bitmap= al_load_bitmap("Assets/Bitmaps/Kong/kong1.png");
        else if (Wukong->getFrame()>Wukong->getDifficolta()*20 and Wukong->getFrame()<=Wukong->getDifficolta()*40)
            bitmap= al_load_bitmap("Assets/Bitmaps/Kong/kong2.png");
        else if (Wukong->getFrame()>Wukong->getDifficolta()*40 and Wukong->getFrame()<=Wukong->getDifficolta()*60)
            bitmap= al_load_bitmap("Assets/Bitmaps/Kong/kong3.png");
        else if (Wukong->getFrame()>Wukong->getDifficolta()*60 and Wukong->getFrame()<=Wukong->getDifficolta()*80)
            bitmap= al_load_bitmap("Assets/Bitmaps/Kong/kong4.png");
        else
            bitmap= al_load_bitmap("Assets/Bitmaps/Kong/kong5.png");
        al_draw_bitmap(bitmap, Wukong->getY(), Wukong->getX(), 0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
        Wukong -> nextFrame();
    } 


    void DrawStaticBarrels()
    {
        al_set_target_bitmap(buffer);  
        bitmap=al_load_bitmap("Assets/Bitmaps/Barrel/barrel_standing.png");
        al_draw_bitmap(bitmap,33, 99,0);
        al_draw_bitmap(bitmap,33, 120,0);
        al_draw_bitmap(bitmap,10, 99,0);
        al_draw_bitmap(bitmap,10, 120,0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h,scaleX, scaleY, scaleW, scaleH,0);
    }
    void DrawBarrel(Barrel Bar)
    {
        al_set_target_bitmap(buffer);
        if (Bar.isFalling())
            bitmap=al_load_bitmap("Assets/Bitmaps/Barrel/barrelfalling.png");
        else
            bitmap=al_load_bitmap("Assets/Bitmaps/Barrel/barrel.png");
        al_draw_bitmap(bitmap,Bar.getY(),Bar.getX(),0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h,scaleX, scaleY, scaleW, scaleH,0);
    }
    void DrawMenu(short unsigned n)
    {
        al_set_target_bitmap(buffer);
        switch(n)
        {
            case 0:
                bitmap=al_load_bitmap("Assets/Bitmaps/Menu/Menu0.png");
                break;
            case 1:
                bitmap=al_load_bitmap("Assets/Bitmaps/Menu/Menu1.png");
                break;
            case 2:
                bitmap=al_load_bitmap("Assets/Bitmaps/Menu/Menu2.png");
                break;
            case 3:
                bitmap=al_load_bitmap("Assets/Bitmaps/Menu/Menu3.png");
                break;
        }
        al_draw_bitmap(bitmap, 0, 0, 0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
    }
    ~Graphics()
    {
        for (int i=0;i<x;i++)
            delete griglia[i];
        delete [] griglia;
    }
};
