#include <string>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <cinttypes>
#include <limits>

#include <argparse.hpp>
#include <boost/predef/other/endian.h>


template <typename T, size_t N>
void reverseArray(T array[N]) {
	static_assert(std::numeric_limits<std::ptrdiff_t>::max() >= 0, "std::ptrdiff_t max size invariant violated");
	static_assert(sizeof(size_t) >= sizeof(std::ptrdiff_t), "size_t must be at least equal in size to std::ptrdiff_t");
	static_assert(N < static_cast<size_t>(std::numeric_limits<std::ptrdiff_t>::max()), "Narrowing conversion from size_t to std::ptrdiff_t");
	for (std::ptrdiff_t i = 0; i < static_cast<std::ptrdiff_t>(N / 2); i++) {
		T temp = array[i];
		array[i] = array[static_cast<std::ptrdiff_t>(N) - i - 1];
		array[static_cast<std::ptrdiff_t>(N) - i - 1] = temp;
	}
}


template <typename T, size_t N>
T bytesToType(const char bytes[N]) {
	static_assert(N > 0, "Attempted cast of zero bytes to type");
	static_assert(sizeof(T) == N, "Attempted cast from bytes to type of incompatible size");
	T result;

	char endianAdjustedBytes[N];
	memcpy(endianAdjustedBytes, bytes, N);

	if (BOOST_ENDIAN_LITTLE_BYTE) {
		reverseArray<char, N>(endianAdjustedBytes);
	}

	memcpy(&result, endianAdjustedBytes, N);
	return result;
}


bool tryRead(std::istream& in, char* buffer, size_t n) {
	if (!in.read(buffer, n)) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return false;
	}
	return true;
}


bool checkForMagicValue(std::ifstream& file) {
	constexpr int magic = 0xCAFEBABE;
	char buffer[4];
	if (!tryRead(file, buffer, 4)) {
		return false;
	}
	else if (bytesToType<uint32_t, 4>(buffer) == magic) {
		return true;
	}
	else {
		std::cerr << "Error: Invalid file format " << std::endl;
		return false;
	}

}


bool checkClassFileVersion(std::ifstream& file) {
	constexpr unsigned int minimumSupportedMajorVersion = 52;
	char minorVersion[2];
	char majorVersion[2];

	bool minorVersionReadSuccess = tryRead(file, minorVersion, 2);
	bool majorVersionReadSuccess = tryRead(file, majorVersion, 2);
	bool versionReadSuccess = minorVersionReadSuccess && majorVersionReadSuccess;
	if (versionReadSuccess && bytesToType<uint16_t, 2>(majorVersion) <= minimumSupportedMajorVersion) {
		return true;
	}

	return false;
}


bool verifyClassFile(std::ifstream& file) {
	if (!file) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return false;
	}

	if (!checkForMagicValue(file)) {
		return false;
	}

	if (!checkClassFileVersion(file)) {
		return false;
	}

	return true;
}


int main(int argc, const char** argv) {
	ArgumentParser parser;
	parser.addFinalArgument("classFilePath");
	parser.parse(argc, argv);

	std::string classFilePath = parser.retrieve<std::string>("classFilePath");
	std::ifstream file(classFilePath.c_str(), std::ifstream::binary);

	std::cout << verifyClassFile(file) << std::endl;

	return 0;
}
