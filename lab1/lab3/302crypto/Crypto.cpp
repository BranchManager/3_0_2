
using namespace std;
//#include "support.cpp"
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
    string message;
    char a;
    int i=0,j=0,r,eight=0,rc,color=0,co=0;
    //pixel *pix;
    set_pixel_list(img,pixels);
    int total = img.get_Ncols()*img.get_Nrows();

    while(cin.get(a)){
        message.push_back(a);

    }
    message.push_back(ETX);

    for(int i = 0; i < message.size();i++){

        r = message[i]>>eight;
        r = r & 0x1;

        if (color == 0){
            img[pixels[i].coli][pixels[i].rowi].R = img[pixels[i].coli][pixels[i].rowi].R & 0xFE;
            img[pixels[i].coli][pixels[i].rowi].R |= r;
        }else if(color == 1){
            img[pixels[i].coli][pixels[i].rowi].G = img[pixels[i].coli][pixels[i].rowi].G & 0xFE;
            img[pixels[i].coli][pixels[i].rowi].G |= r;
        }else if(color == 2){
            img[pixels[i].coli][pixels[i].rowi].B = img[pixels[i].coli][pixels[i].rowi].B & 0xFE;
            img[pixels[i].coli][pixels[i].rowi].B |= r;
        }
        color++;
        if(color >= 3){
            color = 0;
        }

        eight++;
        if(eight >= 8){
            eight = 0;
        }

    }

                
            
}
   // if()
    
  


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
