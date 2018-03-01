//Noah Branch
using namespace std;

#include "support.h"
void set_pixel_list(ppm &img, vector<pixel> &pixels){
    //This function basically gets all the even pairs of variables below
    //and puts them into a vector pixel list
    vector<int>da_histogram;
    for(int i=0;i < img.get_Nrows();i++){
        for(int j = 0;j<img.get_Ncols();j++){
            if(i%2==0 && j%2==0){
                pixel pix(i,j);
                pixels.push_back(pix);


                
            }
        }
        
    }
    //Help with this part
    //This function below is where we add the randomness
    int color, color1;
    //To keep the size of the histogram managable, extract the four most significant bits from each color byte and combine these half-bytes to obtain a 12-bit color integer.
    for(int j = 0; j < (int)pixels.size(); j++) {
        pixel u = pixels[j];
        color = (img[u.rowi][u.coli].R) >> 4 << 8 | (img[u.rowi][u.coli].G) >> 4 << 4 | (img[u.rowi][u.coli].B) >> 4;
        
        //support of 4k pixels
        if(j % 2 == 0) {
            int r24 = color << 12 | color1;
            
            da_histogram.push_back(r24);
        }
        color1 = color;
    }
    
    rnumgen RNG(0);
    RNG.pdf(da_histogram);
    
    
    for(int i = (int)pixels.size() - 1; i > 0; --i) {
        swap(pixels[i], pixels[(RNG.rand())]);
    }
}

//This is where we encode the message into the string
void encode(string &filein, ppm &img) {
    ifstream fin;
    //open file
    fin.open(filein.c_str());
    if(fin.is_open()) {
        img.read(fin);
    }else{
        cout<<"file not open"<<endl;
        return;
    }
    vector<pixel> pixels;
    //set the pixel vector so we know which pixels to change
    set_pixel_list(img, pixels);
    pixel u = pixels[0];
    //int max_pixel = pixels.size();
    int counter = 0;
    int p = 0;
    char c,y;
    //check to see if we get the eof characher
    while(!cin.eof() && p < (int)pixels.size()) {
        cin.get(y);
        if(cin.eof()) {
            y = 0x3;
        }
        c = y;
        //This is where we do the bit manipulation
        for(int i = 0; i < 8; ++i) {
            u = pixels[p];
            
            counter++;
                if (counter == 1){
                    img[u.rowi][u.coli].R &= 0xFE;
                    img[u.rowi][u.coli].R |= ((c >> i) & 0x1);
               
                }if (counter == 2){
                    img[u.rowi][u.coli].G &= 0xFE;
                    img[u.rowi][u.coli].G |= ((c >> i) & 0x1);
                   
                }if(counter == 3){
                    img[u.rowi][u.coli].B &= 0xFE;
                    img[u.rowi][u.coli].B |= ((c >> i) & 0x1);
                   
                }
            
                //The counter basically keeps rotation of the RGB
                p++;
                if(counter == 3)
                    counter = 0;
                }
        }
    
    //was told to use this have yet to see it actually in implimentation
    //but we make sure we dont exeed the pixels to manipulate
    if(p == (int)pixels.size()) {
        cout << endl << "Error: pixel_list exhausted!" << endl;
    }
    //close file
    fin.close();
    
}

//this basically does the same thing as encode just in reverse order
//so see encode for help
void decode(string &filein,ppm &img) {
    
    ifstream fin;
    fin.open(filein.c_str());
    if(fin.is_open()) {
        img.read(fin);
        
    }else{
        cout<<"file not open"<<endl;
        return;
    }
    vector<pixel> pixels;
   
    set_pixel_list(img, pixels);
    int i = 0;
    int counter = 0;
    pixel p = pixels[i];
    char c = 0;
    
    while(c != ETX) {
        c = 0;
        char temp = 0;
        for(int j = 0; j < 8; j++) {
            p = pixels[i];
            counter++;
            if(counter == 1){
                temp = (img[p.rowi][p.coli].R & 0x1);
                c |= (temp << j);
            }
            if(counter == 2){
                temp = (img[p.rowi][p.coli].G & 0x1);
                c |= (temp << j);
            }
                    
            if(counter == 3){
                temp = (img[p.rowi][p.coli].B & 0x1);
                c |= (temp << j);
                
            }
            
            if(counter == 3)
                counter = 0;
            
            i++;
        }
        cout.put(c);
       
        if(c == ETX){
            break;
        }
    }
    fin.close();
    return;
    
}

int main(int argc, char *argv[]) {
    //make sure we have the correct number of arguments
    if(argc != 3){
        cout<< "usage: crypto -encode|decode image.ppm "<<endl;
        return 0;
    }
    
    string filein;
    ifstream fin;
    string arg2 = argv[1];
    string file=argv[2];
    filein = argv[2];
    
    //fin.open(filein.c_str());
    ppm img;
    
    //if the 2nd argument was encode we encode if decode we decode
    if(arg2=="-encode"){
        encode(filein,img);
        img.write(file);
    }else if(arg2 == "-decode"){
        decode(filein,img);
        
    }else{
        cout<< "usage: crypto -encode|decode image.ppm "<<endl;
        
    }
  
    
}
