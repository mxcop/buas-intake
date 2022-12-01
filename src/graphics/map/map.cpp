#include "map.h"

template<class T>
Map<T>::Map(const u16 width, const u16 height)
	: width(width), height(height)
{
	// Initialize the values of the map.
	values = new T[(u64)width * height];
}

template<class T>
Map<T>::Map(const u16 width, const u16 height, const T def)
	: width(width), height(height)
{
	// Initialize the values of the map.
	values = new T[(u64)width * height];

	for (size_t i = 0; i < (u64)width * height; i++)
	{
		*(values + i) = def;
	}
}

template<class T>
Map<T>::Map(const u16 width, const u16 height, const std::initializer_list<T> def)
	: width(width), height(height)
{
	// Initialize the values of the map.
	values = new T[(u64)width * height];

	auto first = def.begin();
	auto last = def.end();

	size_t i = 0;
	while (first != last) {
		*values = *first;
		++values; ++first; ++i;
	}

	for (i; i > 0; i--)
	{
		--values;
	}
}

template<class T>
Map<T>::Map(const u16 width, const u16 height, const std::vector<T> def)
	: width(width), height(height)
{
	// Initialize the values of the map.
	values = new T[(u64)width * height];

	for (size_t i = 0; i < def.size(); i++)
	{
		*(values + i) = def[i];
	}
}

template<class T>
T& Map<T>::operator()(const u16 x, const u16 y) const
{
	return Get(x, y);
}

template<class T>
T& Map<T>::Get(const u16 x, const u16 y) const
{
	return *(values + (u64)y * width + x);
}

template<class T>
void Map<T>::Set(const u16 x, const u16 y, const T& val)
{
	*(values + (u64)y * width + x) = val;
}

template<class T>
Map<T>::~Map()
{
	delete[] values;
}

template class Map<u8>;