#ifndef __CONNECTION_H
#define __CONNECTION_H

#include <string>

class Connection {
public:

	Connection();

	string getData();
	void setData();

	void sendData();
	void disconnect();
	bool isNewData();
	bool isFinished();

private:
	string data;
	bool send;
	bool disconnect;
	bool newData;
	bool finished;
}


#endif

