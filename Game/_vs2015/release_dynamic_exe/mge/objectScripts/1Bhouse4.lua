local scripts = {}
local meta = {["name"] = "1BHouse4",
["objPath"] = "mge/models/VillageForestBiome/housemaybe.obj",
["texture"] = "Game/Maps/VillageForestBiome/HouseMaybe/VillageB_HouseMaybe_v1_Geometrized_AlbedoTransparency.png",
["posX"] = 0,
["posY"] = 0,
["posZ"] = 0 }
colliderMin = { ["width"] = -5, ["height"] = 0, ["depth"] = -5}
colliderMax = { ["width"] = 5, ["height"] = 7, ["depth"] = 5}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

