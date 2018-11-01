#include <iostream>
#include "packet.h"

using namespace std;

Packet::Packet(int seqNum, char data, char checksum ):SOH(1),STX(2),ETX(3){
	this->seqNum = seqNum;
	this->data = data;
	this->checksum = checksum;
}

int Packet::getSeqnum(){
	return this->seqNum;
}

const char Packet::getSOH(){
	return this->SOH;
}

const char Packet::getSTX(){
	return this->STX;
}

char Packet::getData(){
	return this->data;
}

const char Packet::getETX(){
	return this->ETX;
}

char Packet::getChecksum(){
	return this->checksum;
}

bool Packet::isCheckSumEqual(char checksum){
	return this->checksum==checksum;
}

void Packet::printPacket(){
	cout<<"SOH : "<<this->SOH<<"\n";
	cout<<"STX : "<<this->STX<<"\n";
	cout<<"ETX : "<<this->ETX<<"\n";
	cout<<"seqnum : "<<this->seqNum<<"\n";
	cout<<"data : "<<this->data<<"\n";
	cout<< "checksum : "<<this->checksum<<"\n";
}



