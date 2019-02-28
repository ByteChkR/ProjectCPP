local scripts = {}
local meta = {["name"] = "0BInterior1",
["objPath"] = "mge/models/FarmForestBiome/chickenroom_right.obj",
["texture"] = "Game/Maps/FarmForestBiome/chickenroom_lambert2SG_Diffuse2.png",
["ermissive"] = "Game/Maps/FarmForestBiome/chickenroom_lambert2SG_Diffuse2.png",
["posX"] = 0.4,
["posY"] = -1.44,
["posZ"] = 2 }
colliderMin = { ["width"] = -4, ["height"] = -1, ["depth"] = -10}
colliderMax = { ["width"] = 10, ["height"] = 10, ["depth"] = 10}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

