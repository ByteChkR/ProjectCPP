local scripts = {}
local meta = {["name"] = "0BHouse4", 
["objPath"] = "mge/models/FarmForestBiome/windmill.obj", 
["specular"] = "Game/Maps/FarmForestBiome/windmill_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/windmill_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/windmill_initialShadingGroup_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/windmill_initialShadingGroup_Normal.png",
["posX"] = -1,
["posY"] = 0, 
["posZ"] = 0  }
colliderMin = { ["width"] = -4, ["height"] = -1, ["depth"] = -4}
colliderMax = { ["width"] = 4, ["height"] = 11, ["depth"] = 4}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

