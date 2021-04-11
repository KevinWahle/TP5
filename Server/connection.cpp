#include "connection.h"
#include <iostream>

Connection::Connection(){
	request = "";
	response = "";
	send = false;
	newRequest = false;
	newResponse = false;
	finished = false;			//NO EXISTE FINISHED
}

string Connection::getRequest(){
	return request;
}

void Connection::setRequest(string clientRequest){
	request = clientRequest;
	newRequest = true;
}

bool Connection::isNewRequest() {
	return newRequest;
}

string Connection::getResponse() {
	return response;
}

void Connection::setResponse(string response) {
	this->response = response;
	newResponse = true;
}

bool Connection::isNewResponse() {
	return newResponse;
}

bool Connection::isFinished(){
	return disconnect;
}

void Connection::disconnect(){	
	disconnect = true;
}




