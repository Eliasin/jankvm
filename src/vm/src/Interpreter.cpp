#include "Interpreter.hpp"

const Interpreter Interpreter::instance = Interpreter();

const Interpreter& Interpreter::getInstance() {
	return Interpreter::instance;
}

int Interpreter::run(const JavaClass& jclass) const {
	return 0;
}

Interpreter::Interpreter() {}
