local scripts = {}
local meta = {["name"] = "1BSideProp1", 
["objPath"] = "mge/models/VillageForestBiome/9_Village_B_Fance1_V1.obj", 
["specular"] = "Game/Maps/VillageForestBiome/Fance1/9_Village_B_Fance1_V1_initialShadingGroup_MetallicSmoothness.png", 
["texture"] = "Game/Maps/VillageForestBiome/Fance1/9_Village_B_Fance1_V1_initialShadingGroup_AlbedoTransparency.png", 
["posX"] = 0, 
["posY"] = 0, 
["posZ"] = 0 }
colliderMin = { ["width"] = -0.1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 0.1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

