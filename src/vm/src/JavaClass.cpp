#include "JavaClass.hpp"

JavaClass::JavaClass(ConstantPool constantPool) : constantPool(std::move(constantPool)) {}

const ConstantPool& JavaClass::getConstantPool() const {
	return constantPool;
}
