#ifndef INTERPRETER_VM
#define INTERPRETER_VM

#include "JavaClass.hpp"

class Interpreter {
	Interpreter();
	static Interpreter instance;
public:
	static const Interpreter& getInstance();
	int run(const JavaClass& jclass) const;
};

#endif
