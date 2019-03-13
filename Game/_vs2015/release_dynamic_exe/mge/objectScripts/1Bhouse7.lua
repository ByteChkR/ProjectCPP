local scripts = {}
local meta = {["name"] = "1BHouse7",
 ["objPath"] = "mge/models/VillageForestBiome/Carrige.obj",
 ["specular"] = "black.png",
 ["texture"] = "Game/Maps/VillageForestBiome/carrige/Carrige_geometrised_AlbedoTransparency.png",
 ["posX"] = 0, ["posY"] = -1, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

