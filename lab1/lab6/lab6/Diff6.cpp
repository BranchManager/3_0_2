//Noah Branch
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
#include <iomanip>
//line numbers corresponding to first file
//a letter for add delete cange
//line # for second file
using namespace std;

template<typename T>
class matrix {
  // see handout from class or make your own
    //Matrix class for the cost and links
    
public:
    matrix(){
        buf = NULL;
    }
    void assign(int n_rows,int n_cols){
        Nrows = n_rows;
        Ncols = n_cols;
        buf = new T [Nrows*Ncols];
    }
    ~matrix() {
        delete[] buf;
    }

    int get_Nrows() const { return Nrows; }
    int get_Ncols() const { return Ncols; }
    
    T * operator[] (int i) { return &buf[i*Ncols];}
    T *data(){
        return buf;
    }
    
    private:
    int Nrows, Ncols;
    T *buf;
};

class LCS {
  public:
    LCS();
    void text1_push_back(string add1);
    void text2_push_back(string add2);
	void compute_alignment();
	void report_difference();

  private:
    int m,n;
    void report_difference(int a, int b);
	// support functions
    
    stack<pair<int,int> >trace;
    stack<int>tra;
    // text1 buffer
    vector<string>text1;
    // text2 buffer
    vector<string>text2;
    matrix<int>cost;
    matrix<int>link;
    
    int (LCS::*DEL)(string);        // function ptr
    int (LCS::*INS)(string);        // function ptr
    int (LCS::*SUB)(string, string);  // function ptr
    
    int DEL2(string c) { return 1; }
    int INS2(string c) { return 1; }
    int SUB2(string c1, string c2) { return c1==c2 ? 0 : m+n; }
    
    int DELcost(string c) { return (*this.*DEL)(c); }
    int INScost(string c) { return (*this.*INS)(c); }
    int SUBcost(string c1, string c2) {return (*this.*SUB)(c1,c2);}
};

LCS::LCS(){
    
    DEL = &LCS::DEL2;
    INS = &LCS::INS2;
    SUB = &LCS::SUB2;
}
//Pushes strings back onto the text1 buffer and the following function does the same for the text2 buffer
void LCS::text1_push_back(string add1){
    text1.push_back(add1);
    
}

