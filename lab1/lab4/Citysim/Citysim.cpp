//Noah Branch Lab4

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<climits>
#include<limits>

using namespace std;
typedef enum { WHITE, BLACK } vcolor_t;
//The typedef above is used for colors in dijkstras

//the dtable below is used to keep the distances
template<typename T>
class dtable{
public:
    dtable(int i){buf = new T[(i*(i+1))/2];}
    ~dtable(){ delete[]buf;}
    T *operator[](int i){
        return &buf[(i*(i+1))/2];
    }
private:
    int N;
    T*buf;
    
};

//The city class contains all the information to the nodes
class city{
private:
    string name;
    string type;
    int zone;
    float latitude;
    float longitude;
    int population;
   
    
public:
    set<int>adj;
    
    string get_name(){return name;}
    string get_type(){return type;}
    int get_zone(){return zone;}
    float get_latitude(){ return latitude;}
    float get_longitude(){ return longitude;}
    int get_population(){return population;}
    
    
    friend istream& operator>>(istream &,city&);
    friend ostream& operator<<(ostream&, city&);
    
   
    
};

istream& operator>>( istream&file, city&info) {
    //This input sall the information into the file
    string junk,junk1,junk2;
    file>>junk;
    if(junk.find('#') != string::npos){
        
        getline(file,junk1);
        info.zone = '#';
       return file;
    }else{
        stringstream num(junk);
        num>>info.zone;
        file>>info.name>>info.type>>info.latitude>>info.longitude>>info.population;
       
        return file;
    }
   
}
//This outpus th eright info form the city node
ostream& operator<<(ostream&out, city& info){
    out<<info.zone<<" "<<info.name<<" "<<info.type<<" "<<info.latitude<<" "<<info.longitude<<endl;
    return out;
}

//Fucntion to convert to radians
float torad9(float val){
    float radian = val*(M_PI/180);
    
    return radian;
}
//This function determines the distance
int distance1(float lat1,float lat2, float long1, float long2){
    lat1=(torad9(lat1));
    lat2=(torad9(lat2));
    long1=(torad9(long1));
    long2=(torad9(long2));
    float delphi = fabs(lat2-lat1);
    float num = fabs(long2-long1);
    float a = pow(sin(delphi/2),2) + cos(lat1) * cos(lat2) * pow(sin(num/2),2);
    float distance = 3982*2*asin(sqrt(a));
    distance = 5.0*round(distance/5.0);
    return distance;
}
//This function creates the grapgh
void creat_citygrapgh(vector<city> &da_city, dtable<int> &s){
    
    //We get one city then iterate through allt he other cities to test adjacencey
    for(int i=0; i < (int)da_city.size(); i ++){
        set<int>used;
        used.clear();
        int ddis=0,b,a,diss2=0;
      
        
        for(int j =0; j < (int)da_city.size(); j++){
            
            if(i != j){
                //We test all the ReEGIONAL cities
                if(da_city[i].get_type() == "REGIONAL"){
                    
                    if(da_city[j].get_type()=="REGIONAL" && da_city[j].get_zone() == da_city[i].get_zone()){
                        
                        da_city[i].adj.insert(j);
                        da_city[j].adj.insert(i);
                    }else if(da_city[j].get_type()=="GATEWAY" && da_city[i].get_zone() == da_city[j].get_zone() ){
                        if(ddis == 0){
                            
                           
                            da_city[i].adj.insert(j);
                            da_city[j].adj.insert(i);
                            
                            ddis=distance1(da_city[i].get_latitude(),da_city[j].get_latitude(), da_city[i].get_longitude(), da_city[j].get_longitude());
                            b = j;
                            
                        }else if(ddis > distance1(da_city[i].get_latitude(),da_city[j].get_latitude(), da_city[i].get_longitude(), da_city[j].get_longitude())){
                            
                            
                            
                            da_city[i].adj.erase(b);
                            da_city[b].adj.erase(i);
                            da_city[i].adj.insert(j);
                            da_city[j].adj.insert(i);
                            
                            ddis = distance1(da_city[i].get_latitude(),da_city[j].get_latitude(), da_city[i].get_longitude(), da_city[j].get_longitude());
                            b = j;
                            
                        }
                        
                    }
                    //We test all the GATEWAY adjacency
                }else if(da_city[i].get_type() == "GATEWAY"){
                    if(da_city[j].get_type()=="GATEWAY" && da_city[j].get_zone() == da_city[i].get_zone()){
                        da_city[i].adj.insert(j);
                        da_city[j].adj.insert(i);
                        
                    }else if( da_city[j].get_type()=="GATEWAY" && da_city[j].get_zone() != da_city[i].get_zone()){
                        if(distance1(da_city[i].get_latitude(),da_city[j].get_latitude(), da_city[i].get_longitude(), da_city[j].get_longitude()) < 6000
                           && used.find(j) == used.end()){
                            if(diss2 == 0){
                                
                                da_city[i].adj.insert(j);
                                da_city[j].adj.insert(i);
                                
                                diss2=distance1(da_city[i].get_latitude(),da_city[j].get_latitude(), da_city[i].get_longitude(), da_city[j].get_longitude());
                                a = j;
                                
                            }else if(diss2 > distance1(da_city[i].get_latitude(),da_city[j].get_latitude(), da_city[i].get_longitude(), da_city[j].get_longitude())){
                                
                               
                                
                                da_city[i].adj.erase(a);
                                da_city[a].adj.erase(i);
                                da_city[i].adj.insert(j);
                                da_city[j].adj.insert(i);
                                
                                diss2 = distance1(da_city[i].get_latitude(),da_city[j].get_latitude(), da_city[i].get_longitude(), da_city[j].get_longitude());
                                a = j;
                                
                                
                            }
                        
                        }
                       
                    }
                }
            }
           
            if(da_city[j+1].get_zone() > da_city[j].get_zone()){
                used.insert(j);
                diss2=0;
            }
            
        }
    
    }
}

