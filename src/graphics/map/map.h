#pragma once
#include <cstdio> // printf
#include <vector>
#include "types.h"

template <class T>
class Map {
public:
	// Using unsigned int for the size because I won't be using huge maps.
	Map(const u16 width, const u16 height);
	Map(const u16 width, const u16 height, const T def);
	Map(const u16 width, const u16 height, const std::initializer_list<T> def);
	Map(const u16 width, const u16 height, const std::vector<T> def);

	T& operator() (const u16 x, const u16 y) const;

	/// <summary>
	/// Get a value from a position within the map.
	/// </summary>
	T& Get(const u16 x, const u16 y) const;

	/// <summary>
	/// Set a value in a position within the map.
	/// </summary>
	void Set(const u16 x, const u16 y, const T& val);

	virtual ~Map();

protected:
	T* values = nullptr;
	u16 width = 0;
	u16 height = 0;
};