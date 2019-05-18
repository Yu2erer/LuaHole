//
// Created by yu2erer on 2019/5/16.
//

#ifndef LUAHOLE_STUDENT_H
#define LUAHOLE_STUDENT_H

#include <iostream>
#include<string>

using namespace std;

class Student {
public:
    Student(int i);
    ~Student();
    string getName();
    void setName(string name);
    int getAge();
    void setAge(int age);
    void print();
private:
    string name;
    int age;
};

#endif //LUAHOLE_STUDENT_H
