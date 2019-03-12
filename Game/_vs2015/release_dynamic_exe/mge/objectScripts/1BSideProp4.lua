local scripts = {}
local meta = {["name"] = "1BSideProp4",
["texture"] = "Game/Maps/VillageForestBiome/Tree1/12_Village_B_Tree1_V1_geometrized_AlbedoTransparency.png",
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

