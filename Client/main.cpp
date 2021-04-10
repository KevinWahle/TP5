
#include <curl/curl.h>
#include "client.h"



int main(int argc, char* argv[]) {

	if (argc == 2) {
		client Client;
		Client.setData(argv[1]);
		Client.Request();
	}
	else {
		cout << "The arguments are not valid\n" << endl;
	}
}





class client {
public:
	string getData();
	void setData(string mydata);
	void Request(); 
private:
	void configCurl();
	void succeded();
	void failed();
	string Data;
}
