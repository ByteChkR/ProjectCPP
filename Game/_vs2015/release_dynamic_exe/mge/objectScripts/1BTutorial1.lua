local scripts = {}
local meta = {["name"] = "1BTutorial1",
 ["objPath"] = "mge/models/VillageForestBiome/well.obj",
 ["texture"] = "Game/Maps/VillageForestBiome/Well/37_VillageB_Well_V1_Geometrized_AlbedoTransparency.png",
 ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

