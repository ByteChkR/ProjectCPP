local scripts = {}
local meta = {["name"] = "1BSideProp6", 
["objPath"] = "mge/models/VillageForestBiome/14_VillageB_PineTree3_V1.obj", 
["specular"] = "black.png",
["texture"] = "Game/Maps/VillageForestBiome/pinetree/1/14_VillageB_PineTree3_V1_Geom_AlbedoTransparency.png",
--["emissive"] = "Game/Maps/VillageForestBiome/pinetree/1/14_VillageB_PineTree3_V1_Geom_AlbedoTransparency.png", 
["posX"] = 0, ["posY"] = 0, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