//This function reads in the information about each city
void read_cityinfo(vector<city> &da_city, map<string,int> &mp) {
    city cit;
    string hashtag;
    ifstream fin;
    int i=0;
    fin.open("citylist.txt");
    if(fin.is_open()){
        while(fin>>cit){
            
            
            if(cit.get_zone() != '#'){
                da_city.push_back(cit);
                mp[cit.get_name()]=i;
                i++;
            }
            
        }
    }
    
    fin.close();
    
}
//This writes out the information about the city pretty much
void write_cityinfo(vector<city>&da_city){
    ofstream fout;
    fout.open("cityinfo.txt");
    fout<<"CITY INFO (N=30):"<<endl<<endl;
    for(int i =0; i < (int)da_city.size();i++){
        fout<<setw(3)<<right<<i<<" "<<setw(20)<<left<<da_city[i].get_name()<<setw(12)<<left<<da_city[i].get_type()<<setw(2)<<left<<da_city[i].get_zone()<<
        setw(10)<<right<<da_city[i].get_population()<<" "<<
        fixed<<setprecision(2)<<setw(7)<<right<<da_city[i].get_latitude()<<
        fixed<<setprecision(2)<<setw(8)<<right<<da_city[i].get_longitude()<<endl;
    }
    fout.close();
}
//This function writes out the distancec between cities
void write_citydtable(dtable<int>&s,vector<city> &d){
    ofstream fout;
    fout.open("citydtable.txt");
    if(fout.is_open()){
        fout<<"DISTANCE TABLE:"<<endl;
        for(int i = 0;i < (int)d.size(); i++){
            for(int j = 0; j < i ; j++){
               
                string names = d[i].get_name() + " to " + d[j].get_name()+" ";
                fout<<setw(3)<< right << i <<" "
                <<setw(2*17+4)<< left <<setfill('.') << names
                <<setw(5)<< right << setfill(' ')<<s[i][j]<<" miles"
                <<endl
                <<setfill(' ');
                
            }
            fout<<endl;
        }
    }
    fout.close();
    
}
//This function writee out all the adjacent cities and their distances
void write_citygraph(vector<city>&da_city, dtable<int> &S){
    
    set<int>::iterator it;
    ofstream fout;
    fout.open("citygragh.txt");
    if(fout.is_open()){
        fout<<"CITY GRAPH:"<<endl;
        for(int i = 0; i < (int)da_city.size();i++){
            fout<<endl;
            fout<<setw(3)<<right<<i<<" "<<da_city[i].get_name()<<endl;
            for(it = da_city[i].adj.begin();it != da_city[i].adj.end();it++ ){
                fout<<setw(6)<<right<<*it<<" "<<da_city[*it].get_name()<<": ";
                
                if(i > *it){
                    fout<<S[i][*it]<<" miles"<<endl;
                }else{
                    fout<<S[*it][i]<<" miles"<<endl;
                }
            }
        }
    }
    fout.close();
    
}
//BFS determins the shortest rout e between nodes
void bfs_rout(vector<city> &da_city, map<string,int> &mp,vector<int> &vdist, vector<int> &vlink,dtable<int> &d,string &u){
    set<int>::iterator it;
     map<string,int>::iterator mit;
    string city1,city2;
    
    cout<<"Enter> ";
    while(cin>>city1>>city2){
    
        if(mp.find(city1)==mp.end()){
            mit=mp.upper_bound(city1);
            city1 = mit->first;
        }if(mp.find(city2)==mp.end()){
            mit=mp.upper_bound(city2);
            city2 = mit->first;
        }
        
        int source = mp[city1];
        int sink = mp[city2];
        
       
        
        vdist.assign(da_city.size(), INT_MAX);
        vlink.assign(da_city.size(), -1);
        vdist[source] = 0;
        vlink[source] = source;
        queue<int> Q;
        Q.push(source);
        while (!Q.empty()) {
            int i=Q.front();
            Q.pop();
            if (i==sink)
               
                break;
            
           
            for(it = da_city[i].adj.begin();it != da_city[i].adj.end(); it++){
                int j = *it;
                if (vdist[j] == INT_MAX) {
                    vdist[j] = vdist[i] + 1;
                    vlink[j] = i;
                    Q.push(j);
                    
                }
                
            }
            
        }
        while (!Q.empty())
            Q.pop();
        //////////////////////////////////////////
        if (vdist[sink] == INT_MAX) {
            cout << "No path from " << da_city[source].get_name()
            << " to " << da_city[sink].get_name() << "\n";
            return;
            
        }
        stack<int> S;
        for (int i=sink; i != source; i=vlink[i])
            S.push(i);
        S.push(source);
        if(u == "-show"){
            int m = 0;
            int y,b;
            int i = S.top();
            //S.pop();
            cout << setw(8)<<right<< m <<" "<<"miles :"<<setw(3)<<right<<i<<" "<< setw(23)<<left<<da_city[i].get_name()<<endl;// << " "
            y = S.top();
            
           
            while (S.size()>1) {
               // cout<<"T"<<endl;
                int i=S.top();
                S.pop();
               // int y = S.top();
                
                if(!S.empty()){
                    y = S.top();
                   // cout<<"M "<<m;
                    if(y > i){
                        m += d[y][i];
                        b = d[y][i];
                    } else{
                        m += d[i][y];
                        b = d[i][y];
                    }
                    
                }
                
                
                cout << setw(8)<<right<< m <<" "<<"miles :"<<setw(3)<<right<<y<<" "<< setw(23)<<left<<da_city[y].get_name() << " "
                <<setw(5)<< right<< b <<" miles"<<endl;//vdist[i] << "\n";
               
                
            }
            cout<<endl;
        }else{
            int m = 0;
            int y;//b;
            
            y = S.top();
        
            
            while (S.size()>1) {
                // cout<<"T"<<endl;
                int i=S.top();
                S.pop();
                // int y = S.top();
                
                if(!S.empty()){
                    y = S.top();
                    // cout<<"M "<<m;
                    if(y > i){
                        m += d[y][i];
                       // b = d[y][i];
                    } else{
                        m += d[i][y];
                        //b = d[i][y];
                    }
                    
                }
            }
            cout<<source<<" "<<da_city[source].get_name()<<" to"<<setw(3)<<right<<y<<" "<<da_city[y].get_name()<<" : "<<m<<" miles"<<endl<<endl;
        }
        cout<<"Enter> ";
    }
    
}

