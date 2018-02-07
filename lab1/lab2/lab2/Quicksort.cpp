//Noah Branch
//Lab1
//This lab puts names in alphabeticcal order
#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<stdlib.h>

// include header files needed
using namespace std;

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

//Quick select takes a name and put it where it would be if it were in alphabetical order
template <typename T>
void quickselect(std::vector<T> &A,int start, int k,int end) {
    int left = 0, right = (int)A.size()-1;
    int start1;
    while (1) {
		//The following code is taken form the quick sort algoritm 
			//see notes below.
        if(start == 0)
            start1=start+1;
        else
            start1 = start;
        
        int pivindex = rand()% end+start1;
        if(pivindex > end){
            pivindex = end;
        }
        swap(A[pivindex],A[end]);
        pivindex = end;
        
        int inc = start;int dec = end-1;
        while(inc < dec){
            while((A[inc] < A[pivindex] || A[inc]==A[pivindex]) && inc < end){
                inc ++;
            }
            while((A[dec] > A[pivindex] || A[dec]==A[pivindex]) && dec > start){
                dec--;
            }
            
            if((A[inc] > A[dec] || (A[dec]==A[pivindex] & A[inc]==A[pivindex])) && inc <= dec){
                person_t *uemp = new person_t;
                *uemp=A[inc];
                A[inc]=A[dec];
                A[dec]=*uemp;
                delete uemp;
                inc++;
                dec--;
                
                
            }
            
        }
        swap(A[pivindex],A[inc]);
        pivindex = inc;
       //once we know we have put the selectd word in the correct spot we return 
        
        if (pivindex == k)
            return;
        if (k < pivindex)
            end = pivindex-1;
        else
            start = pivindex+1;
        
    }
    
}


//This function sorts names pretty much
void quicksort( vector <person_t>&info,int start,int end) {
    if((end - start) < 1){
        return;
    }
	//If the size is 1 we return of it two then we compare directly and return
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
	//This is where I have set tet bounds for the random number genereator
    int start1;
    if(start == 0)
        start1=start+1;
    else
        start1 = start;
    
    int pivindex = rand()% end+start1;
    if(pivindex > end){
        pivindex = end;
    }
    swap(info[pivindex],info[end]);
    pivindex = end;
    
    int inc = start;int dec = end-1;
	//Below is the main algorithm we make sure the arrows donw cross int he while loop
    while(inc < dec){
		//If the dont cross we keep iterating until they do checking that the left number is less then the right
        while((info[inc] < info[pivindex] || info[inc]==info[pivindex]) && inc < end){
            inc ++;
        }
        while((info[dec] > info[pivindex] || info[dec]==info[pivindex]) && dec > start){
            dec--;
        }
		//This sis where we swap if the left is greater than the right
        if((info[inc] > info[dec] || (info[dec]==info[pivindex] && info[inc]==info[pivindex])) && inc <= dec){
            person_t *uemp = new person_t;
            *uemp=info[inc];
            info[inc]=info[dec];
            info[dec]=*uemp;
            delete uemp;
            inc++;
            dec--;
           
        }
        
    }
    
    swap(info[pivindex],info[inc]);
    pivindex = inc;
    
    quicksort(info, start, pivindex-1);
    quicksort(info, pivindex+1,start+(end-start));

   }

//Below are the comparative operators so we can compare whats in the class
bool operator==(const person_t&ln, const person_t &ln2){
       return ln.lastname == ln2.lastname && ln.firstname == ln2.firstname;

}

bool operator>=(const person_t&ln, const person_t &ln2){
    if(ln.lastname == ln2.lastname)
        return ln.firstname >= ln2.firstname;
    return ln.lastname >= ln2.lastname;
    
}
bool operator>(const person_t&ln, const person_t &ln2){
    if(ln.lastname == ln2.lastname)
        return ln.firstname > ln2.firstname;
    return ln.lastname > ln2.lastname;
}
bool operator<(const person_t&ln, const person_t &ln2){
    if(ln.lastname == ln2.lastname)
        return ln.firstname < ln2.firstname;
    return ln.lastname < ln2.lastname;

}

//Then we have the output operator so can output whats in the class
istream & operator>>(istream &in, person_t &r) {
    in >> r.firstname>>r.lastname>>r.phonenum;
    return in;
}

ostream & operator<<(ostream &out, const person_t &r) {
    out <<setw(20)<<left<< (r.lastname+" "+r.firstname)<<setw(1)<<right<<r.phonenum;
    return out;
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
    int a1,a2;
	//We have to chack that if the arguments are put int hen we have to do a different operation later
    if(argc > 2){
         a1 = atoi(argv[1]);
         a2 = atoi(argv[2]);
    }

    vector <person_t> A;
    person_t din;
    while (cin >> din){
        A.push_back(din);
    }
   int N = (int) A.size();
    
    int k0 = 0;
    int k1 = N - 1;
    	
		//If the Arguments are greater then 2 then that means their were values selected to be put in order. so we use quick select to place the beginning and end values for the range
      if(argc > 2){
        quickselect(A, k0, a1, k1);
        quickselect(A, k0, a2, k1);
        quicksort(A, a1, a2);
        quicksort(A, a1 ,a2);
 //other wise we are just sorting       
    }else{
        quicksort(A, k0, k1);
        quicksort(A, k0 ,k1);
    }
	//finally we print the new vector 
    printlist(A.begin(), A.end());
}

