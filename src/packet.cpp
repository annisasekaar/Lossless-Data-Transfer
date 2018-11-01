#include <iostream>
#include "packet.h"

using namespace std;

Packet::Packet(int seqNum, int dataLength, char data, char checksum ):SOH(1){
	this->seqNum = seqNum;
	this->data = data;
	this->checksum = checksum;
	this->dataLength = dataLength;
}

int Packet::getSeqnum(){
	return this->seqNum;
}

const char Packet::getSOH(){
	return this->SOH;
}

int Packet::getdataLength(){
	return this->dataLength;
}

char Packet::getData(){
	return this->data;
}


char Packet::getChecksum(){
	return this->checksum;
}

bool Packet::isCheckSumEqual(char checksum){
	return this->checksum==checksum;
}

void Packet::printPacket(){
	cout<<"SOH : "<<this->SOH<<"\n";
	cout<<"seqnum : "<<this->seqNum<<"\n";
	cout<<"Data Length : "<<this->dataLength<<"\n";	
	cout<<"data : "<<this->data<<"\n";
	cout<< "checksum : "<<this->checksum<<"\n";
}



