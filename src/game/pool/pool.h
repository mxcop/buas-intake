#pragma once

#include <vector>
#include "types.h"
#include "../../engine/surface.h"

/// <summary>
/// A class that can be placed within a pool.
/// </summary>
class Poolable {
public:
	virtual void Tick(const u64 frame, const float deltatime) = 0;
	virtual void Draw(Tmpl8::Surface* screen) = 0;
	u16 id = 0;
	bool active = true;
};

template<class T = Poolable>
/// <summary>
/// An efficient way of storing a large amount of Poolables.
/// </summary>
class Pool {
public:
	Pool(const u16 capacity = 32);

	/// <summary>
	/// (Debug Function) Get the number of active poolables.
	/// </summary>
	u16 Active() const;

	/// <summary> 
	/// Execute Tick() on all members of the arena. 
	/// </summary>
	void Tick(const u64 frame, const float deltatime);
	/// <summary> 
	/// Execute Draw() on all members of the arena. 
	/// </summary>
	void Draw(Tmpl8::Surface* screen);

	/// <summary> 
	/// Add a new member to the arena unless there's one already unactive. 
	/// </summary>
	u16 Add(T arenable);
	/// <summary> 
	/// Deactivate a member from the arena.
	/// </summary>
	void Deactivate(const u16 id);
	
	/// <summary> 
	/// Get a member from the arena by their id.
	/// </summary>
	T* Get(const u16 id);

	/// <returns>The pool contents as const vector.</returns>
	const std::vector<T>& Pool<T>::Vec() const;
private:
	/* Unique ID counter */
	u16 uid = 0;
	std::vector<T> pool;
};