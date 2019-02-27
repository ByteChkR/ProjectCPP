local scripts = {}
local meta = {["name"] = "0BInterior2", 
["objPath"] = "mge/models/FarmForestBiome/chickenroom_left.obj", 
["texture"] = "Game/Maps/FarmForestBiome/chickenroom_lambert2SG_Diffuse2.png",
["ermissive"] = "Game/Maps/FarmForestBiome/chickenroom_lambert2SG_Diffuse2.png", 
["posX"] = 0, 
["posY"] = -1, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 0.5, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

