local scripts = {}
local meta = {["name"] = "1BSideProp11",
["objPath"] = "mge/models/VillageForestBiome/TreeNaked.obj",
["texture"] = "Game/Maps/VillageForestBiome/TreeNaked/VillageB_TreeNaked_V1_geometrized_AlbedoTransparency.png",
["posX"] = 0,
["posY"] = -0.5,
["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

