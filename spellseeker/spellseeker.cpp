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
    if(r != 0){
        
        if(abs(tmp-grid[r-1][c])==1){
            
            dfs(r-1,c,key);
            
            //grid[r][c]=tmp;
            
        }
        
        if(c % 2 ==1){
            if(c != total_c-1 and abs(tmp - grid[r-1][c+1])==1){
                dfs(r-1,c+1,key);
                
            }
            if(abs(tmp - grid[r-1][c-1])==1){
                dfs(r-1,c-1,key);
            }
        }
    }
    if(r != total_r - 1){
        if(abs(tmp - grid[r+1][c])==1){
            dfs(r+1,c,key);
        }
        if(c % 2 ==0){
            if( c!= 0 and abs(tmp - grid[r +1][c-1])==1){
                dfs(r+1,c-1,key);
            }
            if(c != total_c-1 and abs(tmp - grid[r +1][c+1])==1){
               dfs(r+1,c+1,key);
            }
        }
        
    }
    if( c != 0 and abs(tmp - grid[r][c-1])==1){
        dfs(r,c-1,key);
        
    }
    if(c != total_c -1 and abs(tmp - grid[r][c+1])==1){
        dfs(r,c+1,key);
    }
    
    if(key[total_c * r +c] != 'X'){
        key[total_c * r +c] = 'O';
        
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
    map<string, Answer*>::iterator it;
    
    a ->key.resize(grid[r].size() * grid.size(),'-');
    a->key[total_c * r +c]='X';
    
    dfs(r,c,a->key);
    
    it = cache.find(a->key);
    
    if(it != cache.end()){
        return it -> second;
    }
    
    //a ->key.resize(grid[r].size() * grid.size(),'-');
    a->key[total_c * r +c]='X';
    a->r = r;
    a ->c = c;
    
    cout<<grid.size()<<endl;
    
    if(r != 0){
        
        if(abs(tmp-grid[r-1][c])==1){
            //rm grid[r-1][c]
            grid[r][c] = '-';
            b = Solve(r-1,c);
            if(b -> length > max){
                max = a -> length;
                a -> nexta = b;
            }
            grid[r][c]=tmp;
            
        }
        
        if(c % 2 ==1){
            if(c != total_c-1 and abs(tmp - grid[r-1][c+1])==1){
                //solve(grid[r-1][c+1])
                grid[r][c] = '-';
                b = Solve(r-1,c+1);
                if(b -> length > max){
                    max = a -> length;
                    a -> nexta = b;
                }
                grid[r][c]=tmp;
            }
            if(abs(tmp - grid[r-1][c-1])==1){
               //solve
                grid[r][c] = '-';
                b = Solve(r-1,c-1);
                if(b -> length > max){
                    max = a -> length;
                    a -> nexta = b;
                }
                grid[r][c]=tmp;
                
            }
        }
    }
    if(r != total_r - 1){
        if(abs(tmp - grid[r+1][c])==1){
            //solve and replace
            grid[r][c] = '-';
            b = Solve(r+1,c);
            if(b -> length > max){
                max = a -> length;
                a -> nexta = b;
            }
            grid[r][c]=tmp;
            
        }
        if(c % 2 ==0){
            if( c!= 0 and abs(tmp - grid[r +1][c-1])==1){
                //solve and replace
                grid[r][c] = '-';
                b = Solve(r+1,c-1);
                if(b -> length > max){
                    max = a -> length;
                    a -> nexta = b;
                }
                grid[r][c]=tmp;
                
            }
            if(c != total_c-1 and abs(tmp - grid[r +1][c+1])==1){
                //solve and replace
                grid[r][c] = '-';
                b = Solve(r+1,c+1);
                if(b -> length > max){
                    max = a -> length;
                    a -> nexta = b;
                }
                grid[r][c]=tmp;
                
            }
        }
           
    }
    if( c != 0 and abs(tmp - grid[r][c-1])==1){
        //solve/
        grid[r][c] = '-';
        b = Solve(r,c-1);
        if(b -> length > max){
            max = a -> length;
            a -> nexta = b;
        }
        grid[r][c]=tmp;
    }
    if(c != total_c -1 and abs(tmp - grid[r][c+1])==1){
        grid[r][c] = '-';
        b = Solve(r,c+1);
        if(b -> length > max){
            max = a -> length;
            a -> nexta = b;
        }
        grid[r][c]=tmp;
        
    }
    
    a -> length = max + 1;
    cache.insert(make_pair(key,a));
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
    int max=0;
    map<string, Answer*>::iterator it;
    string txtf = argv[1];
    ifstream txt;
    txt.open(argv[1]);
    
    cout<<argv[1]<<endl;
    string num;
    cout<<"jello"<<endl;
    while(getline(txt,num)){
        //cout<<"hello"<<endl;
        cout<<num<<endl;
        gridinfo -> grid.push_back(num);
    }
    
   // if(isalpha(gridinfo -> grid[0][0])){
    for(int i = 0;i < gridinfo -> grid.size();i++ ){
        for(int j = 0; j < gridinfo -> grid[0].size();j++){
            gridinfo -> Solve(i,j);
                //int u = gridinfo -> grid[i][j]-0;
                //gridinfo -> grid[i][j] = u;
                //cout<<u<<endl;
        }
    }
    for(it = gridinfo -> cache.begin();it != gridinfo->cache.end(); it++){
        if(it->second->length > max){
            max = it->second->length;
            
        }
    }
    
  
   // gridinfo ->Solve(0,0);
    txt.close();
    return 0;
}
