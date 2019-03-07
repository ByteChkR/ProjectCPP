local owningRef
local speedScale = 1
local totalTime = 0
function initialize(owningReference)
	owningRef = owningReference
end

function update(pTime)
	totalTime = totalTime + pTime
	local x,y,z = Game.GetPosition(owningRef)
	Game.SetPosition(owningRef, x, math.sin(totalTime/10), y)
end