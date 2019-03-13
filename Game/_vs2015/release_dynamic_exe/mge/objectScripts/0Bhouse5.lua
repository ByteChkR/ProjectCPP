local scripts = {}
local meta = {["name"] = "0BHouse5", 
["objPath"] = "mge/models/FarmForestBiome/soil.obj", 
["texture"] = "Game/Maps/FarmForestBiome/soil_initialShadingGroup_Diffuse.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = -25, 
["posY"] = 0, 
["posZ"] = 0  }
colliderMin = { ["width"] = -3, ["height"] = 1, ["depth"] = -3}
colliderMax = { ["width"] = 3, ["height"] = 12, ["depth"] = 3}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

