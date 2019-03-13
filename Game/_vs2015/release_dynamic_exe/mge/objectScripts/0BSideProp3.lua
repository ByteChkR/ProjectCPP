local scripts = {}
local meta = {["name"] = "0BSideProp3", 
["objPath"] = "mge/models/FarmForestBiome/scarecrow.obj", 
["texture"] = "Game/Maps/FarmForestBiome/scarecrow_initialShadingGroup_Diffuse.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
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

