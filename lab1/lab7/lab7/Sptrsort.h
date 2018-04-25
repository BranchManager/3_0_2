//WRITE THIS BASED ON SMART POINTER CLASS
#include<algorithm>

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
    vector<person*> temp = t;
    for(int i = 0; i < temp.size();i++){
        sp[i] = temp[i];
    }
    
    sort(sp.begin(),sp.end());
    
    
    for(int i = 0;i < sp.size();i++){
       // t[i]=sp[i];
        cout<<*sp[i]<<endl;
    }
    cout<<"ENNNNNNNNNNNNNND"<<endl;
}
