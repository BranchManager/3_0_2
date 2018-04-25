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
    friend bool operator<(const person&, const person&);
    friend ostream& operator <<(ostream &, const person & );
    person(){;}
    
protected:
    string name;
    string category;
    person_type person_ty;
    virtual void print_details()const=0;
    virtual void print_courses()const=0;
    //printcourses
    
   // vector<string>*courses;
    
};//DEFINITION -- base class

//class faculty //DEFINITION -- derived class
class faculty: public person{
public:
    friend bool operator <(const faculty&, const faculty&);
    faculty(string &n,string &f, vector<string> &t, faculty_type g);
    void add_course(vector<string> &t);
    void set_name(string &n);
    void set_type(string &f);
    
protected:
   // string category;
    faculty_type faculty_ty;
    vector<string>courses;
    void print_details()const;
    void print_courses()const;
};

class student: public person{
public:
    friend bool operator <(const student&, const student&);
    student(string &n, string &f,vector<string> &t,student_type s,vector<float> &gp);
    void add_course(vector<string> &t,vector<float> &gp);
    void set_name(string &n);
    void set_type(string &f);
protected:
    //string category;
    student_type student_ty;
    map<string,float>course;
    void print_details()const;
    void print_courses()const;
    
}; //DEFINITION -- derived class

#endif
