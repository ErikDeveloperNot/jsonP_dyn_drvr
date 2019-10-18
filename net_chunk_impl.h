#ifndef NET_CHUNK_IMPL_H
#define NET_CHUNK_IMPL_H

#include "IChunk_reader.h"


class net_chunk_impl : public IChunk_reader
{
private:
	int soc_fd;
	bool start_json;
	
	bool connect();
	
public:
	net_chunk_impl();
	~net_chunk_impl();

	virtual int get_next(char *buf, int cnt) override;
};

#endif // NET_CHUNK_IMPL_H
