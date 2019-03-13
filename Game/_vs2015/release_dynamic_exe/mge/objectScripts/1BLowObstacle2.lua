local scripts = {}
local meta = {["name"] = "1BLowObstacle2", 
["objPath"] = "mge/models/FarmForestBiome/trashcan2.obj", 
["texture"] = "Game/Maps/FarmForestBiome/trashcan2_initialShadingGroup_Diffuse.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = 0, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

