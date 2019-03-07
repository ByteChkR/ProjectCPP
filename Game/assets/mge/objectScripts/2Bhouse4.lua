local scripts = {}
local meta = {["name"] = "2BHouse4",
 ["objPath"] = "mge/models/CityBiome/house3.obj",
 ["specular"] = "black.png",
 ["texture"] = "Game/Maps/CityBiome/house_paris1/House_Paris1_Diffuse.png" ,
 ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

