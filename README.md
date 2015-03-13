# NeuralNetworkAttackOrFlee
Simple simulation based on neural network, which provides answer for the player, whether to attack a group of enemies 
or flee from battle.

### Details
There are 3 sections in the application: parameter scene, battle scene and neural network scene (not yet implemented).

On the battle scene, there is a player and a random number of enemies. Player is shooting at them (represented by a loading bar) 
and killing them instantly. Enemies are charging towards the player, inflict damage on contact and die. Player wins if all
enemies are dead and HP is greater than zero. Enemies win if they kill the player, regardless of remaining number of them.

You can perform single animated simulation of a battle and see the result, but You can also do fast multiple iterations with either
learning process or validation. Neural network is working based on 3 input parameters (specified in the parameter section):
* Initial HP of the player (chosen randomly between value specified and 100)
* Number of enemies
* Distance to the first enemy (maximum spawn distance can be specified)

and provides single output:
* 1 - Player should attack and survive the battle
* -1 - Player should flee, cause situation is unfavorable

### Controls
* Arrows - Change parameters (left part of the screen)
* S - Randomize battle parameters and spawn enemies (pressing again will generarate new set)
* Space - Perform single animated simulation and see the result.
* Enter - Perform N fast iterations of learning process (N specified in the top left corner. Win/Loss ration shown above)
* Q - Predict N battles and validate the results (correct/incorrect shown above)
* Backspace - Perform a single prediction based on currently shown scene.

### Requirements
Cocos2d-x v. 3.4
### Tested on
MS Visual Studio 2013/2015, Windows 7/8/10
