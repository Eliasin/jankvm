#include "Interpreter.hpp"

const Interpreter& Interpreter::getInstance() {
	return instance;
}

int Interpreter::run(const JavaClass& jclass) const {
	return 0;
}
