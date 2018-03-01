//Noah Branch
using namespace std;
#include "support.h"

const char ETX = 0x3;

void ppm::read(ifstream &fin) {
   
    //This function reads in the file info
    //and we read in the junk using the function given to us
    //we also assign and set the rows and columns
    int totpix;
    fin>>type;
    if(type != "P6"){cout<<"not P6"<<endl;}
    fin>>coll>>roww;
    totpix = coll * roww;
    img.assign(roww,coll);
    fin>>maxval;


    while (fin.get() != '\n') { /* skip */ }
    fin.read((char *)img.data(), 3*totpix);
        
}


void ppm::write(string &name) {
    
    //Write writes to a new file with a "_wmsg.ppm" extenstion
    string s = ".ppm";
    string newname = name.substr(0,name.find(s));
    newname += "_wmsg.ppm";
    ofstream newfile;
    newfile.open(newname.c_str());
    //we open the new file and output header information
    if(newfile.is_open()){
        newfile<<"P6"<<endl;
        newfile<<get_Ncols()<<" "<<get_Nrows()<<endl;
        newfile<<"255"<<endl;
        int totpix = get_Nrows()*get_Ncols();
        
        //Then we write using the write function
        newfile.write((char *)img.data(), 3*totpix);
        
    }
    newfile.close();
    
}

//below are the random numgen functions given that we use
void rnumgen::pdf(const vector<int> &v) {
    F.resize(v.size());
    partial_sum(v.begin(), v.end(), F.begin());
    transform(F.begin(), F.end(), F.begin(),    bind2nd(divides<float>(),*(F.end()-1)));
    
}
int rnumgen::rand() const {
    const float randnorm = RAND_MAX+1.0f;
    const float p = (float)std::rand()/randnorm;
    return upper_bound(F.begin(), F.end(), p) - F.begin();
    
}//notes
