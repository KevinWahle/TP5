#include "client.h"

#include <iostream>
#include <fstream>

using namespace std;


void client::setData(string mydata) {
	data = mydata;
}

//string client::getData() {
//	return Data;
//}

void client::Request(int argc, char* argv[]) {

	//inicializacion y creo el handler
	CURLcode error;
	CURL* curl;  //handler
	error = curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	if ((error == CURLE_OK) && (curl)) {
		configCurl(curl, argv[1]);
	}
	error = curl_easy_perform(curl);

	if (error == CURLE_OK) {
		//los resultados estan en el buffer q yo mande en el callback
		if (createFile()) {
			succeded();
		}
		else {
			failed();
		}
	}
	else {
		failed();
	}
	curl_global_cleanup();
	curl_easy_cleanup(curl);
}

size_t client::writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	((std::string*)userdata)->append(ptr, size * nmemb);
	return size * nmemb;
}


void client::configCurl(CURL* curl, char* argv) {
	curl_easy_setopt(curl, CURLOPT_URL, argv); //configuracion
	curl_easy_setopt(curl, CURLOPT_PORT, 80);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //o =1L
	curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP); //o http
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataRecieved);
}

void client::succeded() {
	cout << "The operation has succeded" << endl;
}

void client::failed() {
	cout << "The operation has failed" << endl;
}

int client::createFile() {
	ofstream outfile(fileName());
	outfile << dataRecieved;
	outfile.close();
	return 1; //devuelve 1 si se pudo crear el file, cero si no
}

string client::fileName() {
	string str(data);
	int i = data.size() - 1;
	while (data[i] != '/') {
		i--;
	}
	string name = str.erase(0, i + 1);
	return name;
}

