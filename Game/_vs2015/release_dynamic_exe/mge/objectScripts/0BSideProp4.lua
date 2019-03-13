local scripts = {}
local meta = {["name"] = "0BSideProp4", 
["objPath"] = "mge/models/FarmForestBiome/wheatfield.obj", 
["texture"] = "Game/Maps/FarmForestBiome/wheatfield_diffuse.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = 0, 
["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

