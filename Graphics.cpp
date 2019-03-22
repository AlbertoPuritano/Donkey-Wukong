#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "Entities.cpp"
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
public:
    Graphics (){}
    Graphics (ALLEGRO_DISPLAY* display,ALLEGRO_BITMAP* buffer,int scaleX, int scaleY,int scaleW,int scaleH)
    {
        this->scaleH = scaleH;
        this->scaleW = scaleW;
        this->scaleX = scaleX;
        this->scaleY = scaleY;
        this->buffer = buffer;
        this->display = display;
    }
    
    
    void DrawMap ()
    {
        al_set_target_bitmap(buffer);
        al_clear_to_color(al_map_rgb(0,0,0));
        for (int i=0;i<28;i++)
        {
            for (int j=0;j<25;j++)
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
    
    
    void DrawPlayer(Entity* Player)
    {
        al_set_target_bitmap(buffer);
        bitmap=al_load_bitmap("mario.png");
        al_draw_bitmap(bitmap,Player->getY(),Player->getX(),0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h,scaleX, scaleY, scaleW, scaleH,0);
    }


    void DrawKong(Entity* Kong)
    {
        al_set_target_bitmap(buffer);
        bitmap = al_load_bitmap("kong.png");
        al_draw_bitmap(bitmap, Kong -> getX(), Kong -> getY(), 0);
        al_destroy_bitmap(bitmap);
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
    } 


    void DrawStaticBarrel()
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
};
