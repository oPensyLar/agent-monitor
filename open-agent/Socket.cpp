#include "Socket.h"

int Socket::DeployServer(std::string ipAddr, int port)
{
	
	// Setup socket
	JsonParser jParser;
	kn::socket<kissnet::protocol::tcp> server(kn::endpoint(REAL_ENDPOINT));
	server.bind();
	server.listen();

	// Buffer vectors
	kn::buffer<1024> recvPayload;

	while (1)
	{
		kn::socket client = server.accept();

		auto req_data = client.get_bind_loc();
		std::cout << "[+] Request from:: " << req_data.address << ":" << req_data.port << std::endl;

		// Recv first package
		const auto [data_size, status_code] = client.recv(recvPayload);

		//To print it as a good old C string, add a null terminator
		if (data_size < recvPayload.size())
			recvPayload[data_size] = std::byte{ '\0' };			

		jParser.SetAuthPass(cfg.GetPwdAtuh());
		jParser.ParserRequest(recvPayload);

		std::string respStr = jParser.GetResponse();
		client.send(reinterpret_cast<const std::byte*>(respStr.c_str()), respStr.size());

		client.close();

		
	}

	return 0;
}


void Socket::SetCfg(JsonParser jCfg)
{
	cfg = jCfg;
}
