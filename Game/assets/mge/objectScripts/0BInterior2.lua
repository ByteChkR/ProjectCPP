local scripts = {}
local meta = {["name"] = "0BInterior2",
["objPath"] = "mge/models/FarmForestBiome/chickenroom_left.obj",
["texture"] = "Game/Maps/FarmForestBiome/chickenroom_lambert2SG_Diffuse2.png",
["ermissive"] = "Game/Maps/FarmForestBiome/chickenroom_lambert2SG_Diffuse2.png",
["posX"] =  0.5,
["posY"] = -1.44,
["posZ"] = 2 }
colliderMin = { ["width"] = -10, ["height"] = -1, ["depth"] = -10}
colliderMax = { ["width"] = -4, ["height"] = 10, ["depth"] = 10}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

