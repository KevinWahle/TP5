#include "server.h"
#include "connection.h"
#include "httpserver.h"


int main () {
	Connection myconnection;

	boost::asio::io_context io_context;
	server server(io_context, 80, &myconnection);
	server.startListening();
	io_context.run();
	
	HTTPServer http (&myconnection);
	std::cout << "casi entre a http" << std::endl;

	while (myconnection.isNewRequest()){
		std::cout << "entre a http" << std::endl;

		http.start();
	}
}

