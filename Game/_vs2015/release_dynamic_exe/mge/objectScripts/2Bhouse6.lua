local scripts = {}
local meta = {["name"] = "2BHouse6", 
["objPath"] = "mge/models/CityBiome/4_CityB_House_Paris3.obj",
 ["specular"] = "black.png",
 ["texture"] = "Game/Maps/CityBiome/house_paris3/house_paris3_diffuse.png",
 ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

