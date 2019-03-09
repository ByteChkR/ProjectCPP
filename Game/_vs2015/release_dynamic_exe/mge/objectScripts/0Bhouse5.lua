local scripts = {}
local meta = {["name"] = "0BHouse5", 
["objPath"] = "mge/models/FarmForestBiome/soil.obj", 
["specular"] = "Game/Maps/FarmForestBiome/soil_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/soil_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/soil_initialShadingGroup_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/soil_initialShadingGroup_Normal.png",
["posX"] = -25, 
["posY"] = 0, 
["posZ"] = 0  }
colliderMin = { ["width"] = -3, ["height"] = 1, ["depth"] = -3}
colliderMax = { ["width"] = 3, ["height"] = 12, ["depth"] = 3}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

