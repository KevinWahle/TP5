#include "connection.h"
#include <iostream>



Connection::Connection() {
	request = "";
	response = "";
	newRequest = false;
}

string Connection::getRequest() {
	newRequest = false;
	return request;
}

void Connection::setRequest(string clientRequest) {
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
}