void LCS::text2_push_back(string add2){
    text2.push_back(add2);
    
}
//This function computes the alighnment matrix cost and links
void LCS::compute_alignment(){
    text1.insert(text1.begin(),"-");
   text2.insert(text2.begin(),"-");
    m = (int)text1.size()-1;
    n = (int)text2.size()-1;
    cost.assign(m+1,n+1);
    link.assign(m+1,n+1);
    cost[0][0] = 0;
    link[0][0] = 0;
    for (int i=1; i<=m; i++) {
        cost[i][0] = cost[i-1][0] + DELcost(text1[i]);
        link[i][0] = 1;//DELmove;
        
    }
    for (int j=1; j<=n; j++) {
        cost[0][j] = cost[0][j-1] + INScost(text2[j]);
        link[0][j] = 2;//INSmove;
        
    }
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            cost[i][j] = cost[i-1][j-1] + SUBcost(text1[i], text2[j]);
            link[i][j] = 4;
            int inscost = cost[i][j-1] + INScost(text2[j]);
            if (inscost < cost[i][j]) {
                cost[i][j] = inscost;
                link[i][j] = 2;//INSmove;
                
            }
            int delcost = cost[i-1][j] + DELcost(text1[i]);
            if (delcost < cost[i][j]) {
                cost[i][j] = delcost;
                link[i][j] = 1;//DELmove;
                
            }
            
        }
        
    }
    //out put cost and link matrix for debugging purposes
   /* cout<<"link: "<<endl;
    for(int i=0; i <(int)text1.size();i++){
        for(int j=0; j < (int)text2.size(); j++){
            cout<<setw(4)<<link[i][j];
        }
        cout<<endl;
    }
    cout<<"cost: "<<endl;
    for(int i=0; i <(int)text1.size();i++){
        for(int j=0; j < (int)text2.size(); j++){
            cout<<setw(4)<<cost[i][j];

        }
        cout<<endl;
    }*/
}
void LCS::report_difference(int i, int j){
    //This function created the trace stack using the links so that we may follow the links from bottom to top
    
    if(i==0 && j==0)
        return;
    else{
        if(link[i][j] == 4){
           
            tra.push(4);
            report_difference(i-1,j-1);
            
        }
        if(link[i][j] == 2){
            tra.push(2);
            report_difference(i,j-1);
        }
        if(link[i][j] == 1){
            tra.push(1);
            report_difference(i-1,j);
        }
    }
}
void LCS::report_difference(){

    //This function does all the hard stuff and prints the information in the format required
    int i = (int)text1.size()-1;
    int j = (int)text2.size()-1;
    
    int filecounter = 0,file2counter =0;
    int ins=0,del=0;
    int cur;
    report_difference(i, j);
   
    //This function does  the main operations on the stack while it is not empty
    while(!tra.empty()){
        cur = tra.top();
        tra.pop();
   //the if and while statements below are just keeping track of inserts and deletions and also what line of hte file we are onin certain vectors
        if(cur == 4){
            filecounter++;
            file2counter++;
        }
        if(cur == 2)
            ins = 1;
        if(cur == 1)
            del = 1;
        
        while(!tra.empty() && tra.top() != 4){
            if(tra.top()==2)
                ins++;
            if(tra.top()==1)
                del++;
            tra.pop();
        }
            //Below is how we determine the output of different lines or multiple lines if needed
        if(del > 0){
            if(del ==1)
                cout<<filecounter + del;
            else
                cout<<filecounter+1<<","<<filecounter+del;
            
            if(ins > 0){
                cout<<"c";
                if(ins == 1){
                    cout<<file2counter+ins;
                }else{
                    cout<<file2counter+1<<","<<file2counter+ins;
                }
            }else{
                cout<<"d"<<file2counter;
            }
            cout<<endl;
        }else if(ins > 0){
            cout<<filecounter<<"a";
            if(ins==1)
                cout<<file2counter+ins;
            else
                cout<<file2counter+1<<","<<file2counter+ins;
            cout<<endl;
        }
        
        int temp = filecounter;
        int temp1 = file2counter;
        int d = del;
        int i = ins;
        
        
        if(del > 0){
            while(del != 0){
                filecounter++;
                cout<<"< "<<text1[filecounter]<<endl;
               
                del--;
            }
            if(ins > 0){
                cout<<"---"<<endl;
            }
        }
        if(ins > 0){
            while(ins !=0){
                file2counter++;
                cout<< "> "<<text2[file2counter]<<endl;
               
                ins--;
            }
        }
        filecounter = temp + d;
        file2counter = temp1 + i;
        //finally we iterate the number of files needed after the process
    }
    
}


int main(int argc, char *argv[])
{
  // check two input files are specified on command line
    string file1,file2,line;
    ifstream ifile,ifile2;
    if(argc != 3){
        cerr<<"wrong cmd line args"<<endl;
    }

  LCS lcs;  // instantiate your "lcs based diff" object
   
  // read the text from file1 into the lcs.text1 buffer
    file1=argv[1]; file2=argv[2];
    ifstream fin,fin2;
    fin.open(argv[1]);
    if(fin.is_open()){
        while(getline(fin,line)){
            lcs.text1_push_back(line);
        }
        fin.close();
        
    }else{
        cerr<<"Bad file 1"<<endl;
    }
    
    
    // read the text from file2 into the lcs.text2 buffer
    fin2.open(argv[2]);
    if(fin2.is_open()){
        while(getline(fin2,line)){
            lcs.text2_push_back(line);
        }
        fin2.close();
        
    }else{
        cerr<<"Bad file 2"<<endl;
    }
    
  lcs.compute_alignment();
  lcs.report_difference();
}
