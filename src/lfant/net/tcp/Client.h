
#pragma once
#include <lfant/stdafx.h>

// External
#include <boost/asio.hpp>
#include <array>

// Internal
#include <lfant/net/tcp/Connection.h>

namespace lfant {
namespace net {
namespace tcp {

/**
 *	Allows broadcasting, multicasting, and onecasting.
 */
class Client : public Connection
{
public:
	Client();
	Client(asio::io_service& io);
	virtual ~Client();

//	void Save(Properties* prop);
//	void Load(Properties* prop);

	// Main Loop Functions
	virtual void Init();
	virtual void OnDestroy();

	// Networking Functions
	void Connect(string host = "127.0.0.1", uint16 port = 22222, string password = "");
	void Disconnect();

	void SendFile(string path, string outpath = "");

	// Asio Callbacks
	virtual void OnConnect(const boost::system::error_code& error);
	virtual void OnGetData(const boost::system::error_code &error);

//	asio::ip::tcp::acceptor acceptor;
//	asio::ip::tcp::socket socket;
	asio::ip::tcp::resolver resolver;
	asio::ip::tcp::resolver::iterator iterator;
	asio::ip::tcp::endpoint endpoint;

private:

	string lastType = "";
	string lastPath = "";
//	uint32 peers = 0;
};

}
}
}