#ifndef JAVACLASS_VM
#define JAVACLASS_VM

#include <istream>

#include "ConstantPool.hpp"

class JavaClassBuilder;

class JavaClass {
	ConstantPool::Pool constantPool;
public:
	JavaClass(const ConstantPool::Pool& constantPool);
	JavaClass(ConstantPool::Pool&& constantPool);
	const ConstantPool::Pool& getConstantPool() const;

};

#endif
