#include <iostream>
#include <fstream>
#include "xpack/json.h"

namespace skel{
#include "api/cni/sekl/skel.h"
}
namespace types{
#include "api/cni/types/types.h"
}
namespace ns{
#include "api/cni/ns/ns.h"
}
namespace netlink{
#include "api/netlink/netlink.h"
}
namespace ip{
#include "api/ip/ip.h"
}
using namespace std;

const string defaultBrName = "cni0";
typedef struct {
    types::NetConf_type netConf_type;
    string BrName; //`json:"bridge"`
    bool IsGW; //`json:"isGateway"`
    bool IsDefaultGW; //`json:"isDefaultGateway"`
    bool ForceAddress; //`json:"forceAddress"`
    bool IPMasq; //`json:"ipMasq"`
    int MTU; //`json:"mtu"`
    bool HairpinMode;//`json:"hairpinMode"`
}NetConf;

struct stu{
    string name;
    int age;
XPACK(O(name, age));
};


void loadNetConf(char *bytes, NetConf *n,string &cniVersion,string &err){
    ifstream infile("D:\\Bridge\\data.txt");
    string data;
    string s;
    stu s1;
    while (getline(infile,s)){
        data += s;
    }
    cout<<data<<endl;
    xpack::json::decode(data, s1);          // json转结构体
    n->BrName = defaultBrName;
    //json.Unmarshal(bytes, n),判断返回错误信息。
    cniVersion = n->netConf_type.CNIVersion;
    err = "";
}

//TODO 创建网桥
void setupBridge(NetConf *n,netlink::Bridge *br){
    br->attrs.Name = "bridge0";
    br->attrs.HardwareAddr = "0.0.0.1";
    cout << "bridge build success"<<endl;
}   //调用netlink建立网桥,netlink.LinkByName、netlink.LinkAdd

//TODO 创建veth，并插入Ns和网桥
void setupVeth(string netns,netlink::Bridge br,string ifName,int mtu,bool hairpinMode){

    cout <<"veth build success"<<endl;
}
void bridgeByName(string name) {

}
char *calcGatewayIP(types::IPNet *ipn){

}
void ensureBridgeAddr(netlink::Bridge *br,types::IPNet *gwn){

}

void cmdAdd(skel::CmdArgs *args) {
    bool success = false;
    NetConf n;
    string cniVersion;
    string err;
    loadNetConf(args->StdinData,&n,cniVersion,err);//加载网络配置
    if(err != "") {
        cout << "错误"<<endl;
    }
    if(n.IsDefaultGW){
        n.IsGW = true;
    }
    //创建网桥
    netlink::Bridge br;
//    types::INTERFACE brInterface;
    setupBridge(&n,&br);
    //创建veth并插入Ns和bridge
    setupVeth(args->Netns,br, args->IfName, n.MTU, n.HairpinMode);
    //TODO 调用IPAM.ExecAdd
    types::Result result;
    if(result.IP4 == nullptr){
        //输出错误：IPAM plugin returned missing IPv4 config
    }
    if(result.IP4->Gateway == nullptr && n.IsGW){
        result.IP4->Gateway = calcGatewayIP(&result.IP4->IP);
    }
    //TODO 调用IPAM.ConfigureIface
    result.print = "done";
//    ip::SetHWAddrByIP();//设置MAC地址
    if (n.IsGW){
        types::IPNet gwn;
        gwn.IP = result.IP4->Gateway;
        gwn.Mask = result.IP4->IP.Mask;
        ensureBridgeAddr(&br, &gwn);
        ip::EnableIP4Forward();
        //TODO 设置网桥为默认网关
        cout<<"成功将网桥设置成网关"<<endl;
    }
  //  if (n.IPMasq){
  //     ip::SetupIPMasq();
  //  }
  result.DNS = n.netConf_type.DNS;
    //TODO 最后返回result.print()
    cout<< result.print<<endl;
}

int main() {
    skel::CmdArgs *args;
    args = new skel::CmdArgs();
    cmdAdd(args);
    return 0;
}

