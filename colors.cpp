
#include <iostream>
#include <cmath>
using namespace std;

void fromCMYtoRGB(double* arrFrom, double* arrTo) {

    for (int i = 0; i < 3; i++) {
        arrTo[i] = 1.0 - arrFrom[i];
    }
    return;
}

void fromCMYKtoRGB(double* arr ,double* arrRGB ) {

    for (int i = 0; i < 3; i++) {
        arrRGB[i] = arr[i] * (1.0 - arr[3]) + arr[3];
        arrRGB[i] = 1.0 - arrRGB[i];
    };
    return;
}

void fromHSVtoRGB(double* arr) {
    int x = (int)(arr[0] / 60);
    int y = (int)(arr[0]);
    double  h = (x % 6);
    double  v1 = ((100 - arr[1]) * arr[2]) / 100;
    double  a = ((arr[2] - v1) * (y % 60) / 60);
    double  v2 = v1 + a;
    double  v3 = arr[2] - a;
    if (h == 0) {
        arr[0] = arr[2];
        arr[1] = v2;
        arr[2] = v1;
    }
    if (h == 1) {
      arr[0] = v3;
      arr[1] = arr[2];
      arr[2] = v1;
    }
    if (h == 2) {
       arr[0] = v1;
       arr[1] = arr[2];
       arr[2] = v2;
    }
    if (h == 3) {
       arr[0] = v1;
        arr[1] = v3;
    }
    if (h == 4) {
        arr[0] = v2;
        arr[1] = v1;
    }
    if (h == 5) {
        arr[0] = arr[2];
        arr[1] = v1;
        arr[2] = v3;
    }
    for (int i = 0; i < 3; i++) {
        arr[i] = arr[i] * 0.01;
    }
     return;
     }

