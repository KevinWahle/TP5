
#include <curl/curl.h>









class client {
public:
	string getData();
	void setData(string mydata);
	void Request();
private:
	void succeded();
	void failed();
	void configCurl();
	string Data;
}
