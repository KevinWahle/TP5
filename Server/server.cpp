#include "server.h"

#include <iostream>
#include <string>
#include <boost\bind.hpp>

using boost::asio::ip::tcp;


server::server(boost::asio::io_context& io_context)
	: context_(io_context),
	acceptor_(io_context, tcp::endpoint(tcp::v4(), 80)),	//Puerto 80
	socket_(io_context)
{
}

server::~server()
{
}

void server::startListening()
{
	if (socket_.is_open())
	{
		socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		socket_.close();
	}
	startWaitingConnection();
}

void server::startWaitingConnection()
{
	std::cout << "startWaitingConnection()" << std::endl;
	if (socket_.is_open())
	{
		std::cout << "Error: Can't accept new connection from an open socket" << std::endl;
		return;
	}
	acceptor_.async_accept(			//solo recibe socket que va a administrar la nueva conexion y el callback
		socket_,
		boost::bind(
			&server::connectionReceived, 
			this,
			boost::asio::placeholders::error
		)
	);
}

void server::startAnswering()
{
	std::cout << "startAnswering()" << std::endl;
	/*
	MANDO EL ARCHIVO
	*/
	boost::asio::async_write(
		socket_,
		boost::asio::buffer(data),
		boost::bind(
			&server::responseSent,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
	socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	socket_.close();
}


void server::connectionReceived(const boost::system::error_code& error)
{
	std::cout << "connectionReceived()" << std::endl;
	/*
	CHEQUEO QUE ESTE BIEN RECIVIDO TODO
	*/
	if (!error) {
		startAnswering();
		startWaitingConnection();
	}
	else {
		std::cout << error.message() << std::endl;
	}
}

void server::responseSent(const boost::system::error_code& error,
	size_t bytes_sent)
{
	std::cout << "responseSent()" << std::endl;
	if (!error) {
		std::cout << "Response sent. " << bytes_sent << " bytes." << std::endl;
	}

}


std::string server::getData()
{
	return data;
}

void server::setData(std::string mydata) {
	data = mydata;
}