#include "featureExtraction.h"

void extractFeatures(Eigen::MatrixXf** res,Packet* pkts,import::holder* ref,int& count){
	(*res) = new Eigen::MatrixXf(count,19);

	for(int i=0;i<count;i++){
		extractor(res,pkts,ref[i],i);
	}
}

int chksum_ver(PDU* pdu,TCP& tcp){
	int cur = tcp.checksum();
	pdu->serialize();
	return tcp.checksum() == cur;
}

void extractor(Eigen::MatrixXf** res,Packet* pkts, import::holder& h,int& pos){
	// features register for this session/stream
	int totalFINvalue = 0,totalSYNvalue = 0, totalRSTvalue = 0;
	float duration = abs(pkts[h.indices.at(h.indices.size()-1)].timestamp().microseconds()-pkts[h.indices.at(0)].timestamp().microseconds());
	// hold features for each packet before calculation for connection
	int totalPackets = h.indices.size();
	Eigen::MatrixXf mat(totalPackets,15);

	int i=-1;
	for(std::vector<int>::iterator it = h.indices.begin();it!=h.indices.end();++it){
		PDU* pdu = pkts[*it].pdu();				// get the packet of this connection
		const IP &ip = pdu->rfind_pdu<IP>();	// Find the IP layer
	    TCP &tcp = pdu->rfind_pdu<TCP>(); 		// Find the TCP layer

	    //now get the attributtes
	    totalFINvalue += _FIN(tcp);
	    totalSYNvalue += _SYN(tcp);
	    totalRSTvalue += _RST(tcp);

	    mat.row(++i) << pdu->size(),DF(ip),MF(ip),RV(ip),ip.ttl(),ip.tos(),chksum_ver(pdu,tcp),
	    		_PSH(tcp),_ECE(tcp),_CWR(tcp),_URG(tcp),_ACK(tcp),_RST(tcp),_SYN(tcp),_FIN(tcp);
	}
						// class, index of packet representing this connection, total packets in conn, fsr
	(*res)->row(pos) << 0,h.indices.at(0) , totalPackets , (totalFINvalue+totalRSTvalue+totalSYNvalue)/float(totalPackets),
					mat.colwise().mean(); //mean elements appended
	// now that we have values calculated for every packet in this connection, now calculate
	// mean values
}
