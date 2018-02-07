// include header files needed
#include<iostream>
#include<iomanip>
#include<vector>
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

// template <typename T>
template <class T>
class slist {
private:
    struct node {
        node() { data = T(); next = NULL; }
        // add node(const T &key) { write this }
        node(const T &key){data = key; next = this;}
        // add overloaded operator< code
        
        T data;
        node *next;
    };
    
    // add class sptr { write this for node data }
    
public:
class iterator {
    public:
        iterator() { p = NULL; }
        T & operator*() { return p->data; }
        iterator & operator++() { p = p->next; return *this; }
        bool operator!=(const iterator & rhs) const { return p != rhs.p; }
        
        friend class slist<T>;
        
    private:
        iterator(node *n_p) { p = n_p; }
        node *p;
    };
    
public:
    slist();
    ~slist();
    
    void push_back(const T &);
    void sort();
    
    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(NULL); }
    
private:
    node *head;
    node *tail;
    int size = 0;
    
};

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
slist<T>::slist() {
    head = new node();
    tail = head;
}

template <typename T>
slist<T>::~slist() {
    while (head->next != NULL) {
        node *p = head->next;
        head->next = p->next;
        delete p;
    }
    delete head;
    
    head = NULL;
    tail = NULL;
}

template <typename T>
void slist<T>::push_back(const T &din) {
    tail->next = new node(din);
    tail = tail->next;
    size++;
}

template <typename T>
void slist<T>::sort() {
    
    node *p = head -> next;
    node *pn;
    slist<T>::iterator it;
    vector<node*>Ap(size,NULL);
    cout<<"size "<<size<<endl;
    int i = 0;
    while(p != tail){
        Ap[i] = p;
        //cout<<p->data<<endl;
        pn = p->next;
        
        p = pn;
        i++;
        cout<<"billh"<<endl;
    }
    Ap[size-1]=tail;
    
    for(int i = 0; i < size;i++){
        cout<<Ap[i]->data<<endl;
        
    }
    std::sort(Ap.begin()->data,Ap.end()->data);
    
    for(int i = 0; i < size;i++){
        cout<<Ap[i]->data<<endl;
        
    }
    // determine number of list elements
    // set up smart pointer array called Ap
    // apply std::sort(Ap.begin(), Ap.end())
    // use sorted Ap array to relink list
    
    
    
    
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
    // copy command-line check from Quicksort.cpp
    
    slist<person_t> A;
    
    person_t din;
    while (cin >> din)
        A.push_back(din);
    
    A.sort();
    cout<<"end"<<endl;
    
   // printlist(A.begin(), A.end());
}
