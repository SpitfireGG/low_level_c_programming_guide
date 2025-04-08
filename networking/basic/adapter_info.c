#include "stdlib.h"
#include "sys/socket.h"
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <stdio.h>

// program to view the adapter info and more with reference from the book
// "network programming with C Packt pub"

#define BUF_SIZE 100

struct ifaddrs *ifa, *ifaddr_list;

int main() {

    char addr_buffer[BUF_SIZE];
    if (getifaddrs(&ifaddr_list)) {
        printf("failed to obtain the names of the \n");
        return -1;
    }

    for (ifa = ifaddr_list; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        int family = ifa->ifa_addr->sa_family;
        if (family == AF_INET || family == AF_INET6) {
            // print the name of the family
            printf("interface %-10s", ifa->ifa_name);

            // print addr family
            printf("<interface type> %-6s",
                   (family = AF_INET) ? "IVP4" : "IPV6");

            // converting the addr to human rdable format

            void *addr_ptr;
            if (family == AF_INET) {
                addr_ptr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            } else {
                addr_ptr = &((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            }
            if (inet_ntop(family, addr_ptr, addr_buffer, BUF_SIZE)) {
                printf("Address: %s\n", addr_buffer);
            } else {

                printf("Address translation failed\n");
            }
        }
    }
    freeifaddrs(ifaddr_list);
    return 0;
}
