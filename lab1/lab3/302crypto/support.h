#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include<cstddef>
#include<string>
#include<fstream>
#include<iostream>

typedef unsigned char uchar;
extern const char ETX;

template <typename T>
class matrix { 
	public:

    matrix(){
        buf = NULL;
       // Nrows = 0;
       // Ncols = 0;
        
    }
    void assign(int n_rows,int n_cols){
    //	buf = new char[size];
        Nrows = n_rows;
        Ncols = n_cols;
        buf = new T [Nrows*Ncols];

    }

    ~matrix() {
        delete [] buf;
    }

		int get_Nrows() const { return Nrows; }
		int get_Ncols() const { return Ncols; }
    
		T * operator[] (int i) { return &buf[i*Ncols]; }

		T *data(){
            return buf;

		}
    
  private:
		int Nrows, Ncols;
		T *buf;
};

struct pixel {
    pixel(){rowi=0;coli=0;}
    int rowi;
    int coli;
    
};

struct RGB { int R=0; int G = 0; int B = 0; };

class ppm {
private:
    matrix<RGB> img;

public:
    ppm(){}
    ~ppm(){}
    int get_Nrows(){
        return(img.get_Nrows());
    }
    
    int get_Ncols(){
        return(img.get_Ncols());
        
    }
    RGB* operator[] (int i){return img[i];}
    
    void read(ifstream &a);
    void write();
    
};


#endif
