#include "httpserver.h"

#include <iostream>
#include <fstream>

#define MAX_FILENAME_LENGTH	260
#define CLRFNUM 2

HTTPServer::HTTPServer() {
	request = "";
	response = "";
}


//Recibe request de connection y los guarda.
bool HTTPServer::start(Connection connection) {
	request = connection.getRequest();
}

//Verifica si el request se corresponde con HTTP.
bool HTTPServer::isConnectionOK() {

	int length = request.size();
	int clrfNum = CLRFNUM;
	int buffer[MAX_FILENAME_LENGTH] = { 0 };

	int i = 0;
	while(i < length && clrfNum < CLRFNUM)
	{
		while(request[i] != '\n') {
			while(c != ' ') {
				if()
			}
		}

	}

		for (int i = 0; i < length; i++){
    request[i];
	}
}

//Busca, abre archivos y guarda contenido de archivo. De producirse error en alguno de los pasos, devuelve error. 
bool HTTPServer::doRequest() {

}

//Guarda respuesta en connection
string HTTPServer::getResponse() {

}

//Activa flag de respuesta en connection.
void HTTPServer::stop(Connection connection) {

}


//Lee request y guarda los campos. De no cumplir el formato, devuelve error.
bool HTTPServer::readRequest() {

}

//Construye respuesta 
void HTTPServer::doResponse() {

}