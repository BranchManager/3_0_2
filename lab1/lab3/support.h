#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <...>

typedef unsigned char uchar;
extern const char ETX;

template <typename T>
class matrix { 
	public:

		void assign(int nrows,int ncols){
		//	buf = new char[size];
			Nrows = n_Nrows;
			Ncols = n_Ncols;
			buf = new T [Nrows*Ncols]; 

		}

		~matrix() { 
	       delete [] buf;
	    }

		int get_Nrows() const { return Nrows; }
		int get_Ncols() const { return Ncols; }
		T * operator[] (int i) { return &buf[i*Ncols]; }

		T *data(){
			return *buf==NULL;

		}
  private:
		int Nrows, Ncols;
		T *buf;
};

struct pixel { write this };

struct RGB { write this };

class ppm { write this };

#endifp
