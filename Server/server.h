#ifndef _SERVER_H 
#define _SERVER_H 

#include <boost\asio.hpp>
#include <string>
#include "connection.h"

class server 
{
public:
	server(boost::asio::io_context& context, int port, Connection* ptr);
	~server();

	void startListening();
	std::string getData();
	void setData(std::string data);

private:
	void startWaitingConnection();
	void startAnswering();
	void connectionReceived_cb(const boost::system::error_code& error);
	void dataReceived_cb(const boost::system::error_code& error, std::size_t size);
	void responseSent_cb(const boost::system::error_code& error, size_t bytes_sent);
	//void stopListening();

	std::string data;
	std::sting answer;
	Connection* connection;
	boost::asio::io_context& context_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::strambuf mybuffer;
}

#endif /* _SERVER_H */