#ifndef __PERSON_H__ 
#define __PERSON_H__

#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<map>

//WHAT'S NEEDED
using namespace std;

enum person_type  { UNKNOWN, FACULTY, STUDENT };
enum faculty_type { ASST_PROF, ASSOC_PROF, FULL_PROF };
enum student_type { FRESHMAN, SOPHOMORE, JUNIOR, SENIOR };

class person {
public:
    virtual bool operator<(const person&)const;
    
    friend ostream& operator <<(ostream &, const person & );
    person(){;}
    virtual ~person(){;}
protected:
    string name;
    string category;
    person_type person_ty;
    virtual void print_details()const=0;
    virtual void print_courses()const=0;
    
    
   
};

//class faculty //DEFINITION -- derived class
class faculty: public person{
public:
    bool operator <(const faculty&)const;
    faculty(string &n,string &f, vector<string> &t, faculty_type g);
    void add_course(vector<string> &t);
    void set_name(string &n);
    void set_type(string &f);
    
protected:
    faculty_type faculty_ty;
    
    map<string,float>course;
    void print_details()const;
    void print_courses()const;
};


//class student //DEFINITION -- derived class
class student: public person{
public:
    bool operator <(const student&)const;
    student(string &n, string &f,vector<string> &t,student_type s,vector<float> &gp);
    void add_course(vector<string> &t,vector<float> &gp);
    void set_name(string &n);
    void set_type(string &f);
protected:
    
    student_type student_ty;
    map<string,float>course;
    void print_details()const;
    void print_courses()const;
    
};

#endif
