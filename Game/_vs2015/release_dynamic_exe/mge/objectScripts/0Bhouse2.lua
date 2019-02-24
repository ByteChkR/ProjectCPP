local scripts = {}
local meta = {["name"] = "0BHouse2",
["objPath"] = "mge/models/FarmForestBiome/house1.obj", 
["specular"] = "Game/Maps/FarmForestBiome/house1_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/house1_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/house1_initialShadingGroup_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/house1_initialShadingGroup_Normal.png",
["posX"] = 0, 
["posY"] = 4, 
["posZ"] = 0 }
colliderMin = { ["width"] = -8, ["height"] = -4, ["depth"] = -2}
colliderMax = { ["width"] = 8, ["height"] = 1, ["depth"] = 2}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

