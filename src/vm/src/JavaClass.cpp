#include "JavaClass.hpp"

JavaClass::JavaClass(const ConstantPool::Pool& constantPool) : constantPool(constantPool) {}
JavaClass::JavaClass(ConstantPool::Pool&& constantPool) : constantPool(std::move(constantPool)) {}

const ConstantPool::Pool& JavaClass::getConstantPool() const {
	return constantPool;
}
