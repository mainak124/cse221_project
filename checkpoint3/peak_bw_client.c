#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "armpmu_lib.h"

//#define BUF_SIZE 15000

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n1=0,n2=0;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	uint32_t time_start;
	uint32_t time_now;
	int con_ret;
	int BUF_SIZE = atoi(argv[3]);
	char* rd_buffer = (char*) malloc(BUF_SIZE);
	char* wr_buffer = (char*) malloc(BUF_SIZE);

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
	serv_addr.sin_port = htons(portno);
	con_ret = connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
	if(con_ret < 0)
		error("ERROR connecting");
	memset(wr_buffer,0,BUF_SIZE);
	memset(rd_buffer,0,BUF_SIZE);
	memcpy(wr_buffer,&time_start,4);
	int sum = 0;
	int flag=1;
	n1 = write(sockfd,wr_buffer,4);
	time_start = rdtsc32();
	while(flag){
		n2 = read(sockfd,rd_buffer,BUF_SIZE);
		if(n2 <= 0) flag=0;
		sum += n2;
	}
	time_now = rdtsc32();
	if (n2 < 0) 
		error("ERROR reading from socket");
	printf("%d, %d, %u, %u, Bandwidth: %f\n", sum, n2, time_now,time_start,(float)(sum)*100000000*72/(time_now - time_start));
	close(sockfd);
	free(rd_buffer);
	free(wr_buffer);
	return 0;
}
