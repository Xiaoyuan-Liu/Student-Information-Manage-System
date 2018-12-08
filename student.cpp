#include"student.h"
const string student::getName(){
    return name;
}

const string student::getOrientation(){
    return orientation;
}

const int student::getId(){
    return id;
}

const int student::getAge(){
    return age;
}

const int student::getGPA(){
    return GPA;
}

const int student::getGPARank(){
    return GPARank;
}

bool student::operator ==(student stu){
    return (age==stu.age)
            && (name==stu.name)
            && (orientation==stu.orientation)
            &&(id == stu.id)
            &&(GPA==stu.GPA)
            &&(GPARank == stu.GPARank);
}

bool student::operator ==(string name){
    return this->name == name;
}

bool student::operator ==(int id){
    return this->id == id;
}
