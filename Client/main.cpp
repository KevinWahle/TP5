
#include "client.h"

using namespace std;

int main(int argc, char* argv[]) {

	//verifica que se haya ingresado solo un argumento (que corresponde al formato que se espera)
	if (argc == 2) {
		client Client;
		//guardo lo ingresado por linea de comandos
		Client.setData(argv[1]);
		//llamo a la conexion
		Client.Request(argc, argv);
	}
	else {
		cout << "The arguments are not valid" << endl;
	}
	cin.get(); //Esta linea esta para evitar que se cierre la terminal (bug de IDE) una vez que se termine ejecutar el client

}
