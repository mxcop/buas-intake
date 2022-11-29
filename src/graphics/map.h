#pragma once
#include <cstdio> // printf
#include <vector>

typedef unsigned int uint;

template <typename T>
class Map {
public:
	// Using unsigned int for the size because I won't be using huge maps.
	Map(const uint width, const uint height);
	Map(const uint width, const uint height, const T def);
	Map(const uint width, const uint height, const std::initializer_list<T> def);
	Map(const uint width, const uint height, const std::vector<T> def);

	T& operator() (const uint x, const uint y) const;

	/// <summary>
	/// Get a value from a position within the map.
	/// </summary>
	T& Get(const uint x, const uint y) const;

	/// <summary>
	/// Set a value in a position within the map.
	/// </summary>
	void Set(const uint x, const uint y, const T& val);

	virtual ~Map();

protected:
	T* values = nullptr;
	uint width = 0;
	uint height = 0;
};

template<typename T>
inline Map<T>::Map(const uint width, const uint height)
	: width(width), height(height)
{
	// Initialize the values of the map.
	values = new T[width * height];
}

template<typename T>
inline Map<T>::Map(const uint width, const uint height, const T def)
	: width(width), height(height)
{
	// Initialize the values of the map.
	values = new T[width * height];

	for (size_t i = 0; i < width * height; i++)
	{
		*(values + i) = def;
	}
}

template<typename T>
inline Map<T>::Map(const uint width, const uint height, const std::initializer_list<T> def)
	: width(width), height(height)
{
	// Initialize the values of the map.
	values = new T[width * height];

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

template<typename T>
inline Map<T>::Map(const uint width, const uint height, const std::vector<T> def)
	: width(width), height(height)
{
	// Initialize the values of the map.
	values = new T[width * height];

	for (size_t i = 0; i < def.size(); i++)
	{
		*(values + i) = def[i];
	}

	/*auto first = def.begin();
	auto last = def.end();

	size_t i = 0;
	while (first != last) {
		*values = *first;
		++values; ++first; ++i;
	}

	for (i; i > 0; i--)
	{
		--values;
	}*/
}

template<typename T>
inline T& Map<T>::operator()(const uint x, const uint y) const
{
	return Get(x, y);
}

template<typename T>
inline T& Map<T>::Get(const uint x, const uint y) const
{
	return *(values + y * width + x);
}

template<typename T>
inline void Map<T>::Set(const uint x, const uint y, const T& val)
{
	*(values + y * width + x) = val;
}

template<typename T>
inline Map<T>::~Map()
{
	delete[] values;
}
