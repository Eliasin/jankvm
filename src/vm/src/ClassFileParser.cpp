#include "ClassFileParser.hpp"

ClassFileParser::ClassFileParser(std::istream& in) : javaClass({}) {
	if (!in)
		return;

	if (!checkMagicValue(in) || !checkClassVersion(in))
		return;

	ConstantPool constantPool = parseConstantPool(in);
	javaClass = JavaClass(constantPool);
}

std::optional<JavaClass> ClassFileParser::getClass() const {
	if (valid)
		return javaClass;
	return {};
}

bool ClassFileParser::checkMagicValue(std::istream& in) {
	constexpr uint32_t magic = 0xCAFEBABE;
	char buffer[4];
	if (!tryRead(in, buffer, 4)) {
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


bool ClassFileParser::checkClassVersion(std::istream& in) {
	constexpr unsigned int minimumSupportedMajorVersion = 52;
	char minorVersion[2];
	char majorVersion[2];

	bool minorVersionReadSuccess = tryRead(in, minorVersion, 2);
	bool majorVersionReadSuccess = tryRead(in, majorVersion, 2);
	bool versionReadSuccess = minorVersionReadSuccess && majorVersionReadSuccess;
	if (versionReadSuccess && bytesToType<uint16_t, 2>(majorVersion) <= minimumSupportedMajorVersion) {
		return true;
	}

	return false;
}

ConstantPool ClassFileParser::parseConstantPool(std::istream& in) {
	return {};
}

