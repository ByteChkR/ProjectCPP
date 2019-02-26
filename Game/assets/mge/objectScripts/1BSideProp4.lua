local scripts = {}
local meta = {["name"] = "1BSideProp4", 
["objPath"] = "mge/models/VillageForestBiome/12_Village_B_Tree1_V1.obj", 
["specular"] = "Game/Maps/VillageForestBiome/Tree1/Tree1_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/VillageForestBiome/Tree1/Tree1_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/VillageForestBiome/Tree1/Tree1_initialShadingGroup_Emissive.png",
["normal"] = "Game/Maps/VillageForestBiome/Tree1/Tree1_initialShadingGroup_Normal.png",
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

