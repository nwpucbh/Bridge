cmake_minimum_required(VERSION 3.20)
project(Bridge)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bridge main.cpp api/cni/sekl/skel.h api/cni/types/types.h api/netlink/netlink.h api/cni/ns/ns.h api/ip/ip.h)
