//
// Created by Huy Duong on 9/12/22.
//
#include <set>
#include <string>
#include <iostream>
using namespace std;

int main(){
    set<string> temp = {"BIGIN", "END"};
    if (temp.find("BIGIN") != temp.end()){
        cout<< "TRUE";
    }
    else cout<<"FALSE";
}