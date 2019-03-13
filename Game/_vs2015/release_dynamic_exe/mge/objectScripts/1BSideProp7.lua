local scripts = {}
local meta = {["name"] = "1BSideProp7",
["objPath"] = "mge/models/VillageForestBiome/15_VillageB_PineTree_V1.obj", 
["texture"] = "Game/Maps/VillageForestBiome/randombonsai/tex.jpg",
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = -1, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

