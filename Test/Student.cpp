//
// Created by yu2erer on 2019/5/16.
//

#include "Student.h"


Student::Student() : name("default"), age(21) {
    cout << "Student Contructor called" << endl;
}
Student::~Student() {
    cout << "Student Destructor called" << endl;
}

string Student::getName() {
    return name;
}

void Student::setName(string name) {
    this->name = name;
}

int Student::getAge() {
    return age;
}

void Student::setAge(int age) {
    this->age = age;
}

void Student::print() {
    cout << "My name is: " << name << ", and my age is " << age << endl;
}