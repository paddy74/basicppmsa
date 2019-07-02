[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# C++ Microservice Template

This library is developed to allow for the rapid implementation of a microservice using the [C++ REST SDK](https://github.com/Microsoft/cpprestsdk).

## Getting Started

### Prerequisites

This project has the following dependencies:

- [Boost](https://github.com/boostorg/boost)
- [Libwebsockets](https://github.com/warmcat/libwebsockets)
- [OpenSSL](https://github.com/boostorg/boost)
- [C++ REST SDK](https://github.com/Microsoft/cpprestsdk)

Dependencies can be installed on Ubuntu using the following command:

```bash
sudo apt install libboost-atomic-dev libboost-thread-dev libboost-system-dev libboost-date-time-dev libboost-regex-dev libboost-filesystem-dev libboost-random-dev libboost-chrono-dev libboost-serialization-dev libwebsocketpp-dev openssl libssl-dev libcpprest-dev -y
```

The following requires fewer compiler flags through the use of `-DWERROR=OFF`.

This project also supports building the dependencies Boost and C++ REST SDK from source by using `cmake .. -DUSE_SYSTEM_BOOL=OFF -DUSE_SYSTEM_CPPRESTSDK=OFF`. In this case the dependencies for Libwebsockets and OpenSSL will still need to exist on system.

### Adding to your project

The reccommended way to add this library to you project is by including the following to your CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.13)
project(myProject)

include_directories("path/to/msabase/include")
add_subdirectory("path/to/msabase")

add_executable(myProject myProject_SOURCES)
# or `add_library(myProject myProject_SOURCES)`

target_link_libraries(myProject msabase)
```

### Usage

When using this library, create a child class of msabase::MainServiceController with your custom overrides of the available HTTP requests.

An example deployment using this library can be found in [tests/src/testDeploy.cc](tests/src/testDeploy.cc)

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](tags).

## Authors

- **Patrick Cox** - [paddy74](https://github.com/paddy74)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgements

This project is based largely on [ivanmejiarocha/micro-service](https://github.com/ivanmejiarocha/micro-service).
