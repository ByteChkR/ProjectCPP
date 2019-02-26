local scripts = {}
local meta = {["name"] = "1BSideProp3", 
["objPath"] = "mge/models/VillageForestBiome/11_Village_B_Barrel_V1.obj", 
["specular"] = "Game/Maps/VillageForestBiome/Barrel/11_Village_B_Barrel_V1_initialShadingGroup_MetallicSmoothness.png", 
["texture"] = "Game/Maps/VillageForestBiome/Barrel/11_Village_B_Barrel_V1_Geom_AlbedoTransparency.png", 
["normal"] = "Game/Maps/VillageForestBiome/Barrel/11_Village_B_Barrel_V1_initialShadingGroup_Normal.png",
["posX"] = 0, 
["posY"] = -0.5, 
["posZ"] = 0  }
colliderMin = { ["width"] = -0.1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 0.1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

