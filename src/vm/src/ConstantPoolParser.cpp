#include "ConstantPoolParser.hpp"

#include <data_utils.hpp>

std::optional<ConstantPool::Pool> ConstantPoolParser::parseConstantPool(std::istream& in) {
	using namespace ConstantPool;
	Pool constantPool;
	char numEntriesBuffer[2];

	if (!tryRead(in, numEntriesBuffer, 2))
		valid = false;
	return {};

	ConstantPool::Pool::size_type numEntries = bytesToType<uint16_t, 2>(numEntriesBuffer);
	for (ConstantPool::Pool::size_type entryNumber = 0; entryNumber < numEntries; entryNumber++) {
		constantPool.push_back(parseEntry(in));
	}

	return valid ? Pool{constantPool} : Pool{};
}

ConstantPool::Entry ConstantPoolParser::parseEntry(std::istream& in) {
	using namespace ConstantPool;
	constexpr uint8_t tagSize = 1;
	char tagBuffer[tagSize];
	if (!tryRead(in, tagBuffer, tagSize))
		valid = false;
	return {};
	unsigned char tag = bytesToType<unsigned char, tagSize>(tagBuffer);

	switch(tag) {
		case CONSTANT_Class:
			{
				constexpr uint8_t indexSize = 2;
				char buf[indexSize];
				if (!tryRead(in, buf, indexSize)) {
					valid = false;
					return {};
				}

				Index index = bytesToType<Index, indexSize>(buf);
				return {ClassInfo{index}};
				break;
			}
		case CONSTANT_Fieldref:
		case CONSTANT_Methodref:
		case CONSTANT_InterfaceMethodref:
			{
				constexpr uint8_t indexSize = 2;
				char classIndexBuf[indexSize];
				char nameAndTypeIndexBuf[indexSize];
				if (!tryRead(in, classIndexBuf, indexSize) || !tryRead(in, nameAndTypeIndexBuf, indexSize)) {
					valid = false;
					return {};
				}

				Index classIndex = bytesToType<Index, indexSize>(classIndexBuf);
				Index nameAndTypeIndex = bytesToType<Index, indexSize>(nameAndTypeIndexBuf);
				return {ReferenceInfo{static_cast<Tag>(tag), classIndex, nameAndTypeIndex}};
				break;
			}
		case CONSTANT_String:
			{
				constexpr uint8_t indexSize = 2;
				char buf[indexSize];
				if (!tryRead(in, buf, indexSize)) {
					valid = false;
					return {};
				}

				Index stringIndex = bytesToType<Index, indexSize>(buf);
				return {StringInfo{stringIndex}};
				break;
			}
		case CONSTANT_Integer:
			{
				constexpr uint8_t intSize = 4;	
				char buf[intSize];
				if (!tryRead(in, buf, intSize)) {
					valid = false;
					return {};
				}

				uint32_t data = bytesToType<uint32_t, intSize>(buf);
				return {data};
				break;
			}
		case CONSTANT_Float:
			{
				constexpr uint8_t floatSize = 4;
				char buf[floatSize];
				if (!tryRead(in, buf, floatSize)) {
					valid = false;
					return {};
				}

				float data = bytesToType<float, floatSize>(buf);
				return {data};
				break;
			}
		case CONSTANT_Long:
			{
				constexpr uint8_t longSize = 8;
				char buf[longSize];

				if (!tryRead(in, buf, longSize)) {
					valid = false;
					return {};
				}
				
				uint64_t data = bytesToType<uint64_t, longSize>(buf);
				return {data};
				break;
			}
		case CONSTANT_Double:
			{
				constexpr uint8_t doubleSize = 8;
				char buf[doubleSize];

				if (!tryRead(in, buf, doubleSize)) {
					valid = false;
					return {};
				}

				double data = bytesToType<double, doubleSize>(buf);
			   	return {data};	
				break;
			}
		case CONSTANT_NameAndType:
			{
				break;
			}
		case CONSTANT_Utf8:
			{
				constexpr uint8_t lengthSize = 2;
				char lenBuf[lengthSize];
				if (!tryRead(in, lenBuf, lengthSize)) {
					valid = false;
					return {};
				}

				uint16_t len = bytesToType<uint16_t, lengthSize>(lenBuf);

				char strBuf[len];
				if (!tryRead(in, strBuf, len)) {
					valid = false;
					return {};
				}

				return {std::string{strBuf}};
				break;
			}
		case CONSTANT_MethodHandle:
			break;
		case CONSTANT_MethodType:
			break;
		case CONSTANT_InvokeDynamic:
			break;
		default:
			valid = false;
			std::cerr << "Error: Unkown/Invalid constant pool entry tag" << std::endl;
			break;
	}

	return {};
}

