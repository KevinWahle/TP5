#include "connection.h"
#include <iostream>



Connection::Connection() {
	request = "";
	response = "";
	newRequest = false;
	newResponse = false;
	finished = false;
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
	newResponse = false;
	return response;
}

void Connection::setResponse(string response) {
	this->response = response;
	newResponse = true;
}

bool Connection::isNewResponse() {
	return newResponse;
}

//ME PARECE QUE ESTAS DOS NO SON NECESARIAS
bool Connection::isFinished() {
	return finished;
}

void Connection::disconnect() {
	finished = true;
}




