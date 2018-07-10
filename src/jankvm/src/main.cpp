#include <string>
#include <fstream>
#include <iostream>
#include <cinttypes>

#include <argparse.hpp>
#include <ClassFileVerifier.hpp>
#include <Interpreter.hpp>
#include <ClassFileParser.hpp>

int main(int argc, const char** argv) {
	ArgumentParser parser;
	parser.addFinalArgument("classFilePath");
	parser.parse(argc, argv);

	std::string classFilePath = parser.retrieve<std::string>("classFilePath");
	std::ifstream file(classFilePath.c_str(), std::ifstream::binary);

	ClassFileParser entrypointParser(file);
	std::optional<JavaClass> entrypoint = entrypointParser.getClass();

	const Interpreter& interpreter = Interpreter::getInstance();
	if (entrypoint) {
		interpreter.run(entrypoint.value());
	}

	return 0;
}
