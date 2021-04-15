#include "client.h"

#include <iostream>
#include <fstream>

using namespace std;


//llena la instancia de la clase
void client::setData(string mydata) {
	data= mydata;
}

void client::Request(int argc, char* argv[]) {

	//inicializacion y creo el handler
	CURLcode error;
	CURL* curl; 
	error = curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	//si se inicializo se configura curl
	if ((error == CURLE_OK) && (curl)) {
		configCurl(curl, argv[1]);
	}
	error = curl_easy_perform(curl); 

	//si se logro la conexion 
	if (error == CURLE_OK) {
		
		//se crea el archivo
		if (createFile()) {
			succeded();
		}
		else {
			failed();
		}
	}
	//si fallo algo de la conexion
	else {
		failed();
	}
	//
	curl_global_cleanup();
	curl_easy_cleanup(curl);
}

//se configura los datos con los que vamos a trabajar en curl
void client::configCurl(CURL* curl, char* argv) {
	curl_easy_setopt(curl, CURLOPT_URL, argv); 
	curl_easy_setopt(curl, CURLOPT_PORT, 80);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); 
	curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataRecieved);
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);
}

//callbacks que usa curl para entregar los punteros con la informacion
size_t client::writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	((std::string*)userdata)->append(ptr, size * nmemb);
	return size * nmemb;
}

size_t client::header_callback(char* buffer, size_t size, size_t nitems, void* userdata) {
	((std::string*)userdata)->append(buffer, size * nitems);
	return size * nitems;
}

//mensajes para identificar desde la terminal si se logro la operacion
void client::succeded() {
	cout << "The operation has succeded" << endl;
}

void client::failed() {
	cout << "The operation has failed" << endl;
}

//esta funcion crea el archivo
int client::createFile() {
	int succeed = 1;
	string str(header);
	string filename(fileName());
	ofstream file;
	file.open(filename, ios::out | ios::binary);

	//Si no se encuentra este mensaje, es porque se encontro el archivo
	if (str.find("404 Not Found") == string::npos) 
	{
		//Se completa el contenido en el archivo
		cout << "The file was found" << endl;
		file << dataRecieved;
	}
	//Si no se encontro devolvemos el 404 Not Found
	else if (str.find("202 OK") == string::npos) 
	{
		cout << "The file was not found" << endl;
		file << header;
	}
	//Si fallo crear el archivo
	if (file.fail())
	{
		succeed = 0;
	}
	file.close();
	return succeed;
	//devuelve 1 si se pudo crear el file, cero si no
}

//Esta funcion separa el nombre de lo que recibio por linea de commandos
string client::fileName() {
	string str(data);
	int i = data.size() - 1;
	//recorre lo ingresado de atras para adelante hasta el inicio del nombre del archivo
	while (data[i] != '/') {
		i--;
	}
	string name = str.erase(0, i + 1);
	return name;
}

