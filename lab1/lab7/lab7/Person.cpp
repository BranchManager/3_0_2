//#include // WHAT'S NEEDED
//using namespace std;

#include "Person.h"
#include "Sptrsort.h"
#include <iomanip>
//PERSON CLASS MEMBER FUNCTION IMPLEMENTATION
bool person:: operator <(const person &person1)const{
   // cout<<"check person"<<endl;
    if(person_ty == person1.person_ty){
        return name < person1.name;
    }
    return person_ty < person1.person_ty;
}

ostream& operator<<(ostream &out, const person &p){
    
    
   // cout<<"Category"<<p.category;
    p.print_details();
    p.print_courses();
    return out;
    
}


//STUDENT CLASS MEMBER FUNCTION IMPLEMENTATION
bool student::operator <(const student &person1)const{
  //  cout<<"check student"<<endl;
    if(student_ty == person1.student_ty){
        
        return name < person1.name;
    }
    return student_ty < person1.student_ty;
}
student::student(string &n, string &f, vector<string> &t, student_type s, vector<float> &gp){
    //we set everything in the student class here
    person_ty = STUDENT;
    student_ty = s;
    name = n; category = f;
    add_course(t,gp);
}
void student::print_courses()const{
    map<string,float>::const_iterator it,endit;
    float avg=0;
    float sum=0;
    int i=0;
    for(it = course.begin();it != course.end();it++,i++){
        sum = it->second+sum;
        avg = (sum)/(i+1);
        cout.clear();
        cout<<setw(12)<<right<<"Course: "<<setw(25)<<left<<it->first<<" "<<fixed<<setprecision(2)<< it->second<<" "<<avg<<endl;
        
    }
    
}
void student::print_details()const{
    cout<<right<<setw(12)<<"Name: "<<name<<endl;
    cout<<right<<setw(12)<<"Category: "<<category<<endl;

}

void student::add_course(vector<string> &t, vector<float> &gp){
    
    for(int i = 0; i < (int)t.size(); i++){
        course.insert(make_pair(t[i], gp[i]));
    }
   
}



//FACULTY CLASS MEMBER FUNCTION IMPLEMENTATION
bool faculty::operator <(const faculty &person1)const{
    if(faculty_ty == person1.faculty_ty){
        return name < person1.name;
    }
    return faculty_ty < person1.faculty_ty;
}
void faculty::add_course(vector<string> &t){
    for(int i = 0; i < (int)t.size(); i++){
        // courses.push_back(t[i]);
        course.insert(make_pair(t[i],0));
    }
}

faculty::faculty(string &n, string &f,vector<string> &t, faculty_type g){
    person_ty = FACULTY;
    faculty_ty = g;
    name = n; category = f;
    add_course(t);
    
}

void faculty::print_courses()const{
    map<string,float>::const_iterator it,endit;
    
    for(it = course.begin();it != course.end();it++){
       // avg = (avg+it->second)/2;
        cout<<right<<setw(12)<<"Course: "<<it->first<<endl;
    }
    
}
void faculty::print_details()const{
    cout<<right<<setw(12)<<"Name: "<<name<<endl;
    cout<<right<<setw(12)<<"Category: "<<category<<endl;
}
