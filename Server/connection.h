#ifndef __CONNECTION_H
#define __CONNECTION_H

#include <string>

using namespace std;

class Connection {
public:

	Connection();

	//Getter request 
	string getRequest();

	//Getter request 
	void setRequest(string);

	//Chequeo de nueva información introducida
	bool isNewRequest();

	//Setter respuesta
	void setResponse(string);

	//Getter respuesta
	string getResponse();

	//Chequeo de nueva respuesta
	bool isNewResponse();

	void disconnect();

	bool isFinished();



private:
	string request;
	string response;
	bool send;
	bool newRequest;
	bool newResponse;
	bool disconnect;
}

#endif

