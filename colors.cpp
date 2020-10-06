
#include <iostream>
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

    double min = 1.0;
    for (int i = 0; i < 3; i++) {
        if (arrRGB[i] < min) {
            min = arrRGB[i];
        }
    }
    for (int i = 0; i < 3; i++) {
        arrCMYK[i] = (arrRGB[i] - min) / (1.0 - min);
    }
    arrCMYK[3] = min;
    return;
};

void fromRGBtoHSV(double* arr, double* arrHSV) {
    double min = arr[0];
    double max = arr[0];
    for (int i = 0; i < 3; i++) {
        if (min > arr[i])
            min = arr[i];
        if (max < arr[i])
            max = arr[i];
    }
    double h = 60.0 * ((arr[1] - arr[2]) / (max - min));
    if ((max == arr[0]) && (arr[1] >= arr[2]))
        arrHSV[0] = h;
    if ((max == arr[0]) && (arr[1] < arr[2]))
        arrHSV[0] = h + 360.0;
    if (max == arr[1])
        arrHSV[0] = 60.0 * ((arr[2] - arr[0]) / (max - min)) + 120.0;
    if (max == arr[2])
        arrHSV[0] = 60.0 * ((arr[0] - arr[1]) / (max - min)) + 240.0;
    if (max == 0.0)
        arrHSV[1] = 0.0;
    else arrHSV[1] = 1.0 - (min / max);
    arrHSV[2] = max;
    arrHSV[1] = arrHSV[1] * 100.0;
    arrHSV[2] = arrHSV[2] * 100.0;
    return;
}

void fromRGBtoHSL(double* arr, double* arrHSL) {
    double min = arr[0];
    double max = arr[0];
    for (int i = 1; i < 3; i++) {
        if (min > arr[i])
            min = arr[i];
        if (max < arr[i])
            max = arr[i];
    }
    double h = 60.0 * ((arr[1] - arr[2]) / (max - min));
    if ((max == arr[0]) && (arr[1] >= arr[2]))
        arrHSL[0] = h;
    if ((max == arr[0]) && (arr[1] < arr[2]))
        arrHSL[0] = h + 360.0;
    if (max == arr[1])
        arrHSL[0] = 60.0 * ((arr[2] - arr[0]) / (max - min)) + 120.0;
    if (max == arr[2])
        arrHSL[0] = 60.0 * ((arr[0] - arr[1]) / (max - min)) + 240.0;
    arrHSL[1] = (max - min) / (1.0 - abs(1.0 - (max + min)));
    arrHSL[2] = 0.5 * (max + min);
    return;
}

void fromRGBtoXYZ(double* arr, double* arrXYZ) {
    arrXYZ[0] = 1.13014 * arr[2] + 1.75171 * arr[1] + 2.76883 * arr[0];
    arrXYZ[1] = 0.06007 * arr[2] + 4.59061 * arr[1] + arr[0];
    arrXYZ[2] = 5.59417 * arr[2] + 0.05651 * arr[1];
    return;
}

void printColor(int system, double* arr,int size) {
    cout << "Your color in model  " << system << " is: ";
    for (int i = 0; i < size; i++) {
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
