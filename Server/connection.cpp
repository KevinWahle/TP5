#include "connection.h"
#include <iostream>

using namespace std;

Connection::Connection(){
	data = "";
	send = false;
	disconnect = false;
	newData = false;
	finished = false;
}

string Connection::getData(){
	return data;
}

bool Connection::setData(string clientData){
	data = clientData;
}

bool Connection::sendData(){

}

void Connection::disconnect(){

}

bool Connection::isNewData(){

}

bool Connection::isFinished(){

}

