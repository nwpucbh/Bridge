//
// Created by cbh on 2022/10/18.
//
#include<iostream>
#include<string>
using namespace std;
typedef struct  {
    string Type; //`json:"type,omitempty"`
}IPAM;
typedef struct {
    string *Nameservers; //`json:"nameservers,omitempty'
    string Domain; //`json:"domain,omitempty"`
    string *Search; // `json:"search,omitempty"`
    string *Options; //`json:"options,omitempty"`

}DNS;
typedef struct {
    string Name;
    string Mac;
    string Sandbox;
}INTERFACE;

typedef struct {
    string CNIVersion; //json:"cniVersion,omitempty
    string Name; // `json:"name,omitempty"`
    string Type; // `json:"type,omitempty"`
//    map[string]bool Capabilities; //`json:"capabilities,omitempty"`
    IPAM IPAM;         //`json:"ipam,omitempty"`
    DNS DNS;            // `json:"dns"`
//    map[string]interface{} RawPrevResult ;// `json:"prevResult,omitempty"`
}NetConf_type;

typedef struct {
    char *IP;
    char *Mask;
}IPNet;
typedef struct {
    IPNet Dst;
    char *GW;
}Route;

typedef struct {
    IPNet IP;
    char *Gateway;
    Route *Routes;
}IPConfig;


typedef struct {
    string print;
    IPConfig *IP4;
    DNS DNS;
}Result;

