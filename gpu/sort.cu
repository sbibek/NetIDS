#include "sort.cuh"




void generateTCPstream(unsigned long long* srcAddrArray,unsigned long long* dstAddrArray,unsigned short* srcPortArray,unsigned short* dstPortArray,int N,import::holder** ref,int& count){
	// upload data to GPU
	    thrust::device_vector<unsigned long long> d_src_addr(srcAddrArray, srcAddrArray+N);
	    thrust::device_vector<unsigned short> d_src_port(srcPortArray, srcPortArray+N);

	    thrust::device_vector<unsigned long long> d_dst_addr(dstAddrArray, dstAddrArray+N);
	    thrust::device_vector<unsigned short> d_dst_port(dstPortArray, dstPortArray+N);

	    thrust::device_vector<unsigned long long> d_orig_ind(N);
	    thrust::sequence(d_orig_ind.begin(), d_orig_ind.end());


	    // 1. sort within packet
	    auto zip_begin = zip(d_src_addr.begin(), d_src_port.begin(), d_dst_addr.begin(), d_dst_port.begin());
	    auto zip_end   = zip(d_src_addr.end(),   d_src_port.end(),   d_dst_addr.end(),   d_dst_port.end());
	    thrust::transform(zip_begin, zip_end, zip_begin, sort_within_packet());

	    // 2. sort packets
	    thrust::stable_sort(zip(d_src_addr.begin(), d_src_port.begin(), d_dst_addr.begin(), d_dst_port.begin(), d_orig_ind.begin()),
	                        zip(d_src_addr.end(),   d_src_port.end(),   d_dst_addr.end(),   d_dst_port.end(),   d_orig_ind.end()));





	    // 3. find stard indices of each stream
	    thrust::device_vector<unsigned long long> d_start_indices(N);

	    using namespace thrust::placeholders;
	    thrust::device_vector<unsigned long long>::iterator copyEnd = thrust::copy_if(thrust::make_counting_iterator(1), thrust::make_counting_iterator(N),
	                                                                            thrust::make_transform_iterator(
	                                                                               zip(
	                                                                                   zip(d_src_addr.begin(), d_src_port.begin(), d_dst_addr.begin(), d_dst_port.begin()),
	                                                                                   zip(d_src_addr.begin()+1, d_src_port.begin()+1, d_dst_addr.begin()+1, d_dst_port.begin()+1)
	                                                                                ),
	                                                                                find_start_indices()
	                                                                            ),
	                                                                            d_start_indices.begin()+1, _1);

	    unsigned long long streamCount = copyEnd-d_start_indices.begin();
	    d_start_indices.resize(streamCount);



	    // 4. generate some additional information about the result and print result formatted
	    thrust::device_vector<unsigned long long> d_stream_lengths(streamCount+1);
	    thrust::adjacent_difference(d_start_indices.begin(), d_start_indices.end(), d_stream_lengths.begin());
	    d_stream_lengths.erase(d_stream_lengths.begin());
	    d_stream_lengths.back() = N-d_start_indices.back();


	    thrust::host_vector<unsigned long long> h_start_indices = d_start_indices;
	    thrust::host_vector<unsigned long long> h_orig_ind = d_orig_ind;

	    auto index = h_start_indices.begin();
	    index++;

	    // we create the vector holder of this size of start indices
	    count = h_start_indices.size();
	    (*ref) = new import::holder[count];
	    int inx = 0;

	    (*ref)[inx].indices.push_back(h_orig_ind[0]);

   	    for(int i=1; i<N;++i){
	      if (i == *index){
	         index++; inx++;
	      }
	      (*ref)[inx].indices.push_back(h_orig_ind[i]);
	    }


}