void fromHSLtoRGB(double *arr) {

    double q;
    if (arr[2] < 0.5) {
        q = arr[2] * (1.0 + arr[1]);
    }
    else {
        q = arr[2] + arr[1] - (arr[1] * arr[2]);
    }
    double p = 2.0 * arr[2] - q;
    double  hk = arr[0] / 360.0;
    double  t[3];
    t[0] = hk + (1.0 / 3.0);
    t[1] = hk;
    t[2] = hk - (1.0 / 3.0);
    for (int i = 0; i < 3; i++) {
        if (t[i] < 0) {
            t[i] = t[i] + 1.0;
        }
        else if (t[i] > 1.0) {
            t[i] = t[i] - 1.0;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (t[i] < (1.0 / 6.0)) {
            arr[i] = p + ((q - p) * (6.0) * t[i]);
        }
        else if ((t[i] >= (1.0 / 6.0)) && (t[i] < (0.5))) {
            arr[i] = q;
        }
        else if ((t[i] >= 0.5) && (t[i] < (2.0 / 3.0))) {
            arr[i] = p + ((q - p) * ((2.0 / 3.0) - t[i]) * 6.0);
        }
        else {
            arr[i] = p;
        }
      }
    return;
}

void fromRGBtoCMYK(double* arrRGB,double* arrCMYK) {

    fromCMYtoRGB(arrRGB, arrRGB);

    double minA = 1.0;
    for (int i = 0; i < 3; i++) {
        if (arrRGB[i] < minA) {
            minA = arrRGB[i];
        }
    }
    for (int i = 0; i < 3; i++) {
        arrCMYK[i] = (arrRGB[i] - minA) / (1.0 - minA);
    }
    arrCMYK[3] = minA;
    fromCMYtoRGB(arrRGB, arrRGB);
    return;
};

void fromRGBtoHSV(double* arr, double* arrHSV) {
    double minA = arr[0];
    double maxA = arr[0];
    for (int i = 0; i < 3; i++) {
        if (minA > arr[i])
            minA = arr[i];
        if (maxA < arr[i])
            maxA = arr[i];
    }
    double h = 60.0 * ((arr[1] - arr[2]) / (maxA - minA));
    if ((maxA == arr[0]) && (arr[1] >= arr[2]))
        arrHSV[0] = h;
    if ((maxA == arr[0]) && (arr[1] < arr[2]))
        arrHSV[0] = h + 360.0;
    if (maxA == arr[1])
        arrHSV[0] = 60.0 * ((arr[2] - arr[0]) / (maxA - minA)) + 120.0;
    if (maxA == arr[2])
        arrHSV[0] = 60.0 * ((arr[0] - arr[1]) / (maxA - minA)) + 240.0;
    if (maxA == 0.0)
        arrHSV[1] = 0.0;
    else arrHSV[1] = 1.0 - (minA / maxA);
    arrHSV[2] = maxA;
    arrHSV[1] = arrHSV[1] * 100.0;
    arrHSV[2] = arrHSV[2] * 100.0;
    return;
}

void fromRGBtoHSL(double* arr, double* arrHSL) {
    double minA = arr[0];
    double maxA = arr[0];
    for (int i = 0; i < 3; i++) {
        if (minA > arr[i])
            minA = arr[i];
        if (maxA < arr[i])
            maxA = arr[i];
    }
    if (maxA == minA)
        arrHSL[0]=0.0;
    if ((maxA == arr[0]) && (arr[1] >= arr[2]))
        arrHSL[0] = 60.0 *(arr[1]- arr[2])/(maxA - minA);
    if ((maxA == arr[0]) && (arr[1] < arr[2]))
        arrHSL[0] = 60.0 * (arr[1]-arr[2])/(maxA- minA) + 360.0;
    if (maxA == arr[1])
        arrHSL[0] = 60.0 *(arr[2] - arr[0]) / (maxA - minA) + 120.0;
    if (maxA == arr[2])
        arrHSL[0] = 60.0 * ((arr[0] - arr[1]) / (maxA - minA)) + 240.0;

    //arrHSL[1] = (maxA - minA) / (1.0 - abs(1.0 - (maxA + minA)));
    arrHSL[2] = (maxA + minA)/ 2;

    if ((arrHSL[2]== 0)||(maxA == minA))
        arrHSL[1]= 0;
    if ((arrHSL[2] > 0)&& (arrHSL[2]<= 0.5))
        arrHSL[1]= (maxA - minA)/(maxA + minA);
    if ((arrHSL[2] > 0.5)&& (arrHSL[2] < 1))
        arrHSL[1]= (maxA - minA)/(2.0 - (maxA + minA));

    return;
}

void fromRGBtoXYZ(double* arr, double* arrXYZ) {

    double r = arr[0];
    double g = arr[1];
    double b = arr[2];
    double sr = 0.04045;
    if (r > sr)
        r =pow(((r + 0.055)/ 1.055),2.4);
    else
        r = r / 12.92;
    if (g > sr)
        g =pow(((g + 0.055)/ 1.055),2.4);
    else
        g = g / 12.92;
    if (b > sr)
        b =pow(((b + 0.055)/ 1.055),2.4);
    else
        b = b / 12.92;

    r = r*100;
    g = g*100;
    b = b*100;

    arrXYZ[0]= r * 0.4124 + g * 0.3576 + b * 0.1805;
    arrXYZ[1]= r * 0.2126 + g * 0.7152 + b * 0.0722;
    arrXYZ[2]= r * 0.0193 + g * 0.1192 + b * 0.9505;

    return;
}

void printColor(int system, double* arr,int sizeM) {
    cout << "Your color in model  " << system << " is: ";
    for (int i = 0; i < sizeM; i++) {
        cout << arr[i] << " " << "; ";
    }
    cout << endl;
}

int main()
{
    cout << "1.RGB 2.CMY 3.CMYK 4.HSV 5.HSL 6.XYZ" << endl;
    cout << "R,G,B [0;1]" << endl;
    cout << "H [0;360] for 4 S,V [0;100]; for 5 S,L [0;1] " << endl;
    int model;
    cout << "What model do you have? Type the number of model(from 1 to 5)" << endl;
    cin >> model;
    cout << "What color do you have? Type coordinates with an enter" << endl;
    double* Dcolor;
    double* arrCMYK;
    int w;
    if (model == 3) {
        arrCMYK = new double[4];
        cin >> arrCMYK[0] >> arrCMYK[1] >> arrCMYK[2]>>arrCMYK[3];
        w = 4;
        Dcolor = new double[3];
        fromCMYKtoRGB(arrCMYK, Dcolor);
    }
    else {
        Dcolor = new double[3];
        cin >> Dcolor[0] >> Dcolor[1] >> Dcolor[2];
        w = 3;
    };
    if (model == 2) {
        fromCMYtoRGB(Dcolor,Dcolor);
    };
    if (model == 4) {
        fromHSVtoRGB(Dcolor);
    };
    if (model == 5) {
        fromHSLtoRGB(Dcolor);
    };

    printColor(1, Dcolor, 3);

    double* aCMY = new double[3];
    fromCMYtoRGB(Dcolor, aCMY);
    printColor(2, aCMY, 3);

    double* aCMYK = new double[4];
    fromRGBtoCMYK(Dcolor, aCMYK);
    printColor(3, aCMYK, 4);

    double* aHSV = new double[3];
    fromRGBtoHSV(Dcolor, aHSV);
    printColor(4, aHSV, 3);

    double* aHSL = new double[3];
    fromRGBtoHSL(Dcolor, aHSL);
    printColor(5, aHSL, 3);

    double* aXYZ = new double[3];
    fromRGBtoXYZ(Dcolor, aXYZ);
    printColor(6, aXYZ, 3);

    delete [] aCMYK, aHSV, aHSL, aXYZ, arrCMYK, Dcolor,aCMY;
    return 0;
}
