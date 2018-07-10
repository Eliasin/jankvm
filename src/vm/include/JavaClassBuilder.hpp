#ifndef JAVACLASSBUILDER_VM
#define JAVACLASSBUILDER_VM

#include "JavaClass.hpp"

class JavaClassBuilder {
	ConstantPool constantPool;
public:
	JavaClass getClass();
};

#endif
