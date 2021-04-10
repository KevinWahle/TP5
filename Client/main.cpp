
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
