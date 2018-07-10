#include "JavaClassBuilder.hpp"

JavaClass JavaClassBuilder::getClass() {
	return JavaClass(std::move(constantPool));
}
