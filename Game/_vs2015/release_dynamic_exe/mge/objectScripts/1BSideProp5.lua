local scripts = {}
local meta = {["name"] = "1BSideProp5", 
["objPath"] = "mge/models/VillageForestBiome/13_Village_B_Fance2_V1.obj", 
["specular"] = "Game/Maps/VillageForestBiome/Fence2_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/VillageForestBiome/Fence2_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/VillageForestBiome/Fence2_initialShadingGroup_Emissive.png",
["normal"] = "Game/Maps/VillageForestBiome/Fence2_initialShadingGroup_Normal.png",
["posX"] = 0, 
["posY"] = 0, 
["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 2, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

