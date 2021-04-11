#include "server.h"
#include "connection.h"
#include "httpserver.h"


int main () {
	Connection myconnection;

	boost::asio::io_context io_context;
	server server(io_context, 80, &myconnection);
	server.startListening();
	io_context.run();
	//LLAMAR A FUNCIONES DE HTTPSERVER Y CARGAR/LEER DATOS DE MYCONNECTION
}
/*
///////////////////// Servidor
class server{
	startListening();
	
	start_waiting_connection();

	conectionReceived();

	start_answering();

	stopListening();

	getData()

	setData()

	string data;
}


class connection{
	getData();
	sendData();
	disconnect();
	isNewData();
	isFinished();
}


class HTTP {
	checkInfo();
	setInfo();
}




*/