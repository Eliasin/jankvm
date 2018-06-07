#include <string>
#include <fstream>
#include <iostream>
#include <cinttypes>

#include <argparse.hpp>
#include <data_utils.hpp>

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
