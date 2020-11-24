#include "tgaimage.h"
#include "tgaimage.cpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int const sizePicture = 1000;
int const centerPicture = 1500;
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void BrLine(int x1,int y1, int x2,int  y2,TGAImage& image, TGAColor color){

  if(((x1>x2)&&(y1>y2))||((x1>x2)&&(y1<y2))){
    int tx= x1;
    int ty= y1;
    x1 = x2;
    x2 = tx;
    y1 = y2;
    y2 = ty;
  };

  int dx = x2-x1;
  int dy = y2-y1;

  if(dy>0){
    if(dx>=dy){
     int x =x1;
     int y =y1;
     int d = 2*dy -dx;
     while(x<=x2){
       image.set(x,y,color);
       if(d<0)
          d= d+2*dy;
       else{
          d= d+ 2*(dy-dx);
          y= y+1;
       }
       x= x+1;
     }
    }
    else{
      int x =x1;
      int y =y1;
      int d = 2*dx -dy;
      while(y<=y2){
        image.set(x,y,color);
        if(d<0)
          d= d+2*dx;
        else{
          d= d+ 2*(dx-dy);
          x= x+1;
        }
      y= y+1;
      }
    }
  }
  else{
    int absdy = abs(dy);
    if(dx>=absdy){
     int x =x1;
     int y =y1;
     int d = 2*absdy -dx;
     while(x<=x2){
       image.set(x,y,color);
       if(d<0)
          d= d+2*absdy;
       else{
          d= d+ 2*(absdy-dx);
          y= y-1;
       }
       x= x+1;
     }
    }
    else{
     int x =x1;
     int y =y1;
     int d = 2*dx-absdy;
     while(y>=y2){
       image.set(x,y,color);
       if(d<0)
          d= d+2*dx;
       else{
          d= d+ 2*(dx-absdy);
          x= x+1;
       }
       y= y-1;
     }
    }

  }

return;
}


void DrawFile (TGAImage& image, TGAColor color){

   string line;
   vector<vector<float>> pix;

  ifstream fin("AfricanHead.obj");

    while (fin >> line){

        if (line == "v"){

            float x, y, z;
            fin >> x >> y >> z;
            x = x*sizePicture;
            y = y*sizePicture;
            z = 0;

            pix.push_back({x,y,z});
         }
        if (line == "f"){

            int p1,p2,p3,skip;
            char slash;

            fin >> p1 >> slash >> skip >> slash >> skip >> p2 >> slash >> skip >> slash >> skip >> p3 >> slash >> skip >> slash >> skip ;
            p1 = p1 -1;
            p2 = p2 -1;
            p3 = p3 -1;

            BrLine( pix[p1][0] +centerPicture, pix[p1][1] +centerPicture, pix[p2][0] +centerPicture, pix[p2][1] +centerPicture, image, red);
            BrLine( pix[p1][0] +centerPicture, pix[p1][1] +centerPicture, pix[p3][0] +centerPicture, pix[p3][1] +centerPicture, image, red);
            BrLine( pix[p2][0] +centerPicture, pix[p2][1] +centerPicture, pix[p3][0] +centerPicture, pix[p3][1] +centerPicture, image, red);

        }
    }

    fin.close();
}

void Paral (int x1, int y1, int x2, int y2, int x3, int y3, int px, int py,TGAImage& image, TGAColor color){

   x1= x1+ px;
   y1= y1+ py;
   x2= x2+ px;
   y2= y2+ py;
   x3= x3+ px;
   y3= y3+ py;

   BrLine(x1,y1,x2,y2,image,color);
   BrLine(x1,y1,x3,y3,image,color);
   BrLine(x2,y2,x3,y3,image,color);
}

void Mashtab (int x1, int y1, int x2, int y2, int x3, int y3, int mx, int my,TGAImage& image, TGAColor color){

   x1= x1* mx;
   y1= y1* my;
   x2= x2* mx;
   y2= y2* my;
   x3= x3* mx;
   y3= y3* my;

   BrLine(x1,y1,x2,y2,image,color);
   BrLine(x1,y1,x3,y3,image,color);
   BrLine(x2,y2,x3,y3,image,color);

}

void Turn (int x1, int y1, int x2, int y2, int x3, int y3, double angel ,TGAImage& image, TGAColor color){

  float tempx1, tempx2, tempx3, tempy1, tempy2, tempy3;

  tempx1 = abs(x1*cos(angel)-y1*sin(angel));
  tempy1 = abs(x1*sin(angel)-y1*cos(angel));
  tempx2 = abs(x2*cos(angel)-y2*sin(angel));
  tempy2 = abs(x2*sin(angel)-y2*cos(angel));
  tempx3 = abs(x3*cos(angel)-y3*sin(angel));
  tempy3 = abs(x3*sin(angel)-y3*cos(angel));

  x1= tempx1;
  y1= tempy1;
  x2= tempx2;
  y2= tempy2;
  x3= tempx3;
  y3= tempy3;

  BrLine(x1,y1,x2,y2,image,color);
  BrLine(x1,y1,x3,y3,image,color);
  BrLine(x2,y2,x3,y3,image,color);
}


int main (int argc, char** argv){

  TGAImage image(3000, 3000, TGAImage::RGB);
  DrawFile(image, white);
  image.flip_vertically();
  image.write_tga_file("output.tga");

  return 0;
}

