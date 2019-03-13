local scripts = {}
local meta = {["name"] = "2BHighObstacle1", 
["objPath"] = "mge/models/CityBiome/22_CityB_Stop_Sign_v1.obj", 
["texture"] = "Game/Maps/CityBiome/Stop_Sign/22_CityB_StopSign_v1_Stop_Sign_BaseColor.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = 0,
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

