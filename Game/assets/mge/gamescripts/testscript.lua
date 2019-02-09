

local totalTime = 0
local spawnTimeDelta = 0.5
local spawnDistance = 50
local intTime = 0
local owningRef
local minXDelta = 8;

function initialize(owningReference)
	owningRef = owningReference
end

function update(pTime)
	totalTime = totalTime + pTime;
	if intTime < totalTime then
		intTime = intTime + spawnTimeDelta
		spawnTimeDelta = spawnTimeDelta*0.99
		local enemy = Game.CreateGameObject("Enemy")
		Game.SetPosition(enemy, ((math.random()*2)-1)*minXDelta,0,-spawnDistance)
	end
end