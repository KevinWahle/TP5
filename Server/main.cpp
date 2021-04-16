#include "server.h"
#include "connection.h"
#include "httpserver.h"


int main () {
	Connection myconnection;

	boost::asio::io_context io_context;
	server server(io_context, 80, &myconnection);
	server.startListening();

	while (1) {
		HTTPServer http(&myconnection);
		if (myconnection.isNewRequest()) {
			http.start();
			server.startAnswering();
		}
		io_context.run_one();
	}
}

