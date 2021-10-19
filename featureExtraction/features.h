/*
 * features.h
 *
 *  Created on: Jul 29, 2015
 *      Author: bhuwan
 */

#ifndef FEATURES_H_
#define FEATURES_H_
#include <stdint.h>



struct features{
	int packetLength;
	int DFvalue;
	int MFvalue;
	int ReservedValue;
	int TTLvalue;
	int TOSvalue;
	int checksumvalue;
	int Pushvalue;
	int ECEvalue;
	int CWRvalue;
	int URGValue;
	int ACKvalue;
	int RSTvalue;
	int SYNvalue;
	int FINvalue;

	features(){}
	features(int pLen,int dfvalue,int mfvalue,int resvalue,int ttlvalue,int tosvalue,int chksmvalue,
			int pshvalue, int ecevalue, int cwrvalue, int urgpointer, int ackvalue, int rstvalue,
			int synvalue, int finvalue):
				packetLength(pLen),DFvalue(dfvalue), MFvalue(mfvalue), ReservedValue(resvalue), TTLvalue(ttlvalue),
				TOSvalue(tosvalue), checksumvalue(chksmvalue), Pushvalue(pshvalue), ECEvalue(ecevalue),
				CWRvalue(cwrvalue), URGValue(urgpointer), ACKvalue(ackvalue), RSTvalue(rstvalue),
				SYNvalue(synvalue), FINvalue(finvalue)
				{}

	void insert(int pLen,int dfvalue,int mfvalue,int resvalue,int ttlvalue,int tosvalue,int chksmvalue,
				int pshvalue, int ecevalue, int cwrvalue, int urgpointer, int ackvalue, int rstvalue,
				int synvalue, int finvalue){

		packetLength = pLen;
		DFvalue = dfvalue;
		MFvalue = mfvalue;
		ReservedValue = resvalue;
		TTLvalue = ttlvalue;
		TOSvalue = tosvalue;
		checksumvalue = chksmvalue;
		Pushvalue = pshvalue;
		ECEvalue = ecevalue;
		CWRvalue = cwrvalue;
		URGValue = urgpointer;
		ACKvalue = ackvalue;
		RSTvalue = rstvalue;
		SYNvalue = synvalue;
		FINvalue = finvalue;

	}
};


#endif /* FEATURES_H_ */
