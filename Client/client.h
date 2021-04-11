#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <curl/curl.h>
#include <sting>


class client {
public:
	string getData();
	void setData(string mydata);
	void Request(int argc, char* argv[]);
private:
	void configCurl();
	void succeded();
	void failed();
	string Data;
}


#endif 