// this ia a wierd change
//  main.cpp
//  spellseeker
//
//  Created by noah Branch on 11/23/17.
//  Copyright © 2017 noah Branch. All rights reserved.
//
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>
#include <cstdlib>

using namespace std;

class Answer {
    public:
        int length;
        int r;
        int c;
        string key;
        Answer *nexta;
};

class SpellSeeker {
    public:
        vector <string> grid;
        vector <int> gridnum;
        map <string, Answer *> cache;
        int total_r;
        int total_c;
        void dfs(int r,int c,string &key);
        Answer *Solve(int r, int c); //answer
   
};
/*************************************************************************************************8*/
/*************************************************************************************************8*/
void SpellSeeker::dfs(int r, int c, string &key){
    
    string b;
    int tmp=grid[r][c];
    if(key[total_c * r +c] != 'X') {
        key[total_c * r + c] = 'O';
    }
    //cout<<"da key is"<<key<<" at "<<r<<" "<<c<<" is "<<key[total_c * r +c]<<" "<<total_c * r +c<<" at "<<grid[r][c]<<endl;
    if(r != 0){
        
        if(abs(tmp-grid[r-1][c])==1){
            
            if(key[total_c * (r-1)+c]!='X' or key[total_c * (r-1)+c]!='O')
               dfs(r-1,c,key);
            
            //grid[r][c]=tmp;
            
        }
        
        if(c % 2 ==1){
            if(c != total_c-1 and abs(tmp - grid[r-1][c+1])==1){
                if(key[total_c * (r-1)+(c+1)]!='X' or key[total_c * (r-1)+(c+1)]!='O')
                    dfs(r-1,c+1,key);
                
            }
            if(abs(tmp - grid[r-1][c-1])==1){
                if(key[total_c * (r-1)+(c-1)]!='X' or key[total_c * (r-1)+(c-1)]!='O')
                    dfs(r-1,c-1,key);
            }
        }
    }
    if(r != total_r - 1){
        if(abs(tmp - grid[r+1][c])==1){
            if(key[total_c *(r+1)+c] == '-')
                dfs(r+1,c,key);
        }
        if(c % 2 ==0){
            if( c!= 0 and abs(tmp - grid[r +1][c-1])==1){
                if(key[total_c *(r+1)+(c-1)] == '-')
                    dfs(r+1,c-1,key);
            }
            if(c != total_c-1 and abs(tmp - grid[r +1][c+1])==1){
                if(key[total_c *(r+1)+(c+1)] == '-')
                    dfs(r+1,c+1,key);
            }
        }
        
    }
    if( c != 0 and abs(tmp - grid[r][c-1])==1){
        if(key[total_c *(r)+(c-1)] == '-')
            dfs(r,c-1,key);
        
    }
    if(c != total_c -1 and abs(tmp - grid[r][c+1])==1){
        if(key[total_c *(r)+(c+1)] == '-')
            dfs(r,c+1,key);
    }

        

    return;
    //key[total_c * r +c] = 'O';
}

/***************************************************************************************************************************/
/***************************************************************************************************************************/

