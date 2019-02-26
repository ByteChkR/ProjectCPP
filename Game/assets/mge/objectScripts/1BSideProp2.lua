local scripts = {}
local meta = {["name"] = "1BSideProp2", 
["objPath"] = "mge/models/VillageForestBiome/9_Village_B_Fance1_V1.obj", 
["specular"] = "Game/Maps/VillageForestBiome/Fence1Stackable_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/VillageForestBiome/Fence1Stackable_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/VillageForestBiome/Fence1Stackable_initialShadingGroup_Emissive.png",
["normal"] = "Game/Maps/VillageForestBiome/Fence1Stackable_initialShadingGroup_Normal.png",
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

