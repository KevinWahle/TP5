#include "httpserver.h"

#include <iostream>
#include <fstream>
#include <ctime>

#define		GET		"GET"
#define		HTTP_PROTOCOL	 "HTTP/1.1/"
#define		HOST	"Host: 127.0.0.1"
#define		CRLF	"\r\n"


HTTPServer::HTTPServer() {
	request = "";
	response = "";
	filename = "";
	fileContent = "";
	filenameLength = 0;
	fileCheck = false;
}


//Recibe request de connection y los guarda.
void HTTPServer::start(Connection connection) {
	request = connection.getRequest();
}

//Verifica si el request se corresponde con HTTP.
void HTTPServer::isConnectionOK() {

	//Separa request en lineas. 
	size_t firstLineLength = request.find(CRLF);

	string firstLine = request.substr(0, firstLineLength);

	size_t secondLineLength = request.find(CRLF, firstLineLength);

	string secondLine = request.substr(firstLineLength, secondLineLength);

	//Si la segunda linea no es equivalente a HOST, la request es incorrecta.
	if (!secondLine.compare(HOST)) {
		fileCheck = false;
		return;
	}

	//Separa firstLine en words.
	string firstLineWords[3];

	size_t lastSpace = 0;
	int i = 0;
	while (firstLineLength > 0) {
		lastSpace = firstLine.rfind(" ");	//Analiza desde el final para atras los espacios
		if (lastSpace == string::npos) {
			lastSpace == 0;
		}
		if (lastSpace < firstLineLength) {	//De haber palabras entre el espacio y el final, o de no haber espacio, lo guarda.
			if (i >= 3) {	//Si se encontraron mas de tres palabras, request error. 
				fileCheck = false;
				return;
			}
			else {	//Guarda palabra localizada y reduce firstLine.
				firstLineWords[i++].assign(firstLine, lastSpace, firstLineLength - lastSpace + 1);
				firstLine.resize(lastSpace);
				firstLineLength = lastSpace;
			}
		}
		else {	//De haber un espacio en el ultimo caracter, lo borra.
			firstLine.pop_back();
			firstLineLength--;
		}
	}

	//Analiza primera linea de request.
	if (firstLineWords[0].compare(GET) != 0) {
		fileCheck = false;
		return;
	}
	if (firstLineWords[1].compare(HTTP_PROTOCOL) != 0) {
		if (firstLineWords[2].compare(HTTP_PROTOCOL) != 0) {
			fileCheck = false;
			return;
		}
		else {
			filename.assign(firstLineWords[1]);
		}
	}
	else {
		filename.assign(firstLineWords[2]);
	}
	//Si llegó hasta acá, parseo de request completo.
}

//Busca, abre archivos y guarda contenido de archivo. De producirse error en alguno de los pasos, devuelve error. 
void HTTPServer::doRequest() {
	if (fileCheck == false) {
		return;
	}
	ifstream file(filename);
	if (!file) {
		fileCheck == false;
		return;
	}
	else
	{
		file.seekg(0, file.end);
		filenameLength = file.tellg();
		file.seekg(0, file.beg);
		char* buffer = new char[filenameLength];
		file.read(buffer, filenameLength);
		if (!file) {
			fileCheck == false;
		}
		else {
			fileContent.assign(buffer);
		}
		file.close();
		delete[] buffer;
	}
}

//Guarda respuesta en connection
string HTTPServer::getResponse() {
	//Se analiza si hubieron errores durante el proceso.
	string state;
	if (fileCheck != false) {
		state = "200 OK";
	}
	else {
		state = "404 Not Found";
	}
	response = "HTTP/1.1" + ' ' + state;
	response += "\r\n";
	response += "Date: ";

	time_t date = time(0);
	tm* gmtm = gmtime(&date);
	char* dateGMT = asctime(gmtm);
	response += dateGMT;
	response += "\r\n";
	if (fileCheck != false) {
		response += "Location: 127.0.0.1" + filename;
	}
	response += "\r\n";
	response += "Cache-Control: max-age=30";
	response += "\r\n";
	response += "Expires: ";
	response += DATE + 30;
	response += "\r\n";
	response += "Content-Length: ";
	response += to_string(filenameLength);
	response += "\r\n";
	response += "Content-Type: text/html; charset=iso-8859-1";
	response += "\r\n";
	if (fileCheck != false) {
		response += fileContent;
	}

	return response;
}

//Activa flag de respuesta en connection.
void HTTPServer::stop(Connection connection) {
	connection.disconnect();
}