#ifndef __HTTPSERVER_H
#define __HTTPSERVER_H

#include "connection.h"
#include <iostream>

class HTTPServer {
public:
	HTTPServer(Connection* connection);

	//Recibe request de connection y los guarda.
	void start();

private:

	//Verifica si el request se corresponde con HTTP.
	bool isRequestOK();

	//Busca, abre archivos y guarda contenido de archivo. De producirse error en alguno de los pasos, devuelve error. 
	void doRequest();

	//Devuelve respuesta.
	void doResponse();

	Connection* myConnection;
	string request;
	string filename;
	string fileContent;
	string response;
	int filenameLength;
	bool fileCheck;
};

#endif
