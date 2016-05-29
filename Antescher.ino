#include "Arduboy.h"
#include "map.h"
Arduboy arduboy;


int mask[10*8]={
1,1,1,1,0,0,1,1,
1,1,0,0,0,0,1,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,1,0,0,0,0,1,1,
1,1,0,0,1,1,1,1
};

int block[10*8]={
0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,
0,0,1,1,1,1,0,0,
0,0,1,1,1,1,0,0,
0,0,0,1,0,0,1,0,
0,0,0,0,0,1,0,0,
0,0,0,0,1,0,1,0,
0,0,0,0,0,1,0,0,
0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0
};

//----------------------------------------------------------
void draw_block(int x, int y)
{
  int i,j,a=0,x2=x+8,y2=y+10;
  
  // mask out then set pixels for a block...
  for (j=y; j<y2; j++) for (i=x; i<x2; i++,a++) {
    if (!mask[a]) arduboy.drawPixel(i,j,0);
    if (block[a]) arduboy.drawPixel(i,j,1);
  }
}

//-----------------------------------------------------------------
void draw_map(int xmap, int ymap)
{ 
  int x,y,z,xs,ys,xm,ym,i,b;
  
  arduboy.fillScreen(1);
  for (x=0; x<35; x++) for (y=0; y<32; y++) {
      xm=xmap+x; ym=ymap+y;
      if (xm<0 || xm>127 || ym<0 || ym>127) b=0;
      else b=pgm_read_byte(amap+ym*128+xm); // stack of 6 blocks to draw
      if (b!=0) {
        xs=80-x*4+y*3; ys=y*3+x*2-40;
        for (z=0; z<6; z++) {
          if (b&1) { draw_block(xs,ys);}
          b=b/2; ys-=4;
          if (b==0) z=6; // exit loop early if possible
        }
     }
  }
}

//-------------------------------------------------------------------
void setup() {
 arduboy.begin();
}

//------------------------------------------------------------------
void loop() {

  int x=0,y=0;

  while(1) {
  draw_map(x,y);
  arduboy.display();
  if (arduboy.pressed(UP_BUTTON)) y--;
  if (arduboy.pressed(DOWN_BUTTON)) y++;
  if (arduboy.pressed(LEFT_BUTTON)) x++;
  if (arduboy.pressed(RIGHT_BUTTON)) x--;
  if (arduboy.pressed(B_BUTTON)) {x=0; y=0;}
  
  };
}
