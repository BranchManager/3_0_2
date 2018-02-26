
using namespace std;

#include "support.h"

void encode() {
  
}

void decode() {

}

int main(int argc, char *argv[]) {
    if(argc < 3){
        cout<< "usage: crypto -encode|decode image.ppm "<<endl;
    }
    
    string filein;
    ifstream fin;
    cout<<argv[1]<<endl;
    cout<<argv[2]<<endl;
    filein = argv[2];
    
  //if something not right,
    //print error message and exit
    fin.open(filein.c_str());
    ppm img;
    cout<<"hello world"<<endl;
    if(fin.is_open()) {
        img.read(fin);
    }else
        cout<<"file not open"<<endl;
    //img.write();//STILL NEED TO WRITE TO A FILE

  //if (encode) encode(fname, img);
  //else
  //if (decode) decode(fname, img);
}
