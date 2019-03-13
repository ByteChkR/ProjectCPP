local scripts = {}
local meta = {["name"] = "2BHouse6", 
["objPath"] = "mge/models/CityBiome/house5.obj",
 ["texture"] = "Game/Maps/CityBiome/house_paris3/house_paris3_diffuse.png",
 ["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = 0, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

