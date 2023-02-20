//
// Created by cbh on 2022/10/19.
//

#ifndef BRIDGE_NETLINK_H
#define BRIDGE_NETLINK_H

#endif //BRIDGE_NETLINK_H
#include<iostream>
#include<string>
using namespace std;
typedef  struct{
    uint64_t RxPackets;
    uint64_t TxPackets;
    uint64_t RxBytes;
    uint64_t TxBytes;
    uint64_t RxErrors;
    uint64_t TxErrors;
    uint64_t RxDropped;
    uint64_t TxDropped;
    uint64_t Multicast;
    uint64_t Collisions;
    uint64_t RxLengthErrors;
    uint64_t RxOverErrors;
    uint64_t RxCrcErrors;
    uint64_t RxFrameErrors;
    uint64_t RxFifoErrors;
    uint64_t RxMissedErrors;
    uint64_t TxAbortedErrors;
    uint64_t TxCarrierErrors;
    uint64_t TxFifoErrors;
    uint64_t TxHeartbeatErrors;
    uint64_t TxWindowErrors;
    uint64_t RxCompressed;
    uint64_t TxCompressed;
}LinkStatistics64;
typedef struct {
    int Index;
    int MTU;
    int TxQlen; // Transmit Queue Length
    string Name;
    char *HardwareAddr;
    unsigned int Flags;
    int ParentIndex; // index of the parent link device
    int MasterIndex; // must be the index of a bridge
    void* Namespace; // nil | NsPid | NsFd
}LinkAttrs;
typedef struct {
    LinkAttrs attrs;
}Bridge;

class NetNs{
public:
    void d();
    void set();
    string path();
    uintptr_t Fd();
    void close();

};
void LinkByName();