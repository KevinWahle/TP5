#ifndef __HTTPSERVER_H
#define __HTTPSERVER_H

#include "connection.h"

#include <iostream>

class HTTPServer {
public:
	HTTPServer();

	//Recibe request de connection y los guarda.
	void start(Connection connection);

	//Verifica si el request se corresponde con HTTP.
	void isConnectionOK();

	//Busca, abre archivos y guarda contenido de archivo. De producirse error en alguno de los pasos, devuelve error. 
	void doRequest();

	//Devuelve respuesta.
	string getResponse();

	//Activa flag de respuesta en connection.
	void stop(Connection connection);

private:
	//Lee request y guarda los campos. De no cumplir el formato, devuelve error.
	//bool readRequest();

	//Construye respuesta 
	//void doResponse();


	string request;
	string filename;
	string fileContent;
	string response;
	int filenameLength;
	bool fileCheck;
}

#endif
