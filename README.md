# 🚀 Curl Clone 🚀

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A blazing-fast C++ implementation of a curl clone that supports HTTP GET, POST, DELETE, and PUT requests. It harnesses the power of the CLI11 library for command line argument parsing and dances with the standard UNIX/Linux system libraries for socket wizardry.

## ✨ Features

- [x] HTTP GET requests
- [x] HTTP POST requests
- [x] HTTP DELETE requests
- [x] HTTP PUT requests
- [x] Custom headers
- [x] Custom data for POST and PUT requests
- [ ] HTTPS support (not implemented yet)

## 🛠️ Dependencies

- [CLI11](https://github.com/CLIUtils/CLI11) - The magical wand for command line argument parsing

## 🚧 Build and Installation

### Prerequisites

- C++ compiler with C++17 support
- CLI11 library, Already enchanted into the mystical realm of 'includes' directory. 🌌✨


### 🛠️ Building from Source

```bash
git clone https://github.com/deepakgohil9/curl-clone.git
cd curl-clone
g++ -std=c++11 main.cpp -o ccurl
```

### 🚀 Usage

```bash
./ccurl [OPTIONS] URL
```

#### 🎉 Options

- `-v,--verbose`: Dump complete request and response.
- `-X, --request`: Specify the request method (GET, POST, PUT, DELETE).
- `-H, --header`: Add a custom header to the request.
- `-d, --data`: Add data to the request body for POST and PUT requests.
- `URL`: The URL to send the request to.

#### 🚀 Examples

```bash
# Perform a GET request
./ccurl http://eu.httpbin.org/get 

# Perform a POST request with custom headers and data
./ccurl -X POST http://eu.httpbin.org/post \
-d '{"key": "value"}' \
-H "Content-Type: application/json"

# Perform a PUT request with custom headers and data
./ccurl -X PUT http://eu.httpbin.org/put \ 
-d '{"key": "value"}' \
-H "Content-Type: application/json"

# Perform a DELETE request
./ccurl -X DELETE http://eu.httpbin.org/delete 
```

## 🤝 Contributing

Contributions are more than welcome! If you find any issues or have suggestions for intergalactic improvements, please open an issue or submit a pull request.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙌 Acknowledgments

- [CLI11](https://github.com/CLIUtils/CLI11) library for providing a user-friendly command line interface.
