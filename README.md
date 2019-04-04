[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# C++ Microservice Template

This library is developed to allow for the rapid implementation of a microservice using the [C++ REST SDK](https://github.com/Microsoft/cpprestsdk).

## Getting Started

### Prerequisites

This project has the following dependencies:

- [C++ REST SDK](https://github.com/Microsoft/cpprestsdk)
- [Boost](https://github.com/boostorg/boost)
- [OpenSSL](https://github.com/boostorg/boost)

Dependencies can be installed on Ubuntu using the following command:

```bash
sudo apt install cmake libssl-dev libboost-all-dev libcpprest-dev
```

### Adding to your project

The reccommended way to add this library to you project is by including the following to your CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.13)
project(myProject)

include_directories("path/to/cppmsa-template/include")
add_subdirectory("path/to/cppmsa-template")

add_executable(myProject myProject_SOURCES)
# or `add_library(myProject myProject_SOURCES)`

target_link_libraries(myProject staticspecrank)
```

### Usage

When using this library, create a child class of cppmsa::MainServiceController with your custom overrides of the available HTTP requests.

An example deployment using this library can be found in [tests/src/testDeploy.cc](tests/src/testDeploy.cc)

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](tags).

## Authors

- **Patrick Cox** - [paddy74](https://github.com/paddy74)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgements

This project is based largely on [ivanmejiarocha/micro-service](https://github.com/ivanmejiarocha/micro-service).
