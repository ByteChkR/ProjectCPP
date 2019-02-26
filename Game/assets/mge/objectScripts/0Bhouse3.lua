local scripts = {}
local meta = {["name"] = "0BHouse3", 
["objPath"] = "mge/models/FarmForestBiome/house1.obj", 
["specular"] = "Game/Maps/FarmForestBiome/house1_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/house1_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/house1_initialShadingGroup_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/house1_initialShadingGroup_Normal.png",
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

