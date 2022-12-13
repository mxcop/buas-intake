#include "arena.h"
#include <tuple>

void EnemyArena::UpdateAll(u64 frame) {
    for (Enemy& e : arena) {
        e.Update(frame);
    }
}

void EnemyArena::DrawAll(Tmpl8::Surface* screen) {
    for (Enemy& e : arena) {
        e.Draw(screen);
    }
}

void EnemyArena::StepAll() {
    for (Enemy& e : arena) {
        e.Step();
    }
}

void EnemyArena::Add(Enemy enemy) {
    enemy.id = idn;
    arena.push_back(enemy);
    idn++;
}

void EnemyArena::Delete(const u16 id) {
    auto itr = std::find_if(
        arena.begin(), arena.end(),
        [&](const Enemy& e) {
            return e.id == id;
        }
    );
    if (itr != arena.end()) {
        int idx = itr - arena.begin();
        arena.erase(arena.begin() + idx);
    }
}

Enemy* EnemyArena::Get(const u16 id) {
    auto itr = std::find_if(
        arena.begin(), arena.end(),
        [&](const Enemy& e) {
            return e.id == id;
        }
    );
    if (itr != arena.end()) {
        return &*itr;
    }
    return nullptr;
}

Enemy* EnemyArena::Get(const u8 x, const u8 y) {
    for (Enemy& e : arena) {
        auto pos = e.GetPosition();
        if (std::get<0>(pos) == x && std::get<1>(pos) == y) {
            return &e;
        }
    }
    return nullptr;
}