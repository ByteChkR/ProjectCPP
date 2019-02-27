local scripts = {}
local meta = {["name"] = "1BHouse4", 
["objPath"] = "mge/models/VillageForestBiome/4_Village_B_HouseLong_Reversable_V1.obj", 
["specular"] = "Game/Maps/VillageForestBiome/HouseLong_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/VillageForestBiome/HouseLong_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/VillageForestBiome/HouseLong_initialShadingGroup_Emissive.png",
["normal"] = "Game/Maps/VillageForestBiome/HouseLong_initialShadingGroup_Normal.png",
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