Answer* SpellSeeker::Solve(int r, int c){
    //int *test;
    int max =0;
    char tmp = grid[r][c];
    Answer *a = new Answer;
    Answer *b = new Answer;
    string key;
    //string key(grid[r].size() * grid.size(),'-');
    map<string, Answer*>::iterator it;
    
    a-> key.resize(grid[r].size() * grid.size(),'-');
    a->key[total_c * r +c]='X';
    
    //debug
    
    key = a->key;
    
    
    dfs(r,c,key);
    
    
    a->key = key;
    it = cache.find(a->key);
    a->key = a->key;
    a->nexta = NULL;
    if(it != cache.end()){
        //cout<<"nigga we returnin"<<endl;
        return it -> second;
        
    }
    
    //a ->key.resize(grid[r].size() * grid.size(),'-');
   // a->key[total_c * r +c]='X';
    a->r = r;
    a ->c = c;
    
    //cout<<grid.size()<<endl;
    
    if(r != 0){
        
        if(abs(tmp-grid[r-1][c])==1){
            //degub statement
            //cout<<"1 we are subtracting "<<tmp<<" and "<<grid[r-1][c]<<endl;
            grid[r][c] = '-';
            b = Solve(r-1,c);
            if(b -> length > max){
                max = b -> length;
                a -> nexta = b;
               // cout<<"next is...."<< b -> r<<" "<<b -> c<<endl;
            }
            grid[r][c]=tmp;
            
        }
        
        if(c % 2 ==1){
            if(c != total_c-1 and abs(tmp - grid[r-1][c+1])==1){
                //degub statement
               // cout<<"2 we are subtracting "<<tmp<<" and "<<r-1<<" "<<c+1<<endl;

                grid[r][c] = '-';
                b = Solve(r-1,c+1);
                if(b -> length > max){
                    max = b -> length;
                    a -> nexta = b;
                   // cout<<"next is...."<< b -> r<<" "<<b -> c<<endl;
                    
                }
                grid[r][c]=tmp;
            }
            if(abs(tmp - grid[r-1][c-1])==1){
                //degub statement
                //cout<<"3 we are subtracting "<<tmp<<" and "<<r-1<<" "<<c-1<<endl;
                grid[r][c] = '-';
                b = Solve(r-1,c-1);
                if(b -> length > max){
                    max = b -> length;
                    a -> nexta = b;
                   // cout<<"next is...."<< b -> r<<" "<<b -> c<<endl;
                    
                }
                grid[r][c]=tmp;
                
            }
        }
    }
    if(r != total_r - 1){
        
        //cout<<abs(tmp - grid[r+1][c])<<endl;
        if(abs(tmp - grid[r+1][c])==1){
            //degub statement
           // cout<<"4 we are subtracting "<<tmp<<" and "<<r+1<<" "<<c<<endl;
            grid[r][c] = '-';
            b = Solve(r+1,c);
            if(b -> length > max){
                max = b -> length;
                a -> nexta = b;
              //  cout<<"next is...."<< b -> r<<" "<<b -> c<<endl;
                
            }
            grid[r][c]=tmp;
            
        }
        if(c % 2 ==0){
            if( c!= 0 and abs(tmp - grid[r +1][c-1])==1){
                //degub statement
               // cout<<"5 we are subtracting "<<tmp<<" and "<<r+1<<" "<<c-1<<endl;
                grid[r][c] = '-';
                b = Solve(r+1,c-1);
                if(b -> length > max){
                    max = b -> length;
                    a -> nexta = b;
                   // cout<<"next is...."<< b -> r<<" "<<b -> c<<endl;
                    
                }
                grid[r][c]=tmp;
                
            }
            if(c != total_c-1 and abs(tmp - grid[r +1][c+1])==1){
                //degub statement
               // cout<<"6 we are subtracting "<<tmp<<" and "<<r+1<<" "<<c+1<<endl;
                grid[r][c] = '-';
                b = Solve(r+1,c+1);
                if(b -> length > max){
                    max = b -> length;
                    a -> nexta = b;
                   // cout<<"next is...."<< b -> r<<" "<<b -> c<<endl;
                    
                }
                grid[r][c]=tmp;
                
            }
        }
    }
           
    
    if( c != 0 and abs(tmp - grid[r][c-1])==1){
        //degub statement
       // cout<<"7 we are subtracting "<<tmp<<" and "<<r<<" "<<c-1<<endl;
        grid[r][c] = '-';
        b = Solve(r,c-1);
        if(b -> length > max){
            max = b -> length;
            a -> nexta = b;
           // cout<<"next is...."<< b -> r<<" "<<b -> c<<endl;
            
        }
        grid[r][c]=tmp;
    }
    if(c != total_c -1 and abs(tmp - grid[r][c+1])==1){
        //degub statement
       // cout<<"8 we are subtracting "<<tmp<<" and "<<r<<" "<<c+1<<endl;
        grid[r][c] = '-';
        b = Solve(r,c+1);
        if(b -> length > max){
            max = b -> length;
            a -> nexta = b;
        }
        grid[r][c]=tmp;
        
    }
    
    a -> length = max + 1;
   // cout<<"length for "<<grid[r][c]<<" at coordinates "<<r<<" "<<c<<" is "<<a -> length<<endl;
    cache.insert(make_pair(a->key,a));
    return a;
        
}
   /* if(c % 2 == 0){
        it = cache.find("qqq");
        if(tmp == grid[r+1][c+1]-1  ){
            Solve(r+1,c+1);// tmp == grid[r+1][grid[c-1]){
            
        }
        
    }
    
    
    test = &test2;
    
    return test;
}*/


int main(int argc,char **argv) {
    // insert code here...
    SpellSeeker *gridinfo = new SpellSeeker;
    Answer *next = new Answer;
    int max=0;
    map<string, Answer*>::iterator it;
    /*string txtf = argv[1];
    ifstream txt;
    txt.open(argv[1]);
    
   // cout<<argv[1]<<endl;*/
    string num;
    
    while(getline(cin,num)){
        
       // cout<<num<<endl;
        gridinfo -> grid.push_back(num);
    }
    gridinfo -> total_r = gridinfo->grid.size();
    gridinfo -> total_c = gridinfo->grid[0].size();
   // if(isalpha(gridinfo -> grid[0][0])){
    for(int i = 0;i < gridinfo -> grid.size();i++ ){
        for(int j = 0; j < gridinfo -> grid[0].size();j++){
           // cout<<"we doin OUR THANG"<<endl;
            gridinfo -> Solve(i,j);
                //int u = gridinfo -> grid[i][j]-0;
                //gridinfo -> grid[i][j] = u;
                //cout<<u<<endl;
        }
    }
    //cout<<"********************************************************";
    string key;
    for(it = gridinfo -> cache.begin();it != gridinfo->cache.end(); it++){
        if(it->second->length > max){
            max = it->second->length;
            key = it->first;
            
        }
    }
    for(int i = 0; i < gridinfo ->grid.size();i++){
        for(int j = 0; j < gridinfo ->grid[0].size();j++){
            cout<<gridinfo -> grid[i][j];
            
        }
        cout<<endl;
    }
    cout<<"PATH"<<endl;
   // cout<<key<<endl;
   // cout<<"2222222222222"<<endl;
    it = gridinfo -> cache.find(key);
    //cout<<it->second->length;
    next = it->second;
    //cout<<"we made it!!!"<<endl;
    while(next != NULL){
        //cout<<next -> c % 2<<" now we in "<<endl;
        cout<<next -> r<<" "<<next->c<<endl;//<<gridinfo->grid[next->r][next ->c]<<endl;
        next = next -> nexta;
    }
  
   // gridinfo ->Solve(0,0);
    txt.close();
    return 0;
}
