local scripts = {}
local meta = {["name"] = "0BLowObstacle4", ["objPath"] = "mge/models/CityBiome/20_CityB_Barrier_v1.obj", ["specular"] = "black.png", ["texture"] = "Game/Maps/CityBiome/Barrier/Barrier_Base_Color.png",["posX"] = 0, ["posY"] = -1, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end