//dijkstra determined the shortest distance via shortest route route
void dijkstra_route(vector<city> &da_city, map<string,int> &mp,vector<int> &vdist, vector<int> &vlink,dtable<int> &d,string &u){
    vector<vcolor_t>vcolor;
    
    
    
    
    set<int>::iterator it;
    map<string,int>::iterator mit;
    string city1,city2;
    cout<<"Enter> ";
    //cin>>city1>>city2;
    
    while(cin>>city1>>city2){
        
        
        
        if(mp.find(city1)==mp.end()){
            mit=mp.upper_bound(city1);
            city1 = mit->first;
        }if(mp.find(city2)==mp.end()){
            mit=mp.upper_bound(city2);
            city2 = mit->first;
        }
        int source = mp[city1];
        int sink = mp[city2];
        
       
        vcolor.assign(da_city.size(), WHITE);
        vdist.assign(da_city.size(), numeric_limits<int>::max());
        vdist[source] = 0;
        vlink.assign(da_city.size(), -1);
        vlink[source] = source;
        while (1) {
           
            int i;
            int i_mindist = -1;
            int mindist = numeric_limits<int>::max();
            for (int i=0; i<(int)vcolor.size(); i++) {
                
                if (vcolor[i] == WHITE && mindist > vdist[i]) {
                    i_mindist = i;
                    mindist = vdist[i];
                    
                    
                }
                
            }
            
            if ((i = i_mindist) == -1)
                return;
            
            vcolor[i] = BLACK;
           
            if (i == sink){
                
                break;
            }
           
            
            for(it = da_city[i].adj.begin();it != da_city[i].adj.end(); it++){
                int j = *it;
                int wij = distance1(da_city[i].get_latitude(),da_city[*it].get_latitude(), da_city[i].get_longitude(), da_city[*it].get_longitude());
                if (vcolor[j] == WHITE) {
                    if (vdist[j] > vdist[i] + wij) {
                        vdist[j] = vdist[i] + wij;
                        vlink[j] = i;
                        
                        
                    }
                    
                }
                
            }
            
        }
       
        stack<int> S;
        for (int i=sink; i != source; i=vlink[i])
            S.push(i);
        S.push(source);
        if(u == "-show"){
            int m = 0;
            int y,b;
            int i = S.top();
            
            cout << setw(8)<<right<< m <<" "<<"miles :"<<setw(3)<<right<<i<<" "<< setw(23)<<left<<da_city[i].get_name()<<endl;// << " "
            y = S.top();
            
            while (S.size()>1) {
                
                int i=S.top();
                S.pop();
                
                
                if(!S.empty()){
                    y = S.top();
                    
                    if(y > i){
                        m += d[y][i];
                        b = d[y][i];
                    } else{
                        m += d[i][y];
                        b = d[i][y];
                    }
                    
                }
                
                
                cout << setw(8)<<right<< m <<" "<<"miles :"<<setw(3)<<right<<y<<" "<< setw(23)<<left<<da_city[y].get_name() << " "
                <<setw(5)<< right<< b <<" miles"<<endl;//vdist[i] << "\n";
                
                
            }
            
            cout<<endl;
            
        }else{
            int m = 0;
            int y;
            
            y = S.top();
           
            while (S.size()>1) {
                
                int i=S.top();
                S.pop();
                
                
                if(!S.empty()){
                    y = S.top();
                    
                    if(y > i){
                        m += d[y][i];
                      
                    } else{
                        m += d[i][y];
                       
                    }
                    
                }
            }
            cout<<source<<" "<<da_city[source].get_name()<<" to"<<setw(3)<<right<<y<<" "<<da_city[y].get_name()<<" : "<<m<<" miles"<<endl<<endl;
        }
        cout<<"Enter> ";
    }

}




