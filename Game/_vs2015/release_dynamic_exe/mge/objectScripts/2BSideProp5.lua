local scripts = {}
local meta = {["name"] = "2BSideProp5", ["objPath"] = "mge/models/CityBiome/13_CityB_FIre_Hydrant_v1.obj",
["texture"] = "Game/Maps/CityBiome/Fire_Hydrant/13_CityB_FIre_Hydrant_v1_Fire_Hydrant_BaseColor.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = -1, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

