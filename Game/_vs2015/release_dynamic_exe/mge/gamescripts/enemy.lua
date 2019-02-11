local speed = 5
local minDistance = 1
local owningRef
local targetRef

function initialize(owningReference)
	owningRef = owningReference
	targetRef = Game.GetObject("player")
end

function update(pTime)
	if Game.GetDistance(owningRef, targetRef) < minDistance then
		Game.GameOver()
	end
	Game.AddPosition(owningRef, 0,0, pTime * speed)
end