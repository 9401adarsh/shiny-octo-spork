#include<bits/stdc++.h>
#include "router.h"

//function to define router topology, make packets, and simulate
void makeAndrun()
{
    std::vector<router> routers;
    int numRouters; 
    
    std::cout<<"Enter the number of routers: "<<std::endl;
    std::cin>>numRouters;
    std::unordered_map<std::string, int> addr_idx_map;
    
    //getting IP addresses of all routers and pushing them onto a vector of routers
    for(int i = 0; i < numRouters; i++)
    {
        std::string ip_addr;
        std::cout<<"Enter IP Address for Router-"<<i<<": ";
        std::cin>>ip_addr;
        addr_idx_map[ip_addr] = i;
        routers.push_back(router(ip_addr));
    }
    
    //getting all edges and setting up connections
    int numEdges; 
    std::cout<<"Enter the number of edges/connections in the topology: "<<std::endl;
    std::cin>>numEdges;

    while(numEdges--)
    {
        std::string addr1, addr2;
        std::cout<<"To make an edge, enter the IP addresses of the 2 routers on 2 separate lines: "<<std::endl;
        std::cin>>addr1;
        std::cin>>addr2;

        int u = addr_idx_map[addr1]; 
        int v = addr_idx_map[addr2];
        routers[u].makeNewConnection(routers[v]);
    }

    //getting packets
    int numPackets;
    std::cout<<"Enter the number of packets: "<<std::endl;
    std::cin>>numPackets;

    std::vector<packet<std::string>> packets(numPackets);
    for(int i = 0; i < numPackets; i++)
    {
        packet<std::string> pckt;
        pckt.setOrigin("Host");
        
        std::string payload;
        std::cout<<"Set Payload (String): ";
        std::getline(std::cin >> std:: ws, payload);
        pckt.setPayload(payload);

        std::string dest_ip;
        std::cout<<"Set Dest Address: ";
        std::getline(std::cin >> std::ws, dest_ip);
        pckt.setDestIP(dest_ip);

        packets[i] = pckt;
    }

    std::string src_ip;
    std::cout<<"Enter Source Router IP Address: ";
    std::cin>>src_ip;

    int src = addr_idx_map[src_ip];
    for(auto &pckt: packets)
        routers[src].receive(pckt);

    return;
}


int main()
{
    /*
    router router1, router2, router3, router4, router5, router6, router7;

    std::string msg1 = "Ole's at the wheel!";
    packet<std::string> dataPacket1;
    dataPacket1.setPayload(msg1);
    dataPacket1.setOrigin("Host");
    dataPacket1.setDestIP("Router-3");

    std::string msg2 = "Carrick's at the wheel!";
    packet<std::string> dataPacket2;
    dataPacket2.setPayload(msg2);
    dataPacket2.setOrigin("Host");
    dataPacket2.setDestIP("Router-4");
    

    extern int numOfTransmissions;

    router1 = *new router("Router-1");
    router2 = *new router("Router-2");
    router3 = *new router("Router-3");
    router4 = *new router("Router-4");
    router5 = *new router("Router-5");

    router1.makeNewConnection(router2);
    //router2.makeNewConnection(router1);

    router1.makeNewConnection(router3);
    //router3.makeNewConnection(router1);
    
    router2.makeNewConnection(router4);
    //router4.makeNewConnection(router2);
    
    router2.makeNewConnection(router5);
    //router5.makeNewConnection(router2);

    router4.makeNewConnection(router5);

    router1.receive(dataPacket1);
    router1.receive(dataPacket2);

    */
    std::cout<<"Flooding Routing Algorithm - Controlled (Packets only forwarded once to prevent looping)"<<std::endl;
    extern int numOfTransmissions;

    makeAndrun();
    
    std::cout<<std::endl;
    std::cout<<"Simulation is Over!! "<<std::endl;
    std::cout<<"The number of transmissions is "<<numOfTransmissions<<std::endl;
    
    return 1;
}