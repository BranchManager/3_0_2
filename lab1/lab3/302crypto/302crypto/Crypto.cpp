
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
    filein = argv[2];
    
  //if something not right,
    //print error message and exit

  ppm img;
    cout<<"hello world"<<endl;
  img.read(filein);
    img.write();//STILL NEED TO WRITE TO A FILE

  //if (encode) encode(fname, img);
  //else
  //if (decode) decode(fname, img);
}
