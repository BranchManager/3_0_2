
using namespace std;

#include "support.h"
void set_pixel_list(ppm &img, vector<pixel> &pixels){
    pixel *pix;
    
    for(int i=0;i < img.get_Nrows();i++){
        for(int j = 0;img.get_Ncols();j++){
            if(i%2==0 && j%2==0){
                pix = new pixel;
                pix->rowi=i;
                pix->rowi=j;
                pixels.push_back(*pix);
                
            }
        }
        
    }
}
void encode(ifstream &fin, ppm &img) {
    vector<pixel>pixels;
    char a;
    int r;
    //pixel *pix;
    set_pixel_list(img,pixels);
    int total = img.get_Ncols()*img.get_Nrows();
    while(cin.get(a)){
        for(int i=0; i < img.get_Nrows();i++){
            for(int j = 0; j<get_Ncols();j++){
            r = a >> i;
            r = a & 0x1;
                
            
        }
    }
    
  
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
    string arg2 = argv[2];
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
    if(arg2=="-encode"){
        encode(fin,img);
    }
  //if (encode) encode(fname, img);
  //else
  //if (decode) decode(fname, img);
}
