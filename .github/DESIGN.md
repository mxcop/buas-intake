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

| Must              | Should       | Could       | Won't              |
| ----------------- | ------------ | ----------- | ------------------ |
| Player Controller | Shops        | Multiplayer | Online Multiplayer |
| Tilemap           | More Ores    | More Floors |                    |
| Collisions        |              |             |                    |
| Enemies           |              |             |                    |
| Inventory         |              |             |                    |
| Mining            |              |             |                    |
| Floor Generation  |              |             |                    |
| User Interface    |              |             |                    |

<br>

## Tasks

<sub><code>MUST</code> Player Controller</sub><br>
Create a player that can move in the four cardinal directions.<br>
The player can also interact by bumping into obstacles.

<sub><code>MUST</code> Tilemap</sub><br>
Create a tilemap class for rendering the environment.

<sub><code>MUST</code> Collisions</sub><br>
Create the collision framework for tilemaps and entities.

<sub><code>MUST</code> Enemies</sub><br>
Create a generic enemy class with health, damage, and a sprite.

<sub><code>MUST</code> Inventory</sub><br>
Create an inventory for the player controller along with a GUI.

<sub><code>MUST</code> Mining</sub><br>
Add ores which the player can mine by bumping into them.<br>
*(The ore will be added into their inventory)*

<sub><code>MUST</code> Floor Generation</sub><br>
Create a procedural floor generator that creates interesting caves & dungeons.

<sub><code>MUST</code> User Interface</sub><br>
Create a main menu & pause menu for the game.

<sub><code>SHOULD</code> Shops</sub><br>
Create random shops inbetween floors where you can sell your ores for items.

<sub><code>SHOULD</code> More Ores</sub><br>
Add more unique ores to the game, that can be used in the shops.

<br>

<sub><code>COULD</code> Multiplayer</sub><br>
Add the option to play together with friends over LAN.<br>
*(The way turns will work here is still vague)*

<sub><code>COULD</code> More Floors</sub><br>
Add more floors with different visuals, ores, and enemies.

<br>

## MDA

### Mechanics

...

### Dynamics

...

### Aesthetics

...

<br>

## Tools & Resources

- Visual Studio C++
- BUAS Template Engine
- Aseprite

<div class="page"/>