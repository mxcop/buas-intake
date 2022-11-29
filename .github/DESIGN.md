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
> <h4>{ name } <sup><code>{ turns }</code></sup></h4>
> { description }<br>
> <sup><code>Dynamic</code></sup> { description }

<br>

<h4>Turns</h4>
The game world uses turns, each turn ``ONE`` action can be performed.<br>
*(Turns are advanced by, walking, attacking, mining, or using an item)*<br>
<sup><code>Dynamic</code></sup> Adds a strategic element to the game.

<h4>Walking <sup><code>'1</code></sup></h4>
The player can walk in the four cardinal directions.
*(Using WASD)*<br>
<sup><code>Dynamic</code></sup> Simple movement options within a complex environment.

<h4>Walls</h4>
The player cannot move through walls.<br>
Attacking an enemy pushing them into a wall will deal extra damage.<br>
<sup><code>Dynamic</code></sup> Indicated by bumbing off the wall when attempting to walk into it.

<h4>Fog of War</h4>
The player at first cannot see the whole level, it becomes visible as they explore.<br>
<sup><code>Dynamic</code></sup> Adds more discovery and risk vs reward to the exploration.

<h4>Attacking <sup><code>'1</code></sup></h4>
The player can attack an enemy by walking into them. *(Using WASD)*<br>
Attacking an enemy will cause them to bounce away from you.<br>
<sup><code>Dynamic</code></sup> Using the same controls for attacking.

<h4>Mining <sup><code>'1</code></sup></h4>
The player can mine ores by walking into them.
*(Using WASD)*<br>
<sup><code>Dynamic</code></sup> Using the same controls for mining.

<h4>Enemies</h4>
Once enemies see the player they move towards them and try to attack them.<br>
*(Enemies attack after being attacked, e.g. killing an enemy in one hit means you don't take damage)*<br>
*(Enemies move after the player, so when moving into the same location the player moves)*<br>
<sup><code>Dynamic</code></sup> This attack delay means that timing is key when trying to avoid damage.

<h4>Pickups</h4>
After being mined ores can be picked up by walking on top of them.<br>
<sup><code>Dynamic</code></sup> Showing a clear indicator that the ore has been picked up.

<h4>Shops</h4>
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
