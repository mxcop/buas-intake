#include "arena.h"
#include <tuple>

void EnemyArena::UpdateAll(u64 frame) {
    for (Enemy e : arena) {
        e.Update(frame);
    }
}

void EnemyArena::DrawAll(Tmpl8::Surface* screen) {
    for (Enemy e : arena) {
        e.Draw(screen);
    }
}

void EnemyArena::Add(Tmpl8::Sprite* sprite, u16 x, u16 y) {
    arena.push_back(Enemy(sprite, x, y, idn));
    idn++;
}

void EnemyArena::Delete(const u16 id) {
    //arena.erase(idx);
}

Enemy* EnemyArena::Get(const u16 id) {
    auto itr = std::find_if(
        arena.begin(), arena.end(),
        [&](const Enemy& e) {
            return e.id == id;
        }
    );
    if (itr != arena.end()) {
        return &(*itr);
    }
    return nullptr;
}

Enemy* EnemyArena::Get(const u8 x, const u8 y) {
    auto itr = std::find_if(
        arena.begin(), arena.end(),
        [&](const Enemy& e) {
            auto pos = e.GetPosition();
            return std::get<0>(pos) == x && std::get<1>(pos) == y;
        }
    );
    if (itr != arena.end()) {
        return &(*itr);
    }
    return nullptr;
}