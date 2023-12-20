#include <string>
#include <regex>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define RESPONSE_BUFFER_LEN 1024
#define DELIMITER "\r\n\r\n"
#define DELIMITER_LEN 4

class Url
{
public:
	std::string url;
	bool is_valid;
	std::string protocol;
	std::string hostname;
	int port;
	std::string path;
	std::string query_str;
	std::string fragment;

	Url(std::string &url)
	{
		std::smatch matches;
		std::regex url_pattern(R"(((https?):\/\/)?([^\s\/:]+):?([0-9]+)?([^\s\?#]*)?\??([^#\s]*)?(#.*)?)");

		this->is_valid = std::regex_search(url, matches, url_pattern);

		if (!this->is_valid)
			throw std::runtime_error("Inavlid URL");

		this->url = matches[0].str();
		this->protocol = matches[2].str().empty() ? "http" : matches[2].str();
		this->hostname = matches[3].str();
		this->port = matches[4].str().empty() ? 80 : std::stoi(matches[4]);
		this->path = matches[5].str().empty() ? "/" : matches[5].str();
		this->query_str = matches[6].str();
		this->fragment = matches[7].str();
	}

	std::string http_request(std::string &verb, std::string *data, std::vector<std::string> *headers)
	{
		std::string request = verb + " ";
		request += this->path + " HTTP/1.1\r\n";
		request += "Host: " + this->hostname + "\r\n";
		request += "Accept: */*\r\n";
		request += "Connection: close\r\n";

		if (headers != nullptr)
		{
			for (int i = 0; i < headers->size(); i++)
				request = request + (*headers)[i] + "\r\n";
		}

		if (data != nullptr)
		{
			request += "Content-Length: " + std::to_string(data->length()) + "\r\n";
			request = request + "\r\n" + *data + "\r\n";
		}

		request += "\r\n";

		return request;
	}
};

class Http_Client : public Url
{
private:
	int sock;
	struct sockaddr_in server;

public:
	Http_Client(std::string &url) : Url(url)
	{
		struct addrinfo hints, *result;
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;

		int status = getaddrinfo(this->hostname.c_str(), NULL, &hints, &result);
		if (status != 0)
			throw std::runtime_error("Failed to resolve domain! \ngetaddrinfo error: " + std::string(gai_strerror(status)));

		memcpy(&server, result->ai_addr, sizeof(struct sockaddr_in));
		server.sin_family = AF_INET;
		server.sin_port = htons(this->port);
		freeaddrinfo(result);
	}

	void connect()
	{
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == -1)
			throw std::runtime_error("Failed to create socket!. \n error no: " + std::string(std::strerror(errno)));

		if (::connect(this->sock, reinterpret_cast<struct sockaddr *>(&server), sizeof(server)) == -1)
			throw std::runtime_error("Failed to connect socket!. \n error no: " + std::string(std::strerror(errno)));
	};

	void close()
	{
		::close(sock);
	};

	std::string send(std::string &verb, std::string *data, std::vector<std::string> *headers, bool verbose = false)
	{
		connect();
		std::string request_str = this->http_request(verb, data, headers);

		if (::send(sock, request_str.c_str(), request_str.length(), 0) < 0)
			throw std::runtime_error("Failed to connect socket!. \n error no: " + std::string(std::strerror(errno)));

		char response_buff[RESPONSE_BUFFER_LEN];
		std::string response = "";
		while (recv(sock, response_buff, RESPONSE_BUFFER_LEN, 0) > 0)
		{
			response += response_buff;
			memset(response_buff, '\0', RESPONSE_BUFFER_LEN);
		}

		close();
		int pos = response.find(DELIMITER);
		return verbose ? request_str + response : response.substr(pos + DELIMITER_LEN, response.length());
	}
};