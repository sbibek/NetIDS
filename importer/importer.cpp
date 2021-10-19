#include "importer.h"
#include "../gpu/sort.cuh"


namespace import{

	unsigned long long* id = new unsigned long long[MAX_BUFFER_SZ]; // id is given to each of the packet for uniquely identifying them
	unsigned short sport[MAX_BUFFER_SZ];
	unsigned short dport[MAX_BUFFER_SZ];
	unsigned long long* sip = new unsigned long long[MAX_BUFFER_SZ];
	unsigned long long* dip = new unsigned long long[MAX_BUFFER_SZ];
	Packet packets[MAX_BUFFER_SZ];

	holder* sorted_ref;
	int ref_count;

	ip src[MAX_BUFFER_SZ]; // src ip
	ip dst[MAX_BUFFER_SZ]; // dest ip
	unsigned long long Index = 0;
	std::hash<std::string> hasher;	



	bool __loop(Packet pkt) {

		const PDU &pdu = *(pkt.pdu());
		const Timestamp ts = pkt.timestamp();

		const IP &ip = pdu.rfind_pdu<IP>(); // Find the IP layer
	    const TCP &tcp = pdu.rfind_pdu<TCP>(); // Find the TCP layer


	    id[Index] = Index; // Index of this packet

	    src[Index].insert(ip.src_addr().to_string()); // Add string source address
   		dst[Index].insert(ip.dst_addr().to_string()); // Add string destination address
   		sport[Index] = tcp.sport(); // Add source port
   		dport[Index] = tcp.dport(); // Add destin port

   		sip[Index] = hasher(ip.src_addr().to_string()); // hash source ip to int
   		dip[Index] = hasher(ip.dst_addr().to_string()); // hash destin ip to int

   		packets[Index] = pkt;

	    Index++;

	    return true;
	}

	bool readPacketsFrom(std::string file){
		try{

			FileSniffer sniffer(file);
			sniffer.set_filter("tcp");
//			sniffer.sniff_loop(import::__loop);
			while(Packet pkt = sniffer.next_packet()){
				import::__loop(pkt);
			}

		} catch(...){
			// this will return any error if happened
			std::cout << "error occured reading files from packet";
			return false;
		}
		return true;
	}

	/*void test(unsigned long long* k,info* f,int count){
		std::cout << *(k+count);
		info i = *(f+count);
		std::cout << i.src;
	}*/
}



#include <iostream>
#include<fstream>

void debug(std::string df,float& f){
	std::cout << df << ' '<<f<<std::endl;
}

#define TIMING_CREATE float et;\
					cudaEvent_t start, stop;\
					cudaEventCreate(&start); cudaEventCreate(&stop);\

#define T_START cudaEventRecord(start);
#define D_SYNC cudaDeviceSynchronize();
#define T_DEBUG(M) \
		cudaEventRecord(stop); \
			cudaEventSynchronize(stop);\
			cudaEventElapsedTime(&et, start, stop);\
			debug(M,et);\

using namespace std;
int main(){
	TIMING_CREATE
	T_START
	import::readPacketsFrom("http.pcap");
	D_SYNC
	T_DEBUG("reading packets from file took (ms)")

	T_START
	generateTCPstream(import::sip,import::dip,import::sport,import::dport,(int)import::Index,&import::sorted_ref,import::ref_count);
	T_DEBUG("stream generation took (ms)")


	T_START
	Eigen::MatrixXf* f;
	extractFeatures(&f,import::packets,import::sorted_ref,import::ref_count);
	T_DEBUG("feature extraction took (ms)")
	//float* nf = f->data();

	std::cout <<"\n++++++++++++End Of Program++++++++++++\n";
}
