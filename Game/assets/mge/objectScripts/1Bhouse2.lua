local scripts = {}
local meta = {["name"] = "1BHouse2", 
["objPath"] = "mge/models/VillageForestBiome/5_Village_B_HouseSquare_V1.obj", 
["specular"] = "Game/Maps/VillageForestBiome/squareHouse/5_Village_B_HouseSquare_V1_initialShadingGroup_MetallicSmoothness.png",
["texture"] = "Game/Maps/VillageForestBiome/squareHouse/5_Village_B_HouseSquare_V1_AlbedoTransparency_Geometrized.png", 
["normal"] = "Game/Maps/VillageForestBiome/squareHouse/5_Village_B_HouseSquare_V1_initialShadingGroup_Normal.png", 
["posX"] = 0, 
["posY"] = 0, 
["posZ"] = 0 }
colliderMin = { ["width"] = -3, ["height"] = 0, ["depth"] = -3}
colliderMax = { ["width"] = 1.5, ["height"] = 4, ["depth"] = 3}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

