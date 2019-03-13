local scripts = {}
local meta = {["name"] = "0BLowObstacle1", 
["objPath"] = "mge/models/FarmForestBiome/hay.obj", 
["texture"] = "Game/Maps/FarmForestBiome/hay_initialShadingGroup_Diffuse.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = -0.9, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -0.5, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 0.5, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

