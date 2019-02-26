local scripts = {}
local meta = {["name"] = "1BSideProp5", 
["objPath"] = "mge/models/VillageForestBiome/13_Village_B_Fance2_V1.obj", 
["specular"] = "Game/Maps/VillageForestBiome/fance2/10_Village_B_Fance2_V1_initialShadingGroup_MetallicSmoothness.png", 
["texture"] = "Game/Maps/VillageForestBiome/fance2/10_Village_B_Fance2_V1_initialShadingGroup_AlbedoTransparency.png", 
["normal"] = "Game/Maps/VillageForestBiome/fance2/10_Village_B_Fance2_V1_initialShadingGroup_Normal.png",
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

