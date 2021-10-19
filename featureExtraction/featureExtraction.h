/*
 * featureExtraction.h
 *
 *  Created on: Jul 28, 2015
 *      Author: bhuwan
 */

#ifndef FEATUREEXTRACTION_H_
#define FEATUREEXTRACTION_H_
#include <iostream>
#include <vector>
#include <tins/tins.h>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include "../importer/importerStructs.h"
#include "features.h"

using namespace Tins;

// ip flags extractor
#define MF(IP) ((IP.frag_off()&57344)>>13)&1
#define DF(IP) ((IP.frag_off()&57344)>>13)&2
#define RV(IP) ((IP.frag_off()&57344)>>13)&4

// tcp flags extractor
#define _SYN(tcp) (tcp.get_flag(TCP::SYN))
#define _FIN(tcp) (tcp.get_flag(TCP::FIN))
#define _RST(tcp) (tcp.get_flag(TCP::RST))
#define _PSH(tcp) (tcp.get_flag(TCP::PSH))
#define _ACK(tcp) (tcp.get_flag(TCP::ACK))
#define _URG(tcp) (tcp.get_flag(TCP::URG))
#define _ECE(tcp) (tcp.get_flag(TCP::ECE))
#define _CWR(tcp) (tcp.get_flag(TCP::CWR))


int chksum_ver(PDU* pdu,TCP& tcp);
void extractFeatures(Eigen::MatrixXf** res,Packet* pkts,import::holder* ref,int& count);
void extractor(Eigen::MatrixXf** res,Packet* pkts, import::holder& h,int& pos);


#endif /* FEATUREEXTRACTION_H_ */