//This function finds the distance between the nodes and put sthem in dtable
    void find_dis(vector<city> &da_city, dtable<int> &S){
        float dis;
     
        
        for(int i = 0;i < (int)da_city.size(); i++){
            for(int j = 0; j <= i ; j++){
                dis =  distance1(da_city[i].get_latitude(),da_city[j].get_latitude(), da_city[i].get_longitude(), da_city[j].get_longitude());
               
                S[i][j] = dis;
                
            }
        }
}



int main(int argc, char *argv[])
{
    vector<int>vlink;
    vector<int>vdist;
    vector<city>da_city;
    map<string,int>mp;
    string argv2;
  //Check cmd line arguments
    if(argc < 2){
        cout<<"usage: ./citysim [-write_info] [-write_dtable] [-write_graph] [-mode_bfs|mode_dijkstra [-randomseed] [-show]]"<<endl;
        return 0;
    }else if(argc > 2){
        argv2 = argv[2];
        if(argv2 != "-show"){
            cout<<"usage: ./citysim [-write_info] [-write_dtable] [-write_graph] [-mode_bfs|mode_dijkstra [-randomseed] [-show]]"<<endl;
            return 0;
        }
        
    }

    string argv1= argv[1];
 
    //read in info
    read_cityinfo(da_city,mp);
    //establish dtable and find the distance between nodes
    dtable<int>S((int)da_city.size());
    find_dis(da_city, S);
    
    //depending ont he arguments we do different things with the grapgh and if wrong out put we display erroe message
    if(argv1 == "-write_info"){
        write_cityinfo(da_city);
        
    }else if(argv1 == "-write_dtable"&& argc == 2){
        
        
        write_citydtable(S, da_city);
        
        
    }else if(argv1 == "-write_graph" && argc ==2){
        creat_citygrapgh(da_city, S);
        write_citygraph(da_city, S);
        
    }else if(argv1 == "-mode_bfs" && argc ==2){
        string n = "null";
        creat_citygrapgh(da_city, S);
        bfs_rout(da_city, mp,vdist,vlink,S,n);
        
    }else if(argv1 == "-mode_bfs" && argv2 == "-show"){
        creat_citygrapgh(da_city, S);
        bfs_rout(da_city, mp,vdist,vlink,S,argv2);
        
    } else if(argv1 == "-mode_dijkstra"&& argc == 2){
        string  n = "null";
        creat_citygrapgh(da_city, S);
        dijkstra_route(da_city, mp,vdist,vlink,S,n);
    }else if(argv1 == "-mode_dijkstra"&& argv2 == "-show"){
       // string  n = "null";
        creat_citygrapgh(da_city, S);
        dijkstra_route(da_city, mp,vdist,vlink,S,argv2);
    }else{
        cout<<"usage: ./citysim [-write_info] [-write_dtable] [-write_graph] [-mode_bfs|mode_dijkstra [-randomseed] [-show]]"<<endl;
        return 0;
    }
    

}
