using namespace std;
//#include<cstdio>
#include "support.h"

const char ETX = 0x3;

void ppm::read(ifstream &fin) {
    //matrix<RGB>vector;
    string P6;
    int row,col,val;
    int R,G,B;
    fin>>P6;
    cout<<P6<<endl;
    if(P6 != "P6"){cout<<"not P6"<<endl;}
    fin>>col>>row;
    cout<<col<<" "<<row<<endl;
    img.assign(row,col);
    fin>>val;


    while (fin.get() != '\n') { /* skip */ }
    int nrgb = 5;         // pixels per line
    int nrgb_read;        // pixels read per
    int npixels_read = 0; // pixels read in total
    unsigned char *rgb_ptr;       // data pointer
    unsigned char buf[3*nrgb];    // data buffer
    char text[80];        // text buffer
    while (1) {
        fin.read((char *)buf, 3*nrgb);
        nrgb_read = fin.gcount()/3;
        if (nrgb_read == 0 && fin.eof())
            break;
        cout<<"sprintf stuf ";
        sprintf(text, "%07d ", npixels_read);
        cout<<"text ";
        cout << text;
        rgb_ptr = buf;
        cout<<"morw sprintf stuff ";
        for (int i=0; i<nrgb_read; i++) {
            cout << " ";
            //for (int j=0; j<3; j++) {

                sprintf(text, " %03u", *rgb_ptr++);
                R = static_cast<int>(text);
                cout << R;
                sprintf(text, " %03u", *rgb_ptr++);
                G = static_cast<int>(text);
                sprintf(text, " %03u", *rgb_ptr++);
                B = static_cast<int>(text);
           // }
        }
        cout << "\n";
        npixels_read += nrgb_read;
    }
}
//	fin.close();
    




void ppm::write() {
    cout<<"P6"<<endl;
    cout<<"255"<<endl;
    cout<<get_Ncols()<<" "<<get_Nrows()<<endl;
    for(int i = 0; i < get_Nrows();i++ ){
        for(int j = 0; j < get_Ncols();j++){
            cout<<img[i*get_Ncols()+j]->R<<" ";
            cout<<img[i*get_Ncols()+j]->G<<" ";
            cout<<img[i*get_Ncols()+j]->B<<" ";
        }
    cout<<endl;
    }
    
}
