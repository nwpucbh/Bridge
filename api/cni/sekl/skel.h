//
// Created by cbh on 2022/10/18.
//
#include<iostream>
#include<string>
using namespace std;

typedef struct {
    string ContainerID;
    string Netns;
    string IfName;
    string Args;
    string Path;
    char *StdinData;
}CmdArgs ;

void GetNS()  {

}