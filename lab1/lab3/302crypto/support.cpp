using namespace std;
//#include<cstdio>
#include "support.h"

const char ETX = 0x3;

void ppm::read(ifstream &fin) {
    //matrix<RGB>vector;
    string P6;
    int row,col,val,totpix;
   // int R,G,B;
    fin>>P6;
    cout<<P6<<endl;
    if(P6 != "P6"){cout<<"not P6"<<endl;}
    fin>>col>>row;
    cout<<col<<" "<<row<<endl;
    totpix = col * row;
    img.assign(row,col);
    fin>>val;


    while (fin.get() != '\n') { /* skip */ }
   // int nrgb = 5;         // pixels per line
    /*int nrgb_read;        // pixels read per
    int npixels_read = 0; // pixels read in total
    unsigned char *rgb_ptr;       // data pointer
    unsigned char buf[3*nrgb];    // data buffer
    char text[80];        // text buffer*/
    //while (1) {
    fin.read((char *)img.data(), 3*totpix);
        
}
//	fin.close();






void ppm::write() {
    cout<<"P6"<<endl;
    cout<<"255"<<endl;
    cout<<get_Ncols()<<" "<<get_Nrows()<<endl;
    int count = 0;
    for(int i = 0; i < get_Nrows();i++ ){
        for(int j = 0; j < get_Ncols();j++){
            cout<<int(img[i][j].R)<<" ";
            cout<<int(img[i][j].G)<<" ";
            cout<<int(img[i][j].B)<<" ";
            cout<<"   ";
            count++;
        }
    cout<<endl;
    }
    cout<<count<<endl;
    cout<<get_Nrows()*get_Ncols()<<endl;
    
}
//notes
