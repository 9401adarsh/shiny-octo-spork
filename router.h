#include<stdlib.h>
#include<string> 
#include<iostream>
#include<list>
#include<unordered_set>
#include "packet.h"

int numOfTransmissions = 0; //keeps track of total number of packets flooded (includes the original packet)

//class defining router => the nodes in our topology
class router{
    
    private: 
        std::string addr; //addr: stores addr by which router is identified
        std::list<router*> adjRouters; //list of routers adjacent to this router
        std::unordered_set<int> seen; //set of seen packet_ids by the router, used for identifying previously forwarded packets
        static Settings settings; //static object of the singleton Settings class for access

    public: 
        //Constructors and Copy Assignment
        router(void)
        {

        }
        router(std::string router_addr)
        {
            this->addr = router_addr;
        }
        router& operator = (router& src){
            this->addr = src.addr;
            this->adjRouters.assign(src.adjRouters.begin(), src.adjRouters.end());
            return *this;
        }

        //Function to put destination in this router's adjRouters and vice versa
        void makeNewConnection(router &destination)
        {
            this->adjRouters.push_back(&destination);
            destination.adjRouters.push_back(this);
            //std::cout<<"Added "<<destination.getIPaddr()<<" to "<<this->getIPaddr()<<"'s adj List"<<std::endl;
            //destination.makeNewConnection(*this);
        }

        //Return router's address
        std::string getIPaddr()
        {
            return this->addr;
        }

        //Function which receives packets from other routers and hosts, and floods to others. 
        template <class T>
        void receive(packet<T> pckt)
        {    
            std::string src_ip_addr = pckt.getOrigin();

            //check if packet has been already forwarded, only checks this if block when _allowLooping is unchecked in settings Class
            if(!settings._allowLooping)
            {
                if(this->seen.find(pckt.getPacketID()) != this->seen.end())
                {
                    std::cout<<"-----------------------\n";
                    std::cout<<"Status: Discarded (Already Forwarded).\nRouter: "<<this->getIPaddr()<<"\nPacket with ID: "<<pckt.getPacketID()<<"\nOrigin: "<<pckt.getOrigin()<<"\nRem Hops: "<<pckt.getHops()<<std::endl;
                    std::cout<<"-----------------------\n";
                    return;
                }
                this->seen.insert(pckt.getPacketID());
            }
            
            
            if(pckt.getDestIP() == this->getIPaddr()) //check if packet has reached destination
            {
                std::cout<<"-----------------------\n";
                std::cout<<"Status: Received.\nRouter: "<<this->getIPaddr()<<"\nPacket with ID: "<<pckt.getPacketID()<<"\nPayload: "<<pckt.getPayload()<<std::endl;
                std::cout<<"-----------------------\n";

                /*
                char response = 'y';
                std::cout<<"Do you still want to view the simulation ? Enter y if yes, any other character if no"<<std::endl;
                std::cin>>response;

                if(response != 'y')
                    exit(EXIT_SUCCESS); 

                */
                std::cout<<"-----------------------"<<std::endl;
                std::cout<<"Resuming Simulation....\n"<<std::endl;               
            }
            else if(pckt.getHops() == 0) //check if packet has zero hopCount
            {
                std::cout<<"-----------------------\n";
                std::cout<<"Status: Discarded (Hop Count = 0).\nRouter: "<<this->getIPaddr()<<"\nPacket with ID: "<<pckt.getPacketID()<<"\nOrigin: "<<pckt.getOrigin()<<std::endl;
                std::cout<<"-----------------------\n";
            }
            else //flooding to all adjacent routers except the origin node for this packet
            {   
                std::cout<<"-----------------------\n";
                std::cout<<"Status: In Transit.\nRouter: "<<this->getIPaddr()<<"\nPacket with ID: "<<pckt.getPacketID()<<"\nOrigin: "<<pckt.getOrigin()<<"\nRem Hops: "<<pckt.getHops()<<std::endl;
                std::cout<<"-----------------------\n";

                //sending clone packets to all adjacent Routers except the packet's origin node
                for(auto adjRouter: this->adjRouters)
                    if(adjRouter->getIPaddr() != src_ip_addr)
                        this->send(pckt, adjRouter); //sends packet to adjRouter
            }

            return;
        }

        template <class T>
        void send(packet<T> pckt, router *destination) //function to send packets
        {
            numOfTransmissions++; 
            pckt.decHops(); //decreasing hops for the cloned packet to be sent
            pckt.setOrigin(this->getIPaddr()); //rechanging origin for newly cloned packet to current router
            //std::cout<<"The origin for this cloned packet is "<<pckt.getOrigin()<<std::endl; 
            destination->receive(pckt); //calling receive for destination router, for it to receive and flood to its neighbours.
        }

        ~router()
        {

        }
};