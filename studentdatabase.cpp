#include<algorithm>
using namespace std;
#include"studentdatabase.h"
const student studentDatabase::getStudent(int index){
    return stu[index];
}

const int studentDatabase::getSize(){
    return stu.size();
}

void studentDatabase::addStudent(){
    student *tmp = new student();
    stu.push_back(*tmp);
    delete tmp;
}

bool studentDatabase::addStudent(student stu){
    if(findStudent(stu)==-1)return false;
    this->stu.push_back(stu);
    sortByGPA();
}

//bool studentDatabase::addStudent(student stu);
bool studentDatabase::deleteStudent(int index){
    stu.erase(stu.begin()+index);
}

bool studentDatabase::deleteStudent(student stu){
    int index = findStudent(stu);
    if(index==-1)return false;
    else{
        this->stu.erase(this->stu.begin() + index);
        return true;
    }
}

const int studentDatabase::findStudent(student stu){
    for(int i = 0;i < this->stu.size();i++){
        if(this->stu[i]==stu)
            return i;
    }
    return -1;
}

const int studentDatabase::findStudent(string name){
    for(int i = 0;i<this->stu.size();i++){
        if(this->stu[i]==name)
            return i;
    }
    return -1;
}

const int studentDatabase::findStudent(int id){
    for(int i = 0;i<this->stu.size();i++){
        if(this->stu[i]==id)
            return i;
    }
    return -1;
}

bool studentDatabase::clear(){
    stu.clear();
}

bool sortCmp(student s1, student s2){
    return s1.getGPA()<s2.getGPA();
}

void studentDatabase::sortByGPA(){
    sort(stu.begin(),stu.end(),sortCmp);
}
