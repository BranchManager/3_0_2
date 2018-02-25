using namespace std;
//#include<cstdio>
#include "support.h"

const char ETX = 0x3;

void ppm::read(string file) {
    //matrix<RGB>vector;
    string P6;
    int row,col,val;
    int R,G,B;
    ifstream fin;
    fin.open(file);
    if(fin.is_open()){
        fin>>P6;
        if(P6 != "P6"){cout<<"not P6"<<endl;}
        fin>>col>>row;
        img.assign(row,col);
        fin>>val;
        if(val < 0 or val > 255){cout<<"to large or to small"<<endl;}
        for(int i = 0; i < get_Nrows();i++ ){
            for(int j = 0; j < get_Ncols();j++){
                fin>>R>>G>>B;
                img[i*get_Ncols()+j]->R=R;
                img[i*get_Ncols()+j]->G=G;
                img[i*get_Ncols()+j]->B=B;
            }
        }
        
    }        /*while(fin>>R>>G>>B){
            img[i*get_Ncols()+j]->R=R;
            img[i*get_Ncols()+j]->G=G;
            img[i*get_Ncols()+j]->B=B;
            i++;
            
            if(i == get_Ncols()){
                i = 0;
                j++;
            }
            
        }*/
//	fin.close();
    


}

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
