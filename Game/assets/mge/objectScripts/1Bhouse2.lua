local scripts = {}
local meta = {["name"] = "1BHouse2", 
["objPath"] = "mge/models/VillageForestBiome/5_Village_B_HouseSquare_V1.obj", 
["specular"] = "Game/Maps/VillageForestBiome/squareHouse/5_Village_B_HouseSquare_V1_initialShadingGroup_MetallicSmoothness.png", 
["texture"] = "Game/Maps/VillageForestBiome/squareHouse/5_Village_B_HouseSquare_V1_AlbedoTransparency_Geometrized.png", 
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

