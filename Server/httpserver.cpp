#include "httpserver.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>


#define		GET		"GET"
#define		HTTP_PROTOCOL	 "HTTP/1.1"
#define		HTML	".html"
#define		JSON	".json"
#define		TXT		".txt"
#define		HOST	"Host: 127.0.0.1"
#define		CRLF	"\r\n"
#define		RELATIVE_PATH	".."

#pragma warning(disable : 4996)


HTTPServer::HTTPServer(Connection* connection) {
	request = "";
	response = "";
	filename = "";
	fileContent = "";
	filenameLength = 0;
	fileCheck = false;
	myConnection = connection;
}

//Recibe request de connection y los guarda.
void HTTPServer::start() {
	request = myConnection->getRequest();
	if (isRequestOK())
		doRequest();
	doResponse();
	myConnection->setResponse(response);
}

//Verifica si el request se corresponde con HTTP.
bool HTTPServer::isRequestOK() {

	//Separa request en lineas. 
	size_t firstLineLength = request.find(CRLF);
	if (firstLineLength == string::npos) {
		return fileCheck;
	}
	string firstLine = request.substr(0, firstLineLength);
	size_t secondLineLength = request.find(CRLF, firstLineLength + 2);
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
	found = firstLine.find(GET);
	if (found == string::npos || found != 0) {
		return fileCheck;
	}
	firstLine.erase(found, 3);
	found = firstLine.find(HTTP_PROTOCOL);
	if (found == string::npos) {
		return fileCheck;
	}
	firstLine.erase(found, 8);

	size_t slash = firstLine.find("/");
	found = firstLine.find(HTML);
	if (found == string::npos) {
		found = firstLine.find(TXT);
		if (found == string::npos) {
			found = firstLine.find(JSON);
			if (found == string::npos) {
				return fileCheck;
			}
			else {
				filename.assign(firstLine, slash, found + 5 - slash);
			}
		}
		else {
			filename.assign(firstLine, slash, found + 4 - slash);
		}
	}
	else {
		filename.assign(firstLine, slash, found + 5 - slash);
	}
	//Adapta filename.
	slash = 0;
	do {
		slash = filename.find("/");
		if (slash != string::npos) {
			if (slash == 0) {
				filename.erase(slash, 1);
			}
			else {
				filename.replace(slash, 1, "\\");
			}
		}
	} while (slash != string::npos);

	//Si llegó hasta acá, parseo de request completo.
	fileCheck = true;
	return fileCheck;
}

//Busca, abre archivos y guarda contenido de archivo. De producirse error en alguno de los pasos, devuelve error. 
void HTTPServer::doRequest() {
	if (fileCheck == false) {
		return;
	}
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

//Guarda respuesta en connection
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

}
