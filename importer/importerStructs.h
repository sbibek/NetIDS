/*
 * importerStructs.h
 *
 *  Created on: Jul 28, 2015
 *      Author: bhuwan
 */

#ifndef IMPORTERSTRUCTS_H_
#define IMPORTERSTRUCTS_H_
#include <iostream>
#include <stddef.h>
#include <functional>
#include <string>
#include <vector>
#define MAX_BUFFER_SZ 10000000
#define MAX_IP_SZ 16

namespace import{
struct ip {

		char value[MAX_IP_SZ];

		void insert(const std::string& val){
			strncpy(value,val.c_str(),MAX_IP_SZ);
		}
	};

	// for holding reference data
	struct holder {
		std::vector<int> indices;
	};

}

#endif /* IMPORTERSTRUCTS_H_ */
