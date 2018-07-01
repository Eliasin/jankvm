#ifndef JANKVM_DATA_UTILS
#define JANKVM_DATA_UTILS

#include <type_traits>
#include <limits>
#include <cerrno>
#include <cstring>
#include <iostream>

#include <boost/predef/other/endian.h>


inline bool tryRead(std::istream& in, char* buffer, size_t n) {
	if (!in.read(buffer, n)) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return false;
	}
	return true;
}


template <typename T, size_t N>
void reverseArray(T array[N]) {
	static_assert(std::numeric_limits<std::ptrdiff_t>::max() >= 0, "std::ptrdiff_t max size invariant violated");
	static_assert(sizeof(size_t) >= sizeof(std::ptrdiff_t), "size_t must be at least equal in size to std::ptrdiff_t");
	static_assert(N < static_cast<size_t>(std::numeric_limits<std::ptrdiff_t>::max()), "Narrowing conversion from size_t to std::ptrdiff_t");
	for (std::ptrdiff_t i = 0; i < static_cast<std::ptrdiff_t>(N / 2); i++) {
		T temp = array[i];
		array[i] = array[static_cast<std::ptrdiff_t>(N) - i - 1];
		array[static_cast<std::ptrdiff_t>(N) - i - 1] = temp;
	}
}


template <typename T, size_t N, std::enable_if<std::is_trivial<T>::value>* = nullptr>
T bytesToType(const char bytes[N]) {
	static_assert(N > 0, "Attempted cast of zero bytes to type");
	static_assert(sizeof(T) == N, "Attempted cast from bytes to type of incompatible size");

	T result;

	char endianAdjustedBytes[N];
	memcpy(endianAdjustedBytes, bytes, N);

	if (BOOST_ENDIAN_LITTLE_BYTE) {
		reverseArray<char, N>(endianAdjustedBytes);
	}

	memcpy(&result, endianAdjustedBytes, N);
	return result;
}


#endif
