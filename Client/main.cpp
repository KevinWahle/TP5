
#include "client.h"

using namespace std;

int main(int argc, char* argv[]) {

	if (argc == 2) {
		client Client;
		Client.setData(argv[1]);
		Client.Request(argc, argv);
	}
	else {
		cout << "The arguments are not valid" << endl;
	}
	cin.get(); //Esta linea esta para evitar que se cierre la terminal (bug de IDE) una vez que se termine ejecutar el client

}
