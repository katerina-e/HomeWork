#include "tgaimage.h"
#include "tgaimage.cpp"
#include <iostream>
#include <cmath>
using namespace std;

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
void DDAline (int x1, int y1, int x2, int y2,TGAImage& image, TGAColor color){

  int dx = x2-x1;
  int dy = y2-y1;
  int absdx = abs(dx);
  int absdy = abs(dy);
  int x =x1;
  int y =y1;

  if(((x1>x2)&&(y1>y2))||((x1>x2)&&(y1<y2))){
    int tx= x1;
    int ty= y1;
    x1 = x2;
    x2 = tx;
    y1 = y2;
    y2 = ty;
  };

    if(dy>0){
     if(dx<dy){
       int d1x = 1;
       int d1y = absdy/absdx;
       while(x<=x2){
          image.set(x,y,color);
          x = x+d1x;
          y = y+d1y;
      }
     }
     else{
       int d1x = absdx/absdy;
       int d1y = 1;
       while(x<=x2){
          image.set(x,y,color);
          x = x+d1x;
          y = y+d1y;
      }
     }
    }
    else{
       if(absdx<absdy){
         int d1x = 1;
         int d1y = absdy/absdx;
         while(x<=x2){
           image.set(x,y,color);
           x = x+d1x;
           y = y-d1y;
         }
       }
       else{
         int d1x = absdx/absdy;
         int d1y = 1;
        while(x<=x2){
          image.set(x,y,color);
          x = x+d1x;
          y = y-d1y;
        }
       }
    }
return;
}

void CirclePar(int x0, int y0, int r,TGAImage& image, TGAColor color){

int x2 = x0+r;
int y2 = y0;
for(int i= 1; i<=360; i++){
    int x1= x2;
    int y1= y2;
    x2 = round(r*cos(i))+x0;
    y2 = round(r*sin(i))+x0;
    image.set(x2,y2,color); //BrLine(x1, y1, x2, y2, image, color);
}
return;
}

void CirclePixel(int x0, int y0, int x, int y, TGAImage& image, TGAColor color ){

   image.set(x0+x,y0+y,color);
   image.set(x0+y,y0+x,color);
   image.set(x0+y,y0-x,color);
   image.set(x0+x,y0-y,color);

   image.set(x0-x,y0-y,color);
   image.set(x0-y,y0-x,color);
   image.set(x0-y,y0+x,color);
   image.set(x0-x,y0+y,color);

return;
};

void Circle (int x0, int y0, int r, TGAImage& image, TGAColor color){
int R= (r*r)/2;
int x=0;
int y;
while((x*x)<= R){
    int tempr = (r-x)*(r+x);
    y = sqrt(tempr);
    CirclePixel(x0,y0,x,y,image,color);
    x= x+1;
}
return;
};

/*void CircleBr (int x0, int y0,int r, TGAImage& image, TGAColor color ){

int x =0;
int y =r;
int d = 1- 2*r;
int mist = 0;
while( y>= 0){
    image.set(x0+x, y0+y, color);
    image.set(x0+x, y0-y, color);
    image.set(x0-x, y0+y, color);
    image.set(x0-x, y0-y, color);

    mist = 2*(d+y)-1;
    if((d<0)&&(mist<=0)){
        x= x+1;
        d= d+2*x+1;
    }
    if ((d>0)&&(mist>0)){
        y= y-1;
        d= d-(2*y+1);
    }
    x= x+1;
    y= y-1;
    d= d+2*(x-y);
}
return;
};*/

void CircleBr (int x0, int y0, int r, TGAImage& image, TGAColor color ){

  image.set(x0, y0, white);
  int d = 3 - 2 * r;
  int x = x0;
  int y = y0 + r;
  float temp = x0 + r/(sqrt(2));
  while (x < temp){
    CirclePixel(x0, y0, (x-x0), (y-y0), image, color);

    if (d < 0)
       d = d + 4*(x-x0) +6;
    else{
       d = d + 4*((x-x0)-(y-y0)) + 10;
       y = y - 1;
    }
    x = x + 1;
  }
return;
};

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	//BrLine(20,80,40,30,image, red);
	//image.set(50, 50, red);
	//DDAline(20,80,40,30,image,white);
	CircleBr (20,50,15,image,red);
	//CirclePar(50,50,30,image,white);
	//Circle(50,50,15,image,white);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

