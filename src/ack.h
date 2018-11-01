#ifndef ACK_H
#define ACK_H
#pragma

class ACK
{
private:
	int seqNum;
	const char SOH;
	char AWS;
	char checksum;
public:
	ACK(int seqNum, char AWS, char checksum);
	int getSeqnum();
	const char getSOH();
	char getAWS();
	char getChecksum();
	bool isCheckSumEqual(char checksum);
	void printACK();
	
};

#endif