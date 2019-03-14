local scripts = {}
local meta = {["name"] = "2BHouse5",
 ["objPath"] = "mge/models/CityBiome/house4.obj",
 ["texture"] = "Game/Maps/CityBiome/house_paris2/house_paris2_diffuse.png",
 ["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = 0, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

