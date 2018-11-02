#include <iostream>
#include "packet.h"

using namespace std;

Packet::Packet(int seqNum, int dataLength, char * data):SOH(1){
	this->seqNum = seqNum;
	this->data = data;
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
	return *this->data;
}

void Packet::printPacket(){
	cout<<"SOH : "<<this->SOH<<"\n";
	cout<<"seqnum : "<<this->seqNum<<"\n";
	cout<<"Data Length : "<<this->dataLength<<"\n";	
	cout<<"data : "<<*this->data<<"\n";
}



