#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <curl/curl.h>
#include <string>
using namespace std;

class client {
public:
	//string getData();
	void setData(string mydata);
	void Request(int argc, char* argv[]);
	string dataRecieved;
	static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userData);
private:
	void configCurl(CURL* curl, char* argv);
	int createFile();
	string fileName();
	void succeded();
	void failed();
	string data;
};

#endif //CLIENT_H 