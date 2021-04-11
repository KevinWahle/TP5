#include "httpserver.h"

#include <iostream>
#include <fstream>

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