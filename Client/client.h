#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <curl/curl.h>
#include <string>
using namespace std;

class client {
public:
	void setData(string mydata);
	void Request(int argc, char* argv[]);
	string dataRecieved;
	string header;
	static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userData);
	static size_t header_callback(char* buffer, size_t size, size_t nitems, void* userdata);
private:
	void configCurl(CURL* curl, char* argv);
	int createFile();
	string fileName();
	void succeded();
	void failed();
	string data;
};

#endif //CLIENT_H 