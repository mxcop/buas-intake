#include "pool.h"
#include "../projectile.h"
#include "../collider.h"

template<class T>
Pool<T>::Pool(const u16 capacity)
{
	pool.reserve(capacity);
}

template<class T>
u16 Pool<T>::Active() const
{
	u16 num = 0;
	for (const T& e : pool) {
		if (e.active) num++;
	}
	return num;
}

template<class T>
void Pool<T>::Tick(const u64 frame, const float deltatime)
{
	for (T& e : pool) {
		if (e.active) e.Tick(frame, deltatime);
	}
}

template<class T>
void Pool<T>::Draw(Tmpl8::Surface* screen)
{
	for (T& e : pool) {
		if (e.active) e.Draw(screen);
	}
}

template<class T>
u16 Pool<T>::Add(T poolable)
{
	auto itr = std::find_if(
		pool.begin(), pool.end(),
		[&](T& e) {
			return e.active == false;
		}
	);
	if (itr != pool.end()) {
		u16 id = itr->id;
		
		/* Might not be the most efficient to override the memory like this... */
		*itr = poolable;

		itr->id = id;
		return id;
	}
	poolable.id = uid;
	pool.push_back(poolable);
	uid++;
	return uid - 1;
}

template<class T>
void Pool<T>::Deactivate(const u16 id)
{
	auto itr = std::find_if(
		pool.begin(), pool.end(),
		[&](T& e) {
		    return e.id == id;
		}
	);
	if (itr != pool.end()) {
		itr->active = false;
	}
}

template<class T>
T* Pool<T>::Get(const u16 id)
{
	auto itr = std::find_if(
		pool.begin(), pool.end(),
		[&](T& e) {
		    return e.id == id;
		}
	);
	if (itr != pool.end()) {
		return &*itr;
	}
	return nullptr;
}

template<class T>
const std::vector<T>& Pool<T>::Vec() const
{
	return pool;
}

template class Pool<Projectile>;
template class Pool<Collider>;