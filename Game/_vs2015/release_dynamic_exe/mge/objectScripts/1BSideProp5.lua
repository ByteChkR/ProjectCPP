local scripts = {}
local meta = {["name"] = "1BSideProp5", 
["objPath"] = "mge/models/VillageForestBiome/13_Village_B_Fance2_V1.obj", 
["texture"] = "Game/Maps/VillageForestBiome/fance2/10_Village_B_Fance2_V1_initialShadingGroup_AlbedoTransparency.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = -1, 
["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 2, ["depth"] = 1}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

