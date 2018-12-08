#ifndef STUDENTDATABASE_H
#define STUDENTDATABASE_H
#include<vector>
using namespace std;
#include"student.h"
class studentDatabase{
private:
    vector<student> stu;
public:
    const student getStudent(int index);
    const int getSize();
    void addStudent();
    bool addStudent(student stu);
    //bool addStudent(student stu);
    bool deleteStudent(int index);
    bool deleteStudent(student stu);
    const int findStudent(student stu);
    const int findStudent(string name);
    const int findStudent(int id);
    void sortByGPA();
    bool clear();
};

#endif // STUDENTDATABASE_H
