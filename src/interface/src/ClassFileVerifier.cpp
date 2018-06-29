#include "ClassFileVerifier.hpp"


bool ClassFileVerifier::checkForMagicValue(std::ifstream& file) {
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


bool ClassFileVerifier::checkClassVersion(std::ifstream& file) {
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


bool ClassFileVerifier::isValid(std::ifstream& file) {
	if (!file) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return false;
	}

	if (!ClassFileVerifier::checkForMagicValue(file)) {
		return false;
	}

	if (!ClassFileVerifier::checkClassVersion(file)) {
		return false;
	}

	return true;
}

