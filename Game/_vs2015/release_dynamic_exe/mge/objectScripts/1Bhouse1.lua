local scripts = {}
local meta = {["name"] = "1BHouse1", 
["objPath"] = "mge/models/VillageForestBiome/4_Village_B_HouseLong_Reversable_V1.obj", 
["specular"] = "Game/Maps/VillageForestBiome/LongHouse/1_Village_B_HouseLong_Reversable_V1_initialShadingGroup_MetallicSmoothness.png", 
["texture"] = "Game/Maps/VillageForestBiome/LongHouse/1_Village_B_HouseLong_Reversable_V1_initialShadingGroup_AlbedoTransparency.png", 
["posX"] = 0, 
["posY"] = -0.5, 
["posZ"] = 0 }
colliderMin = { ["width"] = -5, ["height"] = 0, ["depth"] = -5}
colliderMax = { ["width"] = 5, ["height"] = 7, ["depth"] = 5}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

