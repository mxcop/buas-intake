# Design Document

## Theme

``Bounce``

<br>

## Concept

You're a miner who goes down floors of a mine.<br>
As you make your way through these floors you try to collect as much ore as you can.<br>
However staying on one floor for too long can be dangerous due to the monsters that accumulate overtime.<br>
It's all about balancing risk vs reward to get the most out of your descent.

Each floor is randomly generated with an entrance, exit, ores, and monsters.<br>
The longer you stay in a floor the more monsters will spawn.<br>
Encouraging you to move quickly and choose your moves carefully.

The game is turn-based meaning that every entity moves or attacks at the same time.<br>
A turn only happens if the player moves, or performs an action. (like attacking)

Attacking an enemy causes them to bounce back, messing with the order which causes you to get hit if you move towards the enemy again.<br>
And you cannot just wait for the enemy to move towards you, so now you are motivated to perform an action to avoid being attacked.

<br>

## Style

Old school 8-bit rogue-like art style <sub>(Examples below)</sub>

<div>
  <img src="./assets/pork.png" width=240px>
  <img src="./assets/stray.png" width=240px>
</div>

<div class="page"/>

<br>

## MoSCoW

| Must              | Should           | Could       | Won't              |
| ----------------- | ---------------- | ----------- | ------------------ |
| Player Controller | Shops            | More Floors | Online Multiplayer |
| Tilemap           | More Ores        |             |                    |
| Collisions        | Floor Generation |             |                    |
| Enemies           |                  |             |                    |
| Inventory         |                  |             |                    |
| Mining            |                  |             |                    |
| User Interface    |                  |             |                    |

<br>

## MDA

### Mechanics & Dynamics

> **Note**:<br>
> <sub>\<name\> <code>\<turns\></code></sub><br>
> \<description\><br>
> <sup><code>Dynamic</code></sup> \<description\>

<sub>Turns</sub><br>
The game world uses turns, each turn ``ONE`` action can be performed.<br>
*(Turns are advanced by, walking, attacking, mining, or using an item)*<br>
<sup><code>Dynamic</code></sup> Adds a strategic element to the game.

<sub>Walking <code>'1</code></sub><br>
The player can walk in the four cardinal directions.
*(Using WASD)*<br>
<sup><code>Dynamic</code></sup> Simple movement options within a complex environment.

<sub>Walls</sub><br>
The player cannot move through walls.<br>
<sup><code>Dynamic</code></sup> Indicated by bumbing off the wall when attempting to walk into it.

<sub>Fog of War</sub><br>
The player at first cannot see the whole level, it becomes visible as they explore.<br>
<sup><code>Dynamic</code></sup> Adds more discovery and risk vs reward to the exploration.

<sub>Attacking <code>'1</code></sub><br>
The player can attack an enemy by walking into them. *(Using WASD)*<br>
Attacking an enemy will cause them to bounce away from you.<br>
<sup><code>Dynamic</code></sup> Using the same controls for attacking.

<sub>Mining <code>'1</code></sub><br>
The player can mine ores by walking into them.
*(Using WASD)*<br>
<sup><code>Dynamic</code></sup> Using the same controls for mining.

<sub>Enemies</sub><br>
Once enemies see the player they move towards them and try to attack them.<br>
*(Enemies attack after being attacked, e.g. killing an enemy in one hit means you don't take damage)*<br>
*(Enemies move after the player, so when moving into the same location the player moves)*<br>
<sup><code>Dynamic</code></sup> This attack delay means that timing is key when trying to avoid damage.

<sub>Pickups</sub><br>
After being mined ores can be picked up by walking on top of them.<br>
<sup><code>Dynamic</code></sup> Showing a clear indicator that the ore has been picked up.

<sub>Shops</sub><br>
The player can buys items from shops using the ores they've mined.<br>
*(Shops appear inbetween floors inside of a safe area)*<br>
<sup><code>Dynamic</code></sup> The player can decide how to spend their resources or save them.

### Aesthetics

``Challenge`` & ``Discovery``

<br>

## Tools & Resources

- Visual Studio C++
- BUAS Template Engine
- Aseprite

<div class="page"/>
