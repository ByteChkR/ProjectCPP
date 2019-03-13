local scripts = {}
local meta = {["name"] = "1BSideProp2", 
["objPath"] = "mge/models/VillageForestBiome/9_Village_B_Fance1_V1.obj",  
["texture"] = "Game/Maps/VillageForestBiome/Fance1Stackable/10_Village_B_Fance1Stackable_V1_initialShadingGroup_AlbedoTransparency.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = -1, 
["posZ"] = 0 }
colliderMin = { ["width"] = -0.1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 0.1, ["height"] = 1, ["depth"] = 1}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

