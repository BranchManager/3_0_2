//Noah Branch
//This lab basically sorts names using and array of smart pointers
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
            node(const T &key){data = key; next = NULL;}
            // add overloaded operator< code
            friend bool operator<(const node&l, const node&r){return (l.data < r.data);}
            
            T data;
            node *next;
        };
    
        // add class sptr { write this for node data }
    class sptr {
        public:
            sptr(node *_ptr=NULL) { ptr = _ptr; }
            bool operator< (const sptr &rhs) const { return *ptr < *rhs.ptr;}
            operator node * () const { return ptr; }
        private:
            node *ptr;
            
    };
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
    
    // determine number of list elements and set up smart pointer array called Ap
    //among declaring initial p for first for loop
    node *p = head -> next;
    slist<T>::iterator it;
    vector<sptr>Ap(size,NULL);
   //we make sure the array of pointrs point ro the nodes here
    for(int i = 0; i<size;i ++){
        Ap[i] = p;
    
        p=p->next;
    }
    /*for(int i = 0; i<size;i ++){
        cout<<(*Ap[i]).data<<endl;
       // p=p->next;
    }*/
    
    // apply std::sort(Ap.begin(), Ap.end())
    std::sort(Ap.begin(),Ap.end());
    
    // use sorted Ap array to relink list
    p = head;
    for(int i = 0; i < size; i ++){
        p->next=Ap[i];
        p=p->next;
    }
    tail = p;
    p->next = NULL;
    
    p = head;
    
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
    if(argc > 1){
        cout<<"usage: ./sort_slist < file.txt"<<endl;
        return 0;
        
    }
    
    slist<person_t> A;
    
    person_t din;
    while (cin >> din)
        A.push_back(din);
    
    A.sort();
   
    
    printlist(A.begin(), A.end());
}
