//
//  support.hpp
//  maze
//
//  Created by noah Branch on 3/26/18.
//  Copyright © 2018 noah Branch. All rights reserved.
//

#ifndef support_hpp
#define support_hpp

#include <stdio.h>
#include <vector>

class dset {
    struct node {
        node() {
            rank=0,parent=-1;
            
        }
        int rank;
        int parent;
        
    };
    public:
    dset(int Nsets);
    int size() {
        return Nsets;
        
    }
    int add_set();
    int merge(int, int);
    int find(int);
    
    private:
    int Nsets;
    std::vector<node> S;
    
};
#endif /* support_hpp */
