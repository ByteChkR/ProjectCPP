local scripts = {}
local meta = {["name"] = "0BHouse4", 
["objPath"] = "mge/models/FarmForestBiome/Farm.obj", 
["specular"] = "Game/Maps/FarmForestBiome/Farm_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/Farm_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/Farm_initialShadingGroup_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/Farm_initialShadingGroup_Normal.png",
["posX"] = -25,
["posY"] = 0, 
["posZ"] = 0  }
colliderMin = { ["width"] = -4, ["height"] = 0, ["depth"] = -3}
colliderMax = { ["width"] = 6, ["height"] = 5, ["depth"] = 3}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

