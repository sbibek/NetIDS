#ifndef _SORT_H_
#define _SORT_H_

#include <iostream>
#include <thrust/device_vector.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/iterator/transform_iterator.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/sort.h>
#include <thrust/sequence.h>
#include <thrust/copy.h>
#include <thrust/functional.h>
#include <thrust/adjacent_difference.h>
#include <thrust/scatter.h>
#include <vector>

#include "../importer/importerStructs.h"

using namespace std;
using namespace thrust::placeholders;



// < src ip, src port, dst ip, dst port >
typedef thrust::tuple<unsigned long long, unsigned short, unsigned long long, unsigned short> _packet;


struct sort_within_packet : public thrust::unary_function<_packet, _packet>
{
    __host__ __device__
    _packet operator()(_packet p) const
    {
        if (thrust::get<0>(p) > thrust::get<2>(p))
        {
            _packet copy(p);
            thrust::get<0>(p) = thrust::get<2>(copy);
            thrust::get<1>(p) = thrust::get<3>(copy);
            thrust::get<2>(p) = thrust::get<0>(copy);
            thrust::get<3>(p) = thrust::get<1>(copy);
        }
        return p;
    }
};

struct find_start_indices : public thrust::unary_function<thrust::tuple<_packet, _packet>, bool>
{
    __host__ __device__
    bool operator()(thrust::tuple<_packet, _packet> p)
    {
       return (thrust::get<0>(p) != thrust::get<1>(p));
    }
};

template<typename... Iterators>
__host__ __device__
thrust::zip_iterator<thrust::tuple<Iterators...>> zip(Iterators... its)
{
    return thrust::make_zip_iterator(thrust::make_tuple(its...));
}



void generateTCPstream(unsigned long long* srcAddrArray,unsigned long long* dstAddrArray,unsigned short* srcPortArray,unsigned short* dstPortArray,int N,import::holder** ref,int& refcount);


#endif
