local scripts = {}
local meta = {["name"] = "2BHighObstacle4", ["objPath"] = "mge/models/CityBiome/20_CityB_Barrier_v1.obj", 
["texture"] = "Game/Maps/CityBiome/Barrier/Barrier_Base_Color.png",["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

