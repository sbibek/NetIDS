#ifndef __IMPORTER__
#define __IMPORTER__


#include <tins/tins.h>
#include <iostream>
#include <stddef.h>
#include <functional> 
#include <string>
#include <vector>
#include "importerStructs.h"
#include "../featureExtraction/featureExtraction.h"
using namespace std;

using namespace Tins;


namespace import{
	#define MAX_BUFFER_SZ 10000000
	#define MAX_IP_SZ 16

	// structure for storing the information of packets
	// 
	extern unsigned long long* id; // id is given to each of the packet for uniquely identifying them

	extern unsigned long long* sip;
	extern unsigned short sport[MAX_BUFFER_SZ];

	extern unsigned long long* dip;
	extern unsigned short dport[MAX_BUFFER_SZ];

	extern Packet packets[MAX_BUFFER_SZ];


	extern int ref_count;
	extern holder* sorted_ref;
	extern ip src[MAX_BUFFER_SZ]; // src ip
	extern ip dst[MAX_BUFFER_SZ]; // dest ip
	/*
	 * new elements are added here
	 */

	extern unsigned long long Index;
	extern std::hash<std::string> hasher;	


	// packet read loop hook
	bool __loop(Packet pkt);

	// this function will initiate the transfer of packets from the file specified
	// to the required structures
	bool readPacketsFrom(std::string);
	//void test(unsigned long long* k,info* f,int count);
}



#endif
