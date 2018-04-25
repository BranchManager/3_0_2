//#include //WHAT'S NEEDED
using namespace std;

#include "Person.h"
#include "Sptrsort.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
      cerr<<"BAD cmd line args"<<endl;
	return 0;
  }
    ifstream fin;
    fin.open(argv[1]);

  person *n_person;
  vector<person *> person_list;
    vector<person *>student_list;
    vector<person *>faculty_list;

 // person_enum
    person_type person_typ = UNKNOWN;

  int line = 0;
    float new_gp;
  size_t iL, iR;
  string input;
  string name;
  string category;
  vector<string> course;
  vector<float> gp;
    if(fin.is_open()){
      while (getline(fin, input)) {
        line++;

        if ((iL = input.find('<')) == string::npos) {
          continue;

        } else if (input.compare(iL,9,"<faculty>") == 0) {
          person_typ = FACULTY;
          course.clear();
          gp.clear();

        } else if (input.compare(iL,10,"</faculty>") == 0) {
          faculty_type faculty_typ;
            //faculty_type_e
          if (category.compare("Assistant Professor") == 0)
            faculty_typ = ASST_PROF;
          else if (category.compare("Associate Professor") == 0)
            faculty_typ = ASSOC_PROF;
          else if (category.compare("Full Professor") == 0)
            faculty_typ = FULL_PROF;

          //CODE FOR ADDING FACULTY PERSON TO DATABAS
            n_person = new faculty(name,category,course,faculty_typ); //new student;
            faculty_list.push_back(n_person);
          person_list.push_back(n_person);

          person_typ = UNKNOWN;
          continue;

        } else if (input.compare(iL,9,"<student>") == 0) {
          person_typ = STUDENT;
          course.clear();
          gp.clear();

        } else if (input.compare(iL,10,"</student>") == 0) {
          student_type student_typ;

          if (category.compare("Freshman") == 0)
            student_typ = FRESHMAN;
          else if (category.compare("Sophomore") == 0)
            student_typ = SOPHOMORE;
          else if (category.compare("Junior") == 0)
            student_typ = JUNIOR;
          else if (category.compare("Senior") == 0)
            student_typ = SENIOR;

          //CODE FOR ADDING STUDENT PERSON TO DATABASE
           // cout<<"before "<<name<<endl;
            n_person = new student(name,category,course,student_typ,gp);
            //n_person->add_course(course);
            student_list.push_back(n_person);
          person_list.push_back(n_person);

          person_typ = UNKNOWN;
          continue;

        } else if (input.compare(iL,5,"<name") == 0) {
          iL = input.find("=\"", iL);
          iR = input.find("\"/>", iL+2);
          name = input.substr(iL+2,iR-(iL+2));
          //  cout<<name<<endl;
        } else if (input.compare(iL,10,"<category=") == 0) {
          iL = input.find("=\"", iL);
          iR = input.find("\"/>", iL+2);
          category = input.substr(iL+2,iR-(iL+2));

        } else if (input.compare(iL,7,"<course") == 0) {
          iL = input.find("=\"", iL);
          iR = input.find("\"", iL+2);
          course.push_back(input.substr(iL+2,iR-(iL+2)));////////////////////////////////////

          iL = iR;
          if (person_typ == FACULTY) {
            iR = input.find("/>", iL+1);
          } else if (person_typ == STUDENT) {
            iL = input.find("gp=\"", iL);
            iR = input.find("\"/>", iL+4);

            stringstream ss;
            ss << input.substr(iL+4,iR-(iL+3));
            ss >> new_gp;
            gp.push_back(new_gp);
          }
        }
      }
    }
    fin.close();
    sptrsort(person_list);
    sptrsort(student_list);
    sptrsort(faculty_list);
    cout<<"command: person"<<endl;
    cout<<"command: faculty"<<endl;
    cout<<"command: student"<<endl<<endl;
    cout<<"command> ";
    
    string info;
    while(cin>>info){
        
      // MODIFY TO INFINITE LOOP ASKING FOR PERSON,
      // FACULTY OR STUDENT MODE FOR SORTING
        if(info == "faculty"){
            for (int i=0; i<(int)faculty_list.size(); i++){
                cout << *faculty_list[i] << "\n";
            }
        }
        if(info == "student"){
            for (int i=0; i<(int)student_list.size(); i++){
                cout << *student_list[i] << "\n";
            }
        }
        if(info == "person"){
            for (int i=0; i<(int)person_list.size(); i++){
             cout << *person_list[i] << "\n";
            }
        }
    }
  // RELEASE DYNAMICALLY ALLOACTED MEMORY
}
