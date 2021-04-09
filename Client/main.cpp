
#include <curl>



class client {
public:
	getData();
	setData(string mydata) {
		Data = mydata;
	}
	Request();
	succeded();
	failed();
private:
	string Data;
}

void client::getData(int argc, char* argv[]) {


}

void client::Request() {

	//inicializacion y creo el handler
	CURLcode error;
	CURL* curl;  //handler
	error = curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	if ((error == CURLE_OK) && (curl)) {
		curl_easy_setopt(curl, CURLOPT_URL, "localhost"); //configuracion
		curl_easy_setopt(curl, CURLOPT_PORT, 80);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //o =1L
		curl_easy_setopt(curl, CURLOPT_PROTOCOL, CURLPROTO_HTTP); //o http
		//CURLOPT_WRITE FUNCTION: Curl llama a un callback nuestro cuando recibe información del servidor, como en el caso de parseCmdLine(), le pasamos ese callback: 
		//size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
		//CURLOPT_WRITEDATA: equivalente a userData, aquí curl guarda la información recibida, le debemos pasar un buffer.
	}
	error = curl_easy_perform(curl);
	if (error == CURLE_OK) {
		//los resultados estan en el buffer q yo mande en el callback
		succeded();
	}
	else {
		failed();
	}
	curl_global_cleanup();
	curl_easy_cleanup(curl);
}
