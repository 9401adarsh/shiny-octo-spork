#include "settings.h"
#include <string>
int packetIDseq = 0;

//class defining a packet
template <class T>
class packet{
    private: 

        int packet_id; //packet_id : unique ID used to identify packets on a network
        int hops; //hops: hop Counter for the packets. takes the default value as per the value in the Settings singleton
        T payload; //payload: message in the packet
        Settings settings; 
        std::string origin; //origin: stores the IP Address of router or host from packet originates
        std::string destination_IP; //destination_IP: stores the IP address of the dest. router for the packet.
    
    public: 
        //contructors
        packet(void)
        {
            this->hops = settings._defaultHopCount;
            packet_id = packetIDseq++;
        }
        packet(T &payLoad, std::string dest_ip_addr)
        {
            thishops = settings._defaultHopCount;
            packet_id = packetIDseq++;
            payload = payLoad;
            destination_IP = dest_ip_addr;
        }
        packet& operator = (packet& src)
        {
            this->hops = src.hops;
            this->packet_id = src.packet_id;
            this->payload = src.payload;
            this->destination_IP = src.destination_IP;
            return *this;
        }

        //increase HopCount
        void incHops()
        {
            hops++;
        }

        //decrease HopCount
        void decHops()
        {
            hops--;
        }

        //set Origin - the node from which packet arrives 
        void setOrigin(std::string origin)
        {
            this->origin = origin;
        }

        //Set Hops
        void setHops(int newHops)
        {
            this->hops = newHops;
        }

        //Set Payload - the message or data carried by the packet
        void setPayload(T srcPayload)
        {
            this->payload = srcPayload;
        }

        //Set the destination for the Packet => set Destination IP
        void setDestIP(std::string dest_ip_addr)
        {
            this->destination_IP = dest_ip_addr;
        }

        //get HopCount
        int getHops()
        {
            return hops;
        }

        //get Message in Packet
        T getPayload()
        {
            return payload;
        }

        //get Node from which packet is transmitted
        std::string getOrigin()
        {
            return this->origin;
        }

        //get destination IP address
        std::string getDestIP()
        {
            return this->destination_IP;
        }

        //get unique Packet ID which is used to identify forwarded packets
        int getPacketID()
        {
            return this->packet_id;
        }

        //destructor
        ~packet(void)
        {

        }
};