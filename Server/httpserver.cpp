#include "httpserver.h"

#include <iostream>
#include <fstream>
#include <time.h>


#define		GET		"GET"
#define		HTTP_PROTOCOL	 "HTTP/1.1"
#define		HOST	"Host: 127.0.0.1"
#define		CRLF	"\r\n"

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

	cout << "request " << request << endl;

	//Separa request en lineas. 
	size_t firstLineLength = request.find(CRLF);

	if (firstLineLength == string::npos) {
		return fileCheck;
	}

	cout << "firstLineLength " << firstLineLength << endl;

	string firstLine = request.substr(0, firstLineLength);

	cout << "firstLine " << firstLine << endl;

	size_t secondLineLength = request.find(CRLF, firstLineLength + 2);

	if (secondLineLength == string::npos) {
		return fileCheck;
	}

	cout << "secondLineLength " << secondLineLength << endl;

	string secondLine = request.substr(firstLineLength + 2, secondLineLength - firstLineLength - 1);

	cout << "secondLine " << secondLine << endl;

	//Si la segunda linea no es equivalente a HOST, la request es incorrecta.
	if (!secondLine.compare(HOST)) {
		return fileCheck;
	}

	//Separa firstLine en words.
	string firstLineWords[3];

	size_t lastSpace = 0;
	size_t position = 0;
	int i = 0;
	while (firstLineLength > 0) {
		lastSpace = firstLine.rfind(" ");	//Analiza desde el final para atras los espacios
		if (lastSpace == string::npos) {
			lastSpace = 0;
			position = lastSpace;
		}
		else {
			position = lastSpace + 1;
		}
		if (lastSpace < firstLineLength) {	//De haber palabras entre el espacio y el final, o de no haber espacio, lo guarda.
			if (i >= 3) {	//Si se encontraron mas de tres palabras, request error. 
				return fileCheck;
			}
			else {	//Guarda palabra localizada y reduce firstLine.
				firstLineWords[i++].assign(firstLine, position, firstLineLength - lastSpace + 1);
				firstLine.resize(lastSpace);
				firstLineLength = lastSpace;
			}
		}
		else {	//De haber un espacio en el ultimo caracter, lo borra.
			firstLine.pop_back();
			firstLineLength--;
		}
	}
	cout << "First word" << firstLineWords[0] << endl;
	cout << "Second word" << firstLineWords[1] << endl;
	cout << "Third word" << firstLineWords[2] << endl;

	//Analiza primera linea de request.
	if (firstLineWords[2].compare(GET) != 0) {
		return fileCheck;
	}
	if (firstLineWords[1].compare(HTTP_PROTOCOL) != 0) {
		if (firstLineWords[0].compare(HTTP_PROTOCOL) != 0) {
			fileCheck = false;
			cout << "HOLA  2" << endl;
			return fileCheck;
		}
		else {
			filename.assign(firstLineWords[1]);
		}
	}
	else {
		cout << "HOLA  4" << endl;
		filename.assign(firstLineWords[0]);
	}
	cout << "filename " << filename << endl;

	//Si llegó hasta acá, parseo de request completo.
	fileCheck = true;
	return fileCheck;
}

//Busca, abre archivos y guarda contenido de archivo. De producirse error en alguno de los pasos, devuelve error. 
void HTTPServer::doRequest() {
	if (fileCheck == false) {
		cout << "HOLAAAA 1" << endl;
		return;
	}
	ifstream file(filename);
	if (!file) {
		cout << "HOLAAAA 2" << endl;
		return;
	}
	else
	{
		file.seekg(0, file.end);
		filenameLength = file.tellg();
		file.seekg(0, file.beg);
		char* buffer = new char[filenameLength]();
		file.read(buffer, filenameLength);
		if (!file) {
			cout << "HOLAAAA 3" << endl;
			return;
		}
		else {
			fileContent.assign(buffer);
		}
		file.close();
		delete[] buffer;
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
		response += "Location: 127.0.0.1" + filename;
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
		response += fileContent;
		response += "\r\n";
	}
}

//Activa flag de respuesta en connection.
//void HTTPServer::stop() {
//	connection.disconnect();
//}