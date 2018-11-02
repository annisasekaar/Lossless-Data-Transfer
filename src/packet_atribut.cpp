#include <iostream>
#include "packet_atribut.h"
using namespace std;

char checksum (char * frame , int count){
	u_long sum = 0;
	while (count -- ){
		sum += *frame++;
		if(sum & 0xFFFF0000){
			sum &= 0xFFFF;
			sum++;
		}
	}
}

int createFrame(char * frame, int seqNum, int dataLength, char * data, bool eot ){
	frame[0] = eot ? 0x0 : 0x1;
	uint32_t net_seqnum = htonl(seqNum);
	uint32_t net_dataLength = htonl(dataLength);
	memcpy(frame + 1 , &net_seqnum , 4);
	memcpy(frame + 5 , &net_dataLength,4);
	memcpy(frame + 9 , data , dataLength);
	frame[dataLength+9] = checksum(frame, dataLength + (int) 9 );

	return dataLength + (int) 10;
}

void createACK(int seqNum, char *ack , bool error){
	ack[0] = error ? 0x0 : 0x1;
	uint32_t net_seqnum = htonl(seqNum);
	memcpy(ack + 1 , &net_seqnum, 4);
	ack[5] = checksum(ack, ACK_SIZE - (int) 1);
}

bool readFrame(int * seqNum, char * data, int * dataLength, bool *eot , char * frame){
	*eot = frame[0] = 0x0 ? false : true;
	uint32_t net_seqnum;
	memcpy (&net_seqnum, frame+1 , 4);
	*seqNum = ntohl(net_seqnum);

	uint32_t net_dataLength;
	memcpy(&net_dataLength, frame + 5 , 4);
	*dataLength = ntohl(net_dataLength);

	memcpy(data, frame+9 , *dataLength);

	return frame[*dataLength+9] != checksum(frame, *dataLength + (int) 9 );
}

bool readACK(int *seqNum, bool *error, char *ack){
	*error = ack[0] = 0x0 ? false:true;

	uint32_t net_seqNum;
	memcpy(&net_seqNum, ack+1 , 4);
	*seqNum = ntohl(net_seqNum);

	return ack[5] != checksum(ack, ACK_SIZE - (int) 1);
}