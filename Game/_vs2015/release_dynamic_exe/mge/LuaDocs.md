# MGE Engine Lua Implementation
## Contents
- [Game Scripts Explained](#game-scripts-explained)
	+ [What are Game Scripts](#what-are-game-scripts)
	+ [How do I create a Game Script](#how-do-i-create-a-game-script)
- [Documentation](#documentation)
	+ [Game.GetObject](#gamegetobjectobject-key)
	+ [Game.Print](#gameprintmessage)
	+ [Game.SetPosition](#gamesetpositiongameobject-x-y-z)
	+ [Game.AddPosition](#gameaddpositiongameobject-x-y-z)
	+ [Game.GetPosition](#gamegetpositiongameobject)
	+ [Game.GetDistance](#gamegetdistancegameobject1-gameobject2)
	+ [Game.CreateGameObject](#gamecreategameobjectobjectkey)
	+ [Game.GetParent](#gamegetparentgameobject)
	+ [Game.AddChild](#gameaddchildparent-child)
	+ [Game.CompareRef](#gamecomparerefgameobject1-gameobject2)
	+ [Game.PlaySound](#gameplaysoundnumberofsound)
	+ [Game.PlayMusic](#gameplaymusicnumberofmusic)
	+ [Game.GetLevelNum](#gamegetlevelnum)
	+ [Game.GetLevelProgress](#gamegetlevelprogress)
	+ [Game.ChangeAnimationFrame](#gamechangeanimationframegameobject-framenumber)
	+ [Game.NextAnimationFrame](#gamenextanimationframegameobject)
	+ [Game.GetAnimationFrame](#gamegetanimationframegameobject)
	+ [Game.PlayParticleEffect](#gameplayparticleeffectgameobject)
	+ [Game.StopParticleEffect](#gamestopparticleeffectgameobject)
	+ [Game.StopParticleEffectImmediate](#gamestopparticleeffectimmediategameobject)
## Game Scripts Explained
### What are Game Scripts
Gamescripts are like Behaviours in Unity. They are attached to a Gameobject and are able to update themselfes(and other scripts) every frame.
###How do I create a Game Script
1. Create a new file in your gameScripts folder(you will find it mge/gameScripts)
	+ Make sure that the file has the ".lua" extension.

2. Open the file with any text editor of your choice.

3. Create local variable and name it like so
```lua
local owningObj
```

4. Create the "activation function" for the game script
	+ This function gets called when the script gets attached to the game object.
	+ It passes the gameobject that this gameobject is attached to.
		- That means you should store it ;)
	+ The function looks like this:
	```
	function initialize(owningGameObject)
		owningObj = owningGameObject
	end
	```

5. Create the update function for the game script
	+ This function gets called once per frame
	+ It passes the time that has ellapsed since the last frame.
		- Its useful to incorporate the time ellapsed in your calculations when changing something over several frames. Specially when you move the game object
	+ The function looks like this
	```
	function update(timeEllapsed)
		Game.Print("Hello World") --Prints hello world in console.
	end
	```

6. Save the Document 

7. Attach it to one GameObject.
	+ Navigate to mge/objectScripts
	+ Open the gameobject you want to attach the script to.
	+ At line 1 there is something like this:
	```lua
	local scripts = {}
	```
	+ If its not there, you can simply copy the above code snippet and paste it in the file.
	+ To add a Game script you have to write the path to your created lua script into the curly brackets
	```lua
	local scripts = {"mge/gamescripts/exampleScript.lua", "mge/gamescripts/exampleScript1.lua"} -- Can have more than one lua game script
	```

8. Start the Game
	+ You are now set. You can start the game now and should see Hello World in your Console. Congratulations!


## Documentation
Now to the more technical part. I will list all the functions that I ADDED for Lua to use. I will not explain lua.
With that said, everything this API provides is located in Game(used Like Game.Print(""))

### Game.GetObject(object Key)
	Searches in the whole game for an object with a specified name and returns it
	usage: local objectReference = Game.GetObject("player")
### Game.Print(message)
	Writes a message to the console.
	usage: Game.Print("Hello World")
### Game.SetPosition(gameObject, x, y, z)
	Changes the Gameobjects position to the coordinate specified
	gameObject is an reference that you get over the initialize function OR get it via Game.GetObject("nameofobject")
	usage: Game.SetPosition(objectReference, 0, 1, 0)
### Game.AddPosition(gameObject, 0, 0, 1)
	Adds specified amount on the position of the Gameobject
	usage: see Game.SetPosition for details
### Game.GetPosition(gameObject)
	Returns the x, y and z position of the passed object
	usage: local x,y,z = Game.GetPosition(gameObject)
### Game.GetDistance(gameObject1, gameObject2)
	Returns the distance between gameobject1 and 2
	usage: local distance = Game.GetDistance(gameObject1, gameObject2)
### Game.CreateGameObject(objectKey)
	Returns the reference to the created gameobject. Untested and unused.
	usage: do not use.
### Game.GetParent(gameObject)
	Returns the parent of the passed gameobject. The parent can be nil. Its a good thing to check before using it.
	usage: local parentRef = Game.GetParent(gameObject)
### Game.AddChild(parent, child)
	Sets the child reference to the child of the passed parent.
	usage: Game.AddChild(owningReference, particleEffect)
### Game.CompareRef(gameObject1, gameObject2)
	Returns true if both gameObjects are the same.
	usage: 
	```
	if Game.CompareRef(owningRef, otherRef) then
		Game.Print("DO STUFF")
	end
	```
### Game.PlaySound(numberOfSound)
	Plays the specified sound
	usage: Game.PlaySound(0)
### Game.PlayMusic(numberOfMusic)
	Plays the specified music
	usage: Game.PlayMusic(0)
### Game.GetLevelNum()
	Returns the level number(first level = 0, second level = 1, ...)
	usage:
	```
	if Game.GetLevelNum() == 2 then
		Game.Print("Level3")
	end
	```
### Game.GetLevelProgress()
	Returns the current level progress in a range from 0(begin of the map) to 1(end of the map)
	usage: local levelPercentage = Game.GetLevelProgress() * 100
### Game.ChangeAnimationFrame(gameObject, frameNumber)
	Changes the displayed animation frame to frame number
	usage: Game.ChangeAnimationFrame(owningRef, 0) -- Restart animation(begin at 0)
### Game.NextAnimationFrame(gameObject)
	Changes the displayed animation frame to the next frame in the sprite
	usage: Game.NextAnimationFrame(owningReference) -- Next Sprite
### Game.GetAnimationFrame(gameObject)
	Returns the index of the current animation frame on this GameObject
	usage: local frameNum = Game.GetAnimationFrame(owningReference)
### Game.PlayParticleEffect(gameObject)
	Starts the particle effect attached to the passed gameObject.
	usage: Game.PlayParticleEffect(owningRef)
### Game.StopParticleEffect(gameObject)
	Stops the particle effect (while letting the alive particles active until they are unseen)
	usage: Game.StopParticleEffect(gameObject)
### Game.StopParticleEffectImmediate(gameObject)
	Stops the particle effect and removes all alive particles.


