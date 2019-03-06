local scripts = {}
local meta = {["name"] = "0BSideProp4", 
["objPath"] = "mge/models/FarmForestBiome/wheatfield.obj", 
["specular"] = "Game/Maps/FarmForestBiome/wheatfield_diffuse.png", 
["texture"] = "Game/Maps/FarmForestBiome/wheatfield_diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/wheatfield_diffuse.png", 
["posX"] = 0, 
["posY"] = 0, 
["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

