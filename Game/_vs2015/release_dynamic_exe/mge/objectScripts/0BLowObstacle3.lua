local scripts = {}
local meta = {["name"] = "0BLowObstacle3", 
["objPath"] = "mge/models/FarmForestBiome/trash.obj", 
["texture"] = "Game/Maps/FarmForestBiome/trash_initialShadingGroup_Diffuse.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = -0.5, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

