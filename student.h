#ifndef STUDENT_H
#define STUDENT_H
#include<string>
using namespace std;

class student{
private:
    string name;
    string orientation;
    int id;
    int age;
    int GPA;
    int GPARank;
    int phoneNumber;//unused here
public:
    student():name(""),orientation(""),id(-1),age(-1),GPA(-1),GPARank(-1){}
    student(string name,string orientation,int id,int age,int GPA,int GPARank):
        name(name),orientation(orientation),id(id),age(age),GPARank(GPARank){}
    const string getName();
    const string getOrientation();
    const int getId();
    const int getAge();
    const int getGPA();
    const int getGPARank();
    bool operator ==(student stu);
    bool operator ==(string name);
    bool operator ==(int id);
};

#endif // STUDENT_H
