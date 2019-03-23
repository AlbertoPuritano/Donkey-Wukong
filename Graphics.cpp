#include <fstream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
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
            cout<<"could not initialize matrix"<<endl;
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
    
    
    void DrawPlayer(int PlayerX ,int PlayerY)
    {
        al_set_target_bitmap(buffer);
        bitmap=al_load_bitmap("mario.png");
        al_draw_bitmap(bitmap,PlayerY,PlayerX,0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h,scaleX, scaleY, scaleW, scaleH,0);
    }


    void DrawKong(int KongX,int KongY)
    {
        al_set_target_bitmap(buffer);
        bitmap = al_load_bitmap("kong.png");
        al_draw_bitmap(bitmap, KongY, KongX, 0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
    } 


    void DrawStaticBarrels()
    {
        al_set_target_bitmap(buffer);  
        bitmap=al_load_bitmap("barrel_standing.png");
        al_draw_bitmap(bitmap,33, 99,0);
        al_draw_bitmap(bitmap,33, 120,0);
        al_draw_bitmap(bitmap,10, 99,0);
        al_draw_bitmap(bitmap,10, 120,0);

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
