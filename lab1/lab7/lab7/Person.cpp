//#include // WHAT'S NEEDED
//using namespace std;

#include "Person.h"

//PERSON CLASS MEMBER FUNCTION IMPLEMENTATION
bool operator <(const person &person1, const person &person2){
    if(person1.person_ty == person2.person_ty){
        return person1.name < person2.name;
    }
    return person1.person_ty < person2.person_ty;
}

ostream& operator<<(ostream &out, const person &p){
    
    
   // cout<<"Category"<<p.category;
    p.print_details();
    p.print_courses();
    return cout<<"";
    
}
//FACULTY CLASS MEMBER FUNCTION IMPLEMENTATION

//STUDENT CLASS MEMBER FUNCTION IMPLEMENTATION
bool operator <(const student &person1, const student &person2){
    if(person1.student_ty == person2.student_ty){
        return person1.name < person2.name;
    }
    return person1.student_ty < person2.student_ty;
}
student::student(string &n, string &f, vector<string> &t, student_type s, vector<float> &gp){
    person_ty = STUDENT;
    student_ty = s;
    name = n; category = f;
    add_course(t,gp);
   // cout<<"here "<<name;
}
void student::print_courses()const{
    // cout<<endl<<"zee courses print here:: ";
    map<string,float>::const_iterator it,endit;
    it = course.begin();
    float avg=it->second;
    //endit = course.end();
    for(it;it != course.end();it++){
        avg = (avg+it->second)/2;
        cout<<"Course: "<<it->first<<" "<<it->second<<" "<<avg<<endl;
    }
    
}
void student::print_details()const{
    cout<<"Name: "<<name<<endl;
    cout<<"Category: "<<category<<endl;

}

void student::add_course(vector<string> &t, vector<float> &gp){
    //courses = t;
    //cout<<"sizes "<<t.size()<<endl;
    for(int i = 0; i < t.size(); i++){
       // courses.push_back(t[i]);
        course.insert(make_pair(t[i], gp[i]));
    }
   // for(int i = 0; i < courses.size(); i++){cout<<courses[i]<<endl;
        
   // }
}
bool operator <(const faculty &person1, const faculty &person2){
    if(person1.faculty_ty == person2.faculty_ty){
        return person1.name < person2.name;
    }
    return person1.faculty_ty < person2.faculty_ty;
}
void faculty::add_course(vector<string> &t){
    for(int i = 0; i < t.size(); i++){
        courses.push_back(t[i]);
    }
    
}

faculty::faculty(string &n, string &f,vector<string> &t, faculty_type g){
    person_ty = FACULTY;
    faculty_ty = g;
    name = n; category = f;
    add_course(t);
    
}

void faculty::print_courses()const{
   // cout<<"courses print here: ";
    for(int i = 0;i < courses.size();i++){
        
        cout<<"Course: "<<courses[i]<<endl;
    }
}
void faculty::print_details()const{
    cout<<"Name: "<<name<<endl;
    cout<<"Category: "<<category;
}
