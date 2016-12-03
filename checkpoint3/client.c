#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "armpmu_lib.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char rd_buffer[5];
	char wr_buffer[5];
	uint32_t time_start;
	uint32_t time_now;
	int con_ret;

	if (argc < 3) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	memset((char *) &serv_addr,0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy((char *)&serv_addr.sin_addr.s_addr,(char *)server->h_addr,server->h_length);
//	bcopy((char *)server->h_addr, 
//		(char *)&serv_addr.sin_addr.s_addr,
//		server->h_length);
	serv_addr.sin_port = htons(portno);
	time_start = rdtsc32();
	con_ret = connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
	time_now = rdtsc32();
	printf("Create: %d\n",time_now-time_start);
	if(con_ret < 0)
		error("ERROR connecting");
	memset(wr_buffer,0,5);
	memset(rd_buffer,0,5);
	time_start = rdtsc32();
	memcpy(wr_buffer,&time_start,4);
	n = write(sockfd,wr_buffer,5);
	if (n < 0) 
		error("ERROR writing to socket");
	n = read(sockfd,rd_buffer,5);
	time_now = rdtsc32();
	if (n < 0) 
		error("ERROR reading from socket");
	printf("Roundtrip: %u\n", (time_now - *(uint32_t*)rd_buffer));
	time_start = rdtsc32();
	close(sockfd);
	time_now = rdtsc32();
	printf("Close: %d\n",time_now-time_start);
	return 0;
}
