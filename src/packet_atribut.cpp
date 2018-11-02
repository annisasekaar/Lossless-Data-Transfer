#include <iostream>
#include "packet_atribut.h"
using namespace std;

char checksum (char * frame , int size){
	u_long checksum = 0;
	while (size-- ){
		checksum += *frame++;
		if(checksum & 0xFFFF0000){
			checksum &= 0xFFFF;
			checksum++;
		}
	}
}

int createFrame(char * frame, int seqNum, int dataLength, char * data, bool endData ){
	frame[0] = endData ? 0x0 : 0x1;
	uint32_t frame_seqnum = htonl(seqNum);
	uint32_t frame_dataLength = htonl(dataLength);
	memcpy(frame + 1 , &frame_seqnum , 4);
	memcpy(frame + 5 , &frame_dataLength,4);
	memcpy(frame + 9 , data , dataLength);
	frame[dataLength+9] = checksum(frame, dataLength + (int) 9 );

	return dataLength + (int) 10;
}

void createACK(int seqNum, char *ack , bool dataError){
	ack[0] = dataError ? 0x0 : 0x1;
	uint32_t frame_seqnum = htonl(seqNum);
	memcpy(ack + 1 , &frame_seqnum, 4);
	ack[5] = checksum(ack, ACK_LENGTH - (int) 1);
}

bool readFrame(int * seqNum, char * data, int * dataLength, bool *eot , char * frame){
	*eot = frame[0] = 0x0 ? false : true;
	uint32_t frame_seqnum;
	memcpy (&frame_seqnum, frame+1 , 4);
	*seqNum = ntohl(frame_seqnum);
	uint32_t frame_dataLength;
	memcpy(&frame_dataLength, frame + 5 , 4);
	*dataLength = ntohl(frame_dataLength);
	memcpy(data, frame+9 , *dataLength);
	return frame[*dataLength+9] != checksum(frame, *dataLength + (int) 9 );
}

bool readACK(int *seqNum, bool *error, char *ack){
	*error = ack[0] = 0x0 ? false:true;
	uint32_t frame_seqNum;
	memcpy(&frame_seqNum, ack+1 , 4);
	*seqNum = ntohl(frame_seqNum);
	return ack[5] != checksum(ack, ACK_LENGTH - (int) 1);
}