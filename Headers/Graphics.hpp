#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <fstream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include "Entities.hpp"
#include <vector>  
using namespace std;

class Graphics
{
private:
    int scaleW;
    int scaleH;
    int scaleX;
    int scaleY;
    ALLEGRO_DISPLAY * display;
    ALLEGRO_BITMAP * buffer;
    ALLEGRO_BITMAP* bitmap;
    ALLEGRO_FONT* font;
    ALLEGRO_FONT* fontscore;
    vector <ALLEGRO_BITMAP*> staticBitmaps;  
    int x;
    int y;
    bool allocata;
public:
    int** grid = NULL;
    Graphics (ALLEGRO_DISPLAY* display,ALLEGRO_BITMAP* buffer,int scaleX, int scaleY,int scaleW,int scaleH,ALLEGRO_FONT* font,ALLEGRO_FONT* fontscore);
    void assegnaGriglia(int level);
    void DrawMap (bool cutscene);
    void DrawHammer();
    void DrawPlayerHammer(Player* Play);
    void DrawPlayer(Player* Play);
    void DrawKong(Kong* Wukong);
    void DrawStaticBarrels();
    void DrawExplosive(int& frame);
    void DrawBarrel(Barrel& Bar);
    void DrawPeach(Entity* Peach);
    void DrawMenu(short unsigned n);
    void DrawInstantScore(int opt, int x, int y);
    void DrawClear(int& x,int& y);
    void DrawScore (int score);
    void DrawLives(int lifes);
    void DrawOptions(int n,float difficulty);
    void DrawImage(int a);
    void DrawCut(int frame);
    ~Graphics();
};
#endif