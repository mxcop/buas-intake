#include "pool.h"
#include "../projectile.h"

template<class T>
Pool<T>::Pool(const u16 capacity)
{
	arena.reserve(capacity);
}

template<class T>
void Pool<T>::Tick(const u64 frame, const float deltatime)
{
	for (T& e : arena) {
		if (e.active) e.Tick(frame, deltatime);
	}
}

template<class T>
void Pool<T>::Draw(Tmpl8::Surface* screen)
{
	for (T& e : arena) {
		if (e.active) e.Draw(screen);
	}
}

template<class T>
u16 Pool<T>::Add(T arenable)
{
	auto itr = std::find_if(
		arena.begin(), arena.end(),
		[&](T& e) {
			return e.active == false;
		}
	);
	if (itr != arena.end()) {
		u16 id = itr->id;
		
		/* Might not be the most efficient to override the memory like this... */
		*itr = arenable;

		itr->id = id;
		return id;
	}
	arenable.id = uid;
	arena.push_back(arenable);
	uid++;
	return uid - 1;
}

template<class T>
void Pool<T>::Deactivate(const u16 id)
{
	auto itr = std::find_if(
		arena.begin(), arena.end(),
		[&](T& e) {
		    return e.id == id;
		}
	);
	if (itr != arena.end()) {
		itr->active = false;
	}
}

template<class T>
const T* Pool<T>::Get(const u16 id) const
{
	auto itr = std::find_if(
		arena.begin(), arena.end(),
		[&](const T& e) {
		    return e.id == id;
		}
	);
	if (itr != arena.end()) {
		return &*itr;
	}
	return nullptr;
}

template class Pool<Projectile>;