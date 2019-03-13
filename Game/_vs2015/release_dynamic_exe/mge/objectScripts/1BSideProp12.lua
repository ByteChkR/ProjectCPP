local scripts = {}
local meta = {["name"] = "1BSideProp12",
["objPath"] = "mge/models/VillageForestBiome/ChoppedTreeTrunk.obj",
["texture"] = "Game/Maps/VillageForestBiome/treetrunkchopped/ChoppedTreeTrunk_geometrised_AlbedoTransparency.png",
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0,
["posY"] = -1,
["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

