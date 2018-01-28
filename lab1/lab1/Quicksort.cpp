#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<stdlib.h>

// include header files needed
using namespace std;

// template <typename Tdata>
// void quickselect(...) { write this }

//template <typename Tdata>


class person_t {
public:
    person_t() { }
    
    // add operator< using lastname, firstname, phone number
    friend bool operator>=(const person_t&, const person_t&);
    friend bool operator>(const person_t&, const person_t &);
    friend bool operator<(const person_t&, const person_t &);
    friend bool operator==(const person_t&, const person_t &);
    friend istream & operator>>(istream &, person_t &);
    friend ostream & operator<<(ostream &, const person_t &);
    
private:
    string firstname;
    string lastname;
    string phonenum;
};
void printem(vector<int>&t);


void quicksort( vector <person_t>&info,int start,int end) {
    ///cout<<"start "<<start<<" end "<<end<<endl;
    if((end - start) < 1){
        ///cout<<"return 1 and "<<end-start<<endl;
        return;
    }
    if(end - start == 1){
        if(info[start+1]<info[start]){
            person_t *temp = new person_t;
            *temp = info[start+1];
            info[start+1]=info[start];
            info[start]=*temp;
            delete temp;
        }
        return;
            
    }
    ///cout<<" main execution "<<endl;
    int start1;
    if(start == 0)
        start1=start+1;
    else
        start1 = start;
    
    int pivindex = rand()% end+start1;
    if(pivindex > end){
        pivindex = end;
    }
    ///cout<<"hellend "<<endl;
    ///cout<<"at "<<pivindex<<" and "<<end<<endl;
    ///cout<<"pivindex "<<info[pivindex]<<" and end is "<<info[end]<<endl;

    swap(info[pivindex],info[end]);
    pivindex = end;
    
    int inc = start;int dec = end-1;
    
    while(inc < dec){
        while((info[inc] < info[pivindex] || info[inc]==info[pivindex]) && inc < end){
            //cout<<"info[inc] "<<info[inc]<< " < "<<info[pivindex]<<endl;
            inc ++;
        }
        //cout<<" BUT THIS info[inc] "<<info[inc]<< " > "<<info[pivindex]<<endl;
        while((info[dec] > info[pivindex] || info[dec]==info[pivindex]) && dec > start){
           // cout<<"info[dec] "<<info[dec]<< " > "<<info[pivindex]<<endl;
            dec--;
        }
        //cout<<"BUT THIS info[dec] "<<info[dec]<< " < "<<info[pivindex]<<endl;
        //if the arrows dont cross swap
        if(info[inc] > info[dec] && inc <= dec){
        //if((info[inc] > info[pivindex] || (info[dec]==info[pivindex] && info[inc]==info[pivindex])) && inc <= dec){
            person_t *uemp = new person_t;
            *uemp=info[inc];
            //cout<<"info "<<info[inc]<<" swapped w/ "<<info[dec]<<endl;
            info[inc]=info[dec];
            info[dec]=*uemp;
            delete uemp;
            inc++;
           // cout<<"joe"<<endl;
            dec--;
            //we need to check to mkae sure the pivot index isnt being swapped as well
       /* }else if(info[inc] == info[dec] && inc <= dec){
            inc++;
            dec--;*/
        }
        ///cout<<" inc is "<<inc<<" dec "<<dec<<endl;
    }
    //************swap pivot here with last element crossed***************!!!!!!!!!!!!!!!
    
    swap(info[pivindex],info[inc]);
    pivindex = inc;
    
   // printlist(info.begin(),info.end());
    //printem(info);
    ///////////////***********************/////////////////
   // for(int i = 0;i < info.size();i++){
     //   cout<<info[i]<<"billy "<<endl;
    //}
    quicksort(info, start, pivindex-1);
    ///////////////***********************//////////////////////
    //end-start+1====size;//so start+size-1
    quicksort(info, pivindex+1,start+(end-start));

    /*cout<<"bob"<<endl;
    if(info[0]<info[1])
        cout<<"info 1 smaller"<<info[0]<<"   "<<info[1];
    else
        cout<<"fix it "<<info[0]<<" "<<info[1]<<endl;*/
    // write this
}


bool operator==(const person_t&ln, const person_t &ln2){
    //cout<<"im tryin"<<endl;
    //if(ln.lastname == ln2.firstname)
    //    return ln.firstname > ln2.firstname;
    return ln.lastname == ln2.lastname && ln.firstname == ln2.firstname;

}

bool operator>=(const person_t&ln, const person_t &ln2){
    //cout<<"im tryin"<<endl;
    //if(ln.lastname == ln2.firstname)
    //    return ln.firstname > ln2.firstname;
    return ln.lastname >= ln2.lastname;
    
}
bool operator>(const person_t&ln, const person_t &ln2){
    //cout<<"im tryin"<<endl;
    if(ln.lastname == ln2.lastname)
        return ln.firstname > ln2.firstname;
    return ln.lastname > ln2.lastname;
}
bool operator<(const person_t&ln, const person_t &ln2){
   // cout<<"im tryin"<<endl;
    if(ln.lastname == ln2.lastname)
        return ln.firstname < ln2.firstname;
    return ln.lastname < ln2.lastname;

}

istream & operator>>(istream &in, person_t &r) {
    in >> r.firstname>>r.lastname>>r.phonenum;
    // write this to read person_t object data
    return in;
}

ostream & operator<<(ostream &out, const person_t &r) {
    // write this to write person_t object data
    out << r.lastname<<" "<<r.firstname<<setw(20)<<right<<r.phonenum;
    return out;
}


void printem(vector<person_t> &t){
    
    for(int i = 0;i < t.size();i++){
        cout<<t[i]<<" ";
    }
    cout<<endl;
}



template <typename T>
void printlist(T p1,T p2)
{
    while (p1 != p2){
        cout << *p1<<endl;
        ++p1;
    }
    
}



int main(int argc, char *argv[]) {
    // perform command-line check

    vector <person_t> A;
    //vector<int> A = {0,2,8,1,5,8,10,11,9,4,3,12,18,13,6,7};
    person_t din;
    while (cin >> din){
        //cin>>din;
        A.push_back(din);
    }
   /// printlist(A.begin(), A.end());
    //cin>>din;
        //A.push_back(din);
    int N = (int) A.size();
    
    int k0 = 0;
    int k1 = N - 1;
    
   // for (int i = 0; i < A.size();i++) {
     //   cout << A[i] << endl;
    //}
    // if given as command-line arguments,
    // update k0, k1 and apply quickselect
    // to partition A accordingly
    ///cout<<"k0  "<<k0<<" k1 "<<k1<<endl;
    
    quicksort(A, k0, k1);
   /// cout<<"hello";
    printlist(A.begin(), A.end());
}

