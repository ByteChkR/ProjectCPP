local scripts = {}
local meta = {["name"] = "2BLowObstacle3", ["objPath"] = "mge/models/CityBiome/19_CityB_Traffic_Cone_v1.obj", ["texture"] = "red.png", ["posX"] = 0, ["posY"] = -0.90, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

