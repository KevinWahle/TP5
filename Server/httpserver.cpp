#include "httpserver.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

//--------------- CONSTANTES ---------------//

#define		CRLF	"\r\n"

#define		GET		"GET"
#define		HTTP_PROTOCOL	 "HTTP/1.1"
#define		HOST	"Host: 127.0.0.1"

#define		POINT	"."

#define		RELATIVE_PATH	".."

#pragma warning(disable : 4996)

//--------------- METODOS ---------------//

//Constructor. Recibe puntero a connection. 
HTTPServer::HTTPServer(Connection* connection) {
	request = "";
	response = "";
	filename = "";
	fileContent = "";
	filenameLength = 0;
	fileCheck = false;
	myConnection = connection;
}

//start(): Recibe request de connection, lo procesa, genera respuesta y la carga en connection.
void HTTPServer::start() {
	request = myConnection->getRequest();
	if (isRequestOK())
		doRequest();
	doResponse();
	myConnection->setResponse(response);
}

//isRequestOK(): Verifica si el request se corresponde con HTTP.
bool HTTPServer::isRequestOK() {

	//Separa request en lineas. 
	size_t firstLineLength = request.find(CRLF);	//Busca CRLF y separa primera linea. 
	if (firstLineLength == string::npos) {
		return fileCheck;
	}
	string firstLine = request.substr(0, firstLineLength);
	size_t secondLineLength = request.find(CRLF, firstLineLength + 2); //Busca CRLF y separa segunda linea. 
	if (secondLineLength == string::npos) {
		return fileCheck;
	}
	string secondLine = request.substr(firstLineLength + 2, secondLineLength - firstLineLength - 1);

	//Si la segunda linea no es equivalente a HOST, la request es incorrecta.
	if (!secondLine.compare(HOST)) {
		return fileCheck;
	}

	//Analiza primera linea.
	size_t found = 0;
	found = firstLine.find(GET);	//De no encontrarse GET, error.
	if (found == string::npos || found != 0) {
		return fileCheck;
	}
	firstLine.erase(found, 3);
	found = firstLine.find(HTTP_PROTOCOL);	//De no encontrarse el HTTP protocol, error.
	if (found == string::npos) {
		return fileCheck;
	}
	firstLine.erase(found, 8);
	
	//Busca nombre de archivo. Inicia buscando el punto y el siguiente espacio libre para la detectar extension.
	size_t firstSpace = firstLine.find(" ");
	found = firstLine.find(POINT);	
	if (found == string::npos) {
			//En caso de no encontrar el punto de la extension, devuelve error.
			return fileCheck;
	}
	else {
		size_t lastSpace = firstLine.find(" ", found);	//Busca siguiente espacio.
		if (lastSpace == string::npos) {
			return fileCheck;
		}
		else {
			filename.assign(firstLine, firstSpace + 1, lastSpace - firstSpace + 1); //Y construye la respuesta. 
		}
	}
	//Adapta filename cambiando formato de barras.
	do {
		found = filename.find("/");
		if (found != string::npos) {
			if (found == 0) {
				filename.erase(found, 1);
			}
			else {
				filename.replace(found, 1, "\\");
			}
		}
	} while (found != string::npos);

	//Si llegó hasta acá, parseo de request completo.
	fileCheck = true;
	return fileCheck;
}

//Busca, abre archivos y guarda contenido de archivo. De producirse error en alguno de los pasos, devuelve error. 
void HTTPServer::doRequest() {
	if (fileCheck == false) {
		return;
	}
	//Abre archivo.
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		fileCheck = false;
		return;
	}
	else
	{
		//Busca contenido y lo guarda.
		string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		fileContent.insert(0, content);

		//Calcula largo del contenido.
		file.seekg(0, file.end);
		filenameLength = (int) file.tellg();

		file.close();
	}
}

//doResponse(): construye respuesta y la guarda en connection.
void HTTPServer::doResponse() {
	//Se analiza si hubieron errores durante el proceso.
	string state;
	if (fileCheck != false) {
		state = "200 OK";
	}
	else {
		state = "404 Not Found";
	}

	response = "HTTP/1.1 ";
	response += state;
	response += "\r\n";
	response += "Date: ";

	//Tiempo
	time_t date = time(0);
	struct tm* datetm = gmtime(&date);
	char* dateGMT = asctime(datetm);
	string stringDate = "";
	if (dateGMT != NULL) {
		stringDate.assign(dateGMT);
		stringDate.pop_back();
	}

	response += stringDate;
	response += "\r\n";

	if (fileCheck != false) {
		response += "Location: 127.0.0.1 " + filename;
		response += "\r\n";
	}
	response += "Cache-Control: max-age=30";
	response += "\r\n";
	response += "Expires: ";

	//Tiempo
	datetm->tm_sec += 30;
	if (datetm->tm_sec > 59) {
		datetm->tm_sec -= 60;
	}
	dateGMT = asctime(datetm);
	if (dateGMT != NULL) {
		stringDate.assign(dateGMT);
		stringDate.pop_back();
	}

	response += stringDate;
	response += "\r\n";
	response += "Content-Length: ";
	response += to_string(filenameLength);
	response += "\r\n";
	response += "Content-Type: text/html; charset=iso-8859-1";
	response += "\r\n";
	if (fileCheck != false) {
		response += "\r\n";
		response += fileContent;
	}
	//Finaliza respuesta.
}
