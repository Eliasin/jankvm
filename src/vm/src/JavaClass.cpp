#include "JavaClass.hpp"

JavaClass::JavaClass(std::istream& in) {

}

const ConstantPool& JavaClass::getConstantPool() const {
	return constantPool;
}
