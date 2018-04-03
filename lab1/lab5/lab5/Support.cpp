//
//  Support.cpp
//  maze
//
//  Created by noah Branch on 3/26/18.
//  Copyright © 2018 noah Branch. All rights reserved.
//

#include "Support.h"
#include "Dset.h"

//This function basically creates a maze

void maze::create_maze(int row,int col){
    r = row;
    c = col;
    //We set the vector for the wall here
    vector<bool>w(4,true);
    walls.resize(row*col,w);
    
    dset d(1);
    //We go through and make all the nodes adjacent to each other
    for(int i = 0; i < row;i++){
        for(int j = 0; j < col; j++){
            
            d.add_set();
            if(i-1 >= 0){ adj.push_back( make_pair(i*col+j,(i-1)*col+j));}
            if(j-1 >= 0){ adj.push_back( make_pair(i*col+j, i*col+(j-1)));}
            if(i+1 < row){ adj.push_back( make_pair(i*col+j, (i+1)*col+j));}
            if(j+1 < col){ adj.push_back( make_pair(i*col+j, i*col+(j+1)));}
        }
    }
   
    //We randomly shuffle the vector paros to determine which wall to break.
    randperm(adj);
    for(int i = 0; i < adj.size(); i++){
        if(d.find(adj[i].first) !=  d.find(adj[i].second)){
            if((adj[i].first/col == adj[i].second/col) && adj[i].first-1  == adj[i].second){
                
                walls[adj[i].first][1] = false;
                walls[adj[i].second][3] = false;
                
                d.merge(adj[i].first,adj[i].second);
            }if((adj[i].first/col == adj[i].second/col) && adj[i].first+1 == adj[i].second){
               
                walls[adj[i].first][3] = false;
                walls[adj[i].second][1] = false;
               
                d.merge(adj[i].first,adj[i].second);
            }if((adj[i].first%col == adj[i].second%col) && adj[i].first+col ==  adj[i].second){
               
                walls[adj[i].first][2] = false;
                walls[adj[i].second][0] = false;
                d.merge(adj[i].first,adj[i].second);
               
                
            }if((adj[i].first%col == adj[i].second%col) && adj[i].first - col == adj[i].second){
                
                walls[adj[i].first][0] = false;
                walls[adj[i].second][2] = false;
                d.merge(adj[i].first,adj[i].second);
               
                
            }
        }
    }
    
}
void maze::write_maze(){
    cout<<"MAZE"<<" "<<r<<" "<<c<<endl;
    for(int i = 0;i < r; i++){
        for(int j = 0; j < c;j++){
            
            for(int p = 0; p < 4;p++){
                
                if(walls[i*c+j][p]){
                    cout<<i*c+j<<" ";
                    cout<<p<<endl;
                }
                
            }
        }
    }
}
void maze::read_maze(){
    //Read maze basically reads in the maze
    int block1, block2,row,col;
    done = false;
    string maze;
    cin>>maze>>row>>col;
    r = row;
    c = col;
    //We hav no walls at first
    vector<bool>w(4,false);
    walls.resize(r*c,w);
    
    visited.resize(r*c,false);
    //it reads in a block and a wall and adds the wall to that node
    while(cin>>block1>>block2){
    
        walls[block1][block2] = true;
       
       
        if(block2 == 0 && block1-c > 0){
           
            walls[block1 - c][2] = true;
            
        }else if(block2 == 1 && (((block1-1)/c) == block1/c && block1-1>0)){
            
            walls[block1 - 1][3] = true;
            
            
        }else if(block2 == 2 && ((block1+c)%c == block1%c && block1+c < col)){
           
            walls[block1 + c][0] = true;
           
            
        }else if(block2 == 3 && ((block1+1)/c) == block1/c){
            
            walls[block1 + 1][1] = true;
           
            
        }
    }
    
}

//Actually solve does the solving for both parts recurisvely
//I t bacially starts at a and ends at b
bool maze::acutallysolve(int a, int b){
    path.push_back(a);
    visited[a]=true;
   //make sure we dont keep returning in this function
    if(done){
        return true;
    }
    //if a = b on recursive call we are done pretty mcuj
    if(a == b){
      
        done = true;
        return true;
    }else{
        //otherwise we go though the adjacent vectos in search of a path to the surrounding nodes
        for(int i = 0; i < 4 && !done;i++){
    
                if(i == 0 && (walls[a][i] == false && !visited[a-c])){
                    acutallysolve( a - c, b);
                }else if(i == 1 && (walls[a][i] == false  && !visited[a-1])){
                    acutallysolve(a-1, b);
                }else if(i == 2 && (walls[a][i] == false && !visited[a+c])){
                    acutallysolve(a + c, b);
                }else if(i == 3 && (walls[a][i] == false && !visited[a+1])){
                    acutallysolve(a+1, b);
                    
                }
                
          
            
            
            
        }
        //If we ge to this point then that means we dis not find a path this route so we remove the last vector added
        if(!done){
            path.pop_back();
        }
        
        return true;
    }
}

bool maze::solve_maze(){
    return acutallysolve(0,r*c-1);
    
}

bool maze::solve_maze(int a, int b){
    return acutallysolve(a,b);
}

void maze::write_path(){
    cout<<"PATH "<<" "<<r<<" "<<c<<endl;
    
    for(int i = 0; i < (int)path.size();i++){
        cout<<path[i]<<endl;
    }
}








