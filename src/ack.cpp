#include <iostream>
#include "ack.h"

using namespace std;

ACK::ACK(int seqNum, char AWS, char checksum):SOH(6){
	this->seqNum = seqNum;
	this->AWS = AWS;
	this->checksum = checksum;
}

int ACK::getSeqnum(){
	return this->seqNum;
}

const char ACK::getSOH(){
	return this->SOH;
}

char ACK::getAWS(){
	return this->AWS;
}

char ACK::getChecksum(){
	return this->checksum;
}

bool ACK::isCheckSumEqual(char checksum){
	return this->checksum==checksum;
}

void ACK::printACK(){
	cout<<"SOH : "<<SOH<<"\n";
	cout<<"seqnum : " <<seqNum<<"\n";
	cout<<"AWS : " <<AWS << "\n";
	cout<< "Checksum : " << int(this->checksum) << "\n"; 
}



