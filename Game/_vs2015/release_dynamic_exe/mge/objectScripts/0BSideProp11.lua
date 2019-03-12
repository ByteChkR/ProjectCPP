local scripts = {}
--local scripts = {"mge/gamescripts/exampleScript.lua"}
local meta = {["name"] = "0BSideProp11", 
["objPath"] = "mge/models/FarmForestBiome/grass_right.obj", 
["texture"] = "Game/Maps/FarmForestBiome/grass.png", 
["ermissive"] = "Game/Maps/FarmForestBiome/grass.png", 
["posX"] = 0, 
["posY"] = -0.5, 
["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 10, ["height"] = 2, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

