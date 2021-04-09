#ifndef _SERVER_H 
#define _SERVER_H 

#include <boost\asio.hpp>
#include <string>

class server 
{
public:
	server(boost::asio::io_context& context);
	~server();

	void startListening();
	std::string getData();
	void setData(std::string data);

private:
	void startWaitingConnection();
	void connectionReceived(const boost::system::error_code& error);
	void startAnswering();
	void responseSent(const boost::system::error_code& error, size_t bytes_sent);
	void stopListening();

	std::string data;

	boost::asio::io_context& context_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::acceptor acceptor_;
}

#endif /* _SERVER_H */