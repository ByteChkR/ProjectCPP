local scripts = {}
local meta = {["name"] = "1BHighObstacle1", 
["objPath"] = "mge/models/VillageForestBiome/ChoppedTreeTrunk.obj",
["texture"] = "Game/Maps/VillageForestBiome/treetrunkchopped/ChoppedTreeTrunk_geometrised_AlbedoTransparency.png",
["posX"] = 0,
["posY"] = -0.5,
["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

