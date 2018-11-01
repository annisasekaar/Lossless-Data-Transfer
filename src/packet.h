#ifndef PACKET_H
#define PACKET_H
#pragma

class Packet
{
private:
	int seqNum;
	int dataLength;
	char data;
	char checksum;
	const char SOH;
public:
	Packet(int seqNum, int dataLength, char data, char checksum);
	int getSeqnum();
	const char getSOH();
	int getdataLength();
	char getData();
	char getChecksum();
	bool isCheckSumEqual(char checksum);
	void printPacket();	
};

#endif