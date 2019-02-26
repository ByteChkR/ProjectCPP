local scripts = {}
local meta = {["name"] = "0BSideProp4", 
["objPath"] = "mge/models/FarmForestBiome/wheatfield.obj", 
["specular"] = "Game/Maps/FarmForestBiome/wheatfield_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/wheatfield_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/wheatfield_initialShadingGroup_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/wheatfield_initialShadingGroup_Normal.png",
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

