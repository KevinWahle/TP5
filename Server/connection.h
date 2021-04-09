#ifndef __CONNECTION_H
#define __CONNECTION_H

#include <string>

class Connection {
public:

	Connection();

	string getData();
	void setData();

	bool sendData();
	bool disconnect();
	bool isNewData();
	bool isFinished();

private:
	string path;
	string filename;
	bool send;
	bool disconnect;
	bool newData;
	bool finished;
}


#endif

