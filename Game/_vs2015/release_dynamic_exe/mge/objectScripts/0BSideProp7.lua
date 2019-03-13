local scripts = {}
local meta = {["name"] = "0BSideProp7", 
["objPath"] = "mge/models/FarmForestBiome/pole.obj", 
["texture"] = "Game/Maps/FarmForestBiome/pole_pole_initialShadingGroup_Diffuse.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = -1, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

