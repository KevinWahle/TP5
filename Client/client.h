#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <curl/curl.h>
#include <string>
using namespace std;

class client {
public:
	/* Esta funcion se encarga de cargar la instancia data con lo recibido por linea de comandos*/
	void setData(string mydata);
	/*Esta funcion recibe los argumentos por linea de comandos y se encarga de realizar todas las
	operaciones desde la conexion hasta la creacion del archivo*/
	void Request(int argc, char* argv[]);
	/*Variables que se pasan a los callbacks para guardar datos que devuelve cURL*/
	string dataRecieved;
	string header;
	/*Callbacks que se pasan en la configuracion de cURL para recibir la informacion*/
	static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userData);
	static size_t header_callback(char* buffer, size_t size, size_t nitems, void* userdata);
private:
	/*Se encarga de configurar las opciones de cURL*/
	void configCurl(CURL* curl, char* argv);
	/*Genera el archivo
	Devuelve 1 si se pudo crear el archivo, y 0 si fallo*/
	int createFile();
	/*Se encarga de separar el nombre del archivo de todo el argumento que recibe por linea de comandos*/
	string fileName();
	/*Para imprimir en la terminal como se llevo a cabo la operacion*/
	void succeded();
	void failed();
	/*Guarda el argumento que se recibe por linea de comandos*/
	string data;
};

#endif //CLIENT_H 