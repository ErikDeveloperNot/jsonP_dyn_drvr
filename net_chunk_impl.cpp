#include "net_chunk_impl.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <sys/poll.h>
//#include <sys/ioctl.h>
#include <unistd.h>
#include <netdb.h>
//#include <resolv.h>

#include <iostream>


net_chunk_impl::net_chunk_impl() : soc_fd{-1}, start_json{false}
{
//	char buf[1025];
//	get_next(buf, 1024);
}

net_chunk_impl::~net_chunk_impl()
{
	close(soc_fd);
//	std::cout << "IChunk_reader example net_chunk_impl destroyed\n";
}


int net_chunk_impl::get_next(char* buf, int cnt)
{
	if (soc_fd == -1) {
		//need to connect
		connect();
	}
	
	int rec{0};
	
	rec = recv(soc_fd, buf, cnt, 0);

	std::cout << "net_chunk_impl received " << rec << " bytes, feeding to the buffer parser\n"; // << buf << std::endl;	

// bad workaround - not sure why these so up it the stream sometimes
bool b1{false};
bool b2{false};
if (start_json) {
	for (size_t i{0}; i<rec; i++) {
	//	std::cout << buf[i] << ":";
		if (buf[i] == '\r') {
			b1 = (b1) ? false : true;
			b2 = false;
		}
		if (buf[i] == '\n' && b1)
			b2 = (b2) ? false : true;
			
		if (b1 && b2) {
			std::cout << "b1 && b2, changing: " << buf[i] << "\n";
			buf[i] = ' ';
		}
	}
}

	if (start_json) {
		return rec;
	} else {
		while (!start_json) {
			int start{0};
			for (; start < rec; start++) {
				if (buf[start] == '{') {
					start_json = true;
					
					int i{0};
					for (; start < rec; start++)
						buf[i++] = buf[start];
						
					return i;
				}
			}
			
			rec = recv(soc_fd, buf, cnt, 0);
		}
	}
	
	return -1;
}


bool net_chunk_impl::connect()
{
	sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
	hostent *host = (hostent*) gethostbyname("data.cityofnewyork.us"); 
	
	if (host == NULL) {
		std::cerr << "error getting address for data.transportation.gov\n";
		return false;
	}
		
	addr.sin_addr = *((in_addr *)host->h_addr);
	
//	http:data.cityofnewyork.us/api/views/25th-nujf/rows.json?accessType=DOWNLOAD
//	addr.sin_addr = "data.transportation.gov"; //"https://data.transportation.gov/api/views/8ect-6jqj/rows.json?accessType=DOWNLOAD";
	soc_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	::connect(soc_fd, (sockaddr *)&addr, sizeof(sockaddr));
	
	if (soc_fd == -1) {
		std::cerr << "error connecting to data.transportation.gov\n";
		return false;
	}
//https://data.ny.gov/api/views/tk82-7km5/rows.json?accessType=DOWNLOAD
//	const char *msg = "GET /api/views/8ect-6jqj/rows.json?accessType=DOWNLOAD HTTP/1.1\n\n";
	const char *msg = "GET /api/views/25th-nujf/rows.json?accessType=DOWNLOAD HTTP/1.1\r\nHost: data.cityofnewyork.us\r\nConnection: close\r\n\r\n";
	int len = strlen(msg);
	
	int sent = send(soc_fd, msg, len, 0);
std::cout << "Sent: " << sent << std::endl;
	if (sent > 0)
		return true;
	else 
		return false;
}
