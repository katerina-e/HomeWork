#include "tgaimage.h"
#include "tgaimage.cpp"
#include <iostream>
using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void BrLine(int x1,int y1, int x2,int  y2,TGAImage image, TGAColor color){

  int absdx = abs(x1-x2);
  int absdy = abs(y1-y2);
  int mist = 0;
  int dmist= absdy+1;
  int y = y1;
  int dy = y2-y1;
  if (dy>0){
     dy = 1;
  };
  if (dy<0){
     dy = -1;
  };
  for  (int i= x1; i<= x2; i++){
     image.set(i,y, color);
     mist = mist+ dmist;
     if (mist >= (absdx+1)){
        y = y + dy;
        mist = mist - (absdx+1);
     };
  };

return;
}
void CDAline (int x1, int y1, int x2, int y2,TGAImage image, TGAColor color){

  int dx = x2-x1;
  int dy = y2-y1;
  int absdx = abs(dx);
  int absdy = abs(dy);
  int m= max(absdx,absdy);
  int e= 1/m;
  int y = y1;
  for (int x= x1; x<=(x1+absdx); x++){
     image.set(x,y,color);
     x= x+ e*dx;
     y= y+ e*dy;
  }
return;
}

void CirclePar(int x0, int y0, int r,TGAImage image, TGAColor color){

int x2 = x0+r;
int y2 = y0;
for(int i= 1; i<=360; i++){
    int x1= x2;
    int y1= y2;
    x2 = round(r*cos(i))+x0;
    y2 = round(r*sin(i))+x0;
    BrLine(x1, y1, x2, y2, image, color);
}
return;
}

void CirclePixel(int x0, int y0, int x, int y, TGAImage image, TGAColor color ){

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

void Circle (int x0, int y0, int r, TGAImage image, TGAColor color){

for(int x=0; x<= (r/sqrt(2));x++){
    int y = (int)(sqrt(r^2-x^2));
    CirclePixel(x0, y0,x,y,image,color);
}
return;
};

void CircleBr (int x0, int y0,int r, TGAImage image, TGAColor color ){

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
        d= d-(2*+1);
    }
    x= x+1;
    y= y+1;
    d= d+2*(x-y);
}
return;
};

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(10, 10, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	//BrLine(25,25,50,70,image, red);
	//CDAline(25,25,50,70,image,red);
	Circle (45,56,7,image,white);
	image.write_tga_file("output.tga");
	return 0;
}

