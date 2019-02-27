local scripts = {}
local meta = {["name"] = "0BSideProp6", 
["objPath"] = "mge/models/FarmForestBiome/corn.obj", 
["texture"] = "Game/Maps/FarmForestBiome/corn_initialShadingGroup_Diffuse.png", 
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

