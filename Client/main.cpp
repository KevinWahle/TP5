
#include <curl/curl.h>









class client {
public:
	void getData();
	void setData(string mydata) {
		Data = mydata;
	}
	void Request();
private:
	void succeded();
	void failed();
	string Data;
}

void client::getData(int argc, char* argv[]) {
	

	if (argc>1){
		//error
	}
	else {
		setData(argv);
	}

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

void client:: succeded(){
	
	

}