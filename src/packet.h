#ifndef PACKET_H
#define PACKET_H
#pragma

class Packet
{
private:
	int seqNum;
	char data;
	char checksum;
	const char SOH;
	const char STX; 
	const char ETX;
public:
	Packet(int seqNum, char data, char checksum);
	int getSeqnum();
	const char getSOH();
	const char getSTX();
	char getData();
	const char getETX();
	char getChecksum();
	bool isCheckSumEqual(char checksum);
	void printPacket();	
};

#endif