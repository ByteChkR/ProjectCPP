local scripts = {}
local meta = {["name"] = "0BLowObstacle2", 
["objPath"] = "mge/models/FarmForestBiome/trashcan2.obj", 
["specular"] = "Game/Maps/FarmForestBiome/trashcan2_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/trashcan2_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/trashcan2_initialShadingGroup_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/trashcan2_initialShadingGroup_Normal.png",
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

