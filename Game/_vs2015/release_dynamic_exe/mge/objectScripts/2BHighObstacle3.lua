local scripts = {}
local meta = {["name"] = "2BHighObstacle3", ["objPath"] = "mge/models/CityBiome/24_CityB_Fridge_v1.obj", ["texture"] = "Game/Maps/CityBiome/Fridge/Fridge_Base_Color.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
colliderMode = "auto"

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

