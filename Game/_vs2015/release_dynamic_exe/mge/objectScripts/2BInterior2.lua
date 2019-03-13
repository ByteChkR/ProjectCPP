local scripts = {}
local meta = {["name"] = "2BInterior2",
["objPath"] = "mge/models/CityBiome/park_left.obj",
["texture"] = "Game/Maps/CityBiome/park.png",
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0,
["posY"] = -0.8,
["posZ"] = 0 }
colliderMin = { ["width"] = 0, ["height"] = 0, ["depth"] = 0}
colliderMax = { ["width"] = 0, ["height"] = 0, ["depth"] = 0}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

