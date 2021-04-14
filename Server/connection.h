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


private:
	string request;
	string response;
	bool newRequest;
};

#endif //__CONNECTION_H

