local scripts = {}
local meta = {["name"] = "2BLowObstacle2", 
["objPath"] = "mge/models/CityBiome/18_CityB_Trash_Can_v1.obj", 
["texture"] = "Game/Maps/CityBiome/Trash_Can/Trash_Can_Base_Color.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = -1, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

