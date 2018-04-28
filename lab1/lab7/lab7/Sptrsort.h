//WRITE THIS BASED ON SMART POINTER CLASS
#include<algorithm>
#include"Person.h"
template <typename T>
class sptr {
    public:
    sptr(T *_ptr=NULL) {
        ptr = _ptr;
        
    }
    bool operator< (const sptr &rhs) const {
        return *ptr < *rhs.ptr;
    }
    
    operator T * () const { return ptr; }
    
    
    private:
    T *ptr;
    
};
template<typename T>
void sptrsort(vector<T *> &t){
    vector<sptr<T> >sp(t.size(),NULL);
    //vector<person*> temp = t;
    for(int i = 0; i < t.size();i++){
       sp[i] = t[i];
    }
    sort(sp.begin(),sp.end());
    
    
    for(int i = 0;i < sp.size();i++){
        t[i]=sp[i];
        
    }
   /* for(int i = 0; i < sp.size();i++){
        cout<<*t[i]<<endl;
        
    }*/
   
}
