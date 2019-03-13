local scripts = {}
local meta = {["name"] = "1BLowObstacle1",
["objPath"] = "mge/models/VillageForestBiome/17_Village_B_Trunk_V1.obj",
["texture"] = "Game/Maps/VillageForestBiome/trunk/17_Village_B_Trunk_V1_Geom_AlbedoTransparency.png",
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0,
["posY"] = -1,
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -0.5, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = -0.5, ["depth"] = 1}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

