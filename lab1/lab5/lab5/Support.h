//
//  Support.hpp
//  maze
//
//  Created by noah Branch on 3/26/18.
//  Copyright © 2018 noah Branch. All rights reserved.
//


#include<vector>
#include<stdio.h>
#include<iostream>
#include <stdlib.h>
using namespace std;

class maze{
    
private:
    int r;
    int c;
    //WE use a vector of vectos to represent walls
    //I have a vector to determine if each node is visited
    
    //I use a vector to store the path.
    vector<vector<bool> >walls;
    vector<pair<int,int> >adj;
    vector<bool>visited;
    bool done;
    
    vector<int>path;
    
    
    
    
public:
    
    void create_maze(int row, int col);
    void write_maze();
    void read_maze();
    bool solve_maze();
    bool solve_maze(int a, int b);
    //Actually solve does the computation for both the solve mazes so I didnt have to rewrite code
    bool acutallysolve(int a,int b);
    void write_path();
    void randperm(vector<pair<int,int> > &v);/*{
        for (int i=(int)v.size()-1; i>0; --i){
            swap(v[i], v[rand() % (i+1)]);
        }
    }*/
};
        /* Support_hpp */
