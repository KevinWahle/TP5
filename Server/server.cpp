#include "server.h"
#include <iostream>
#include <string>
#include <boost\bind.hpp>
using boost::asio::ip::tcp;


server::server(boost::asio::io_context& io_context, int port, Connection* ptr)
	: context_(io_context),
	acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),	//Puerto 80
	socket_(io_context)
{
	connection = ptr;
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
	mybuffer.consume(mybuffer.size());
	startWaitingConnection();
}


void server::startWaitingConnection()
{
	std::cout << "Start waiting for connection" << std::endl;
	if (socket_.is_open())
	{
		std::cout << "Error: Can't accept new connection from an open socket" << std::endl;
		return;
	}
	acceptor_.async_accept(
		socket_,
		boost::bind(
			&server::connectionReceived_cb,
			this,
			boost::asio::placeholders::error
		)
	);
}

void server::connectionReceived_cb(const boost::system::error_code& error)
{
	if (!error) {
		std::cout << "connection Received" << std::endl;

		boost::asio::async_read_until(socket_, mybuffer, "\r\n\r\n",
			boost::bind(&server::dataReceived_cb,
				this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	else {
		std::cout << error.message() << std::endl;
	}
}

void server::dataReceived_cb(const boost::system::error_code& error, std::size_t size)
{
	if (!error) {
		connection->setRequest(boost::asio::buffer_cast<const char*>(mybuffer.data()));
	}
	else {
		std::cout << error.message() << std::endl;
	}
}

void server::startAnswering()
{
	std::cout << "start Answering" << std::endl;
	{ 
		answer = connection->getResponse();
		//std::cout << answer << std::endl;
		boost::asio::async_write(
			socket_,
			boost::asio::buffer(answer),
			boost::bind(
				&server::responseSent_cb,
				this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
	}
}

void server::responseSent_cb(const boost::system::error_code& error, size_t bytes_sent)
{
	if (!error) {
		std::cout << "Response sent. " << bytes_sent << " bytes." << std::endl;
	}
	else {
		std::cout << error.message() << std::endl;
	}
	socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);	//Ends the connection
	socket_.close();

	startListening();

}

std::string server::getData()
{
	return data;
}

void server::setData(std::string mydata) {
	data = mydata;
}