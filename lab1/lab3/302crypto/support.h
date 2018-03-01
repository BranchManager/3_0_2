//Noah Branch
#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include<cstddef>
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<math.h>
#include<cstdlib>
#include<functional>
#include<numeric>
#include<algorithm>
typedef unsigned char uchar;
extern const char ETX;

template <typename T>
class matrix { 
	public:

    matrix(){
        buf = NULL;
    }
    void assign(int n_rows,int n_cols){
    
        Nrows = n_rows;
        Ncols = n_cols;
        buf = new T [Nrows*Ncols];

    }

    ~matrix() {
        delete[] buf;
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
    pixel(int r, int c){rowi=r;coli=c;}
    int rowi;
    int coli;
    
};

struct RGB {
    RGB( ){R=0;  G = 0; B = 0; }

    uchar R,G,B;
};
class ppm {
private:
    matrix<RGB> img;
    string type;
    int coll,roww;
    int maxval;
    
    
public:
    
    ppm(){
        type = "P6";
        coll = 0;
        roww = 1;
        maxval = 255;
    }
    
    int get_Nrows(){
        return(roww);
    }
    
    int get_Ncols(){
        return(coll);
        
    }
    RGB* operator[] (int i){return img[i];}
    
    void read(ifstream &a);
    void write(string &a);
    
};

class rnumgen {
    public:
    rnumgen(int seed=0){ srand(seed); }
    void pdf(const std::vector<int> &);
    int rand() const;
    
    private:
    std::vector<float> F;
    
};

#endif
