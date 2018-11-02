#ifndef PACKET_H
#define PACKET_H
#pragma

class Packet
{
private:
	int seqNum;
	int dataLength;
	char * data;
	const char SOH;
public:
	Packet(int seqNum, int dataLength, char * data);
	int getSeqnum();
	const char getSOH();
	int getdataLength();
	char getData();
	void printPacket();	
};

#endif