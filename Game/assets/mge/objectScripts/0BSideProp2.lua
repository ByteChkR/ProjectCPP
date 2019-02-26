local scripts = {}
local meta = {["name"] = "0BSideProp2", 
["objPath"] = "mge/models/FarmForestBiome/balloon.obj", 
["specular"] = "Game/Maps/FarmForestBiome/balloon_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/balloon_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/balloon_initialShadingGroup_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/balloon_initialShadingGroup_Normal.png",
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

