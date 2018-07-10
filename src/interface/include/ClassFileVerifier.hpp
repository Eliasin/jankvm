#ifndef JANKVM_VERIFIER
#define JANKVM_VERIFIER

#include <fstream>

class ClassFileVerifier {
public:
	static bool isValid(std::ifstream& file);
	ClassFileVerifier() = delete;
private:
	static bool checkForMagicValue(std::ifstream& file);
	static bool checkClassVersion(std::ifstream& file);
};

#endif
