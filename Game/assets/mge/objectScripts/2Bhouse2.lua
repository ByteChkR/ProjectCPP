local scripts = {}
local meta = {["name"] = "2BHouse2", ["objPath"] = "mge/models/CityBiome/2_CityB_OldHouse_v1.obj", ["specular"] = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = -1, ["posY"] = -0.5, ["posZ"] = 0 }
colliderMin = { ["width"] = -2, ["height"] = 0, ["depth"] = -2}
colliderMax = { ["width"] = 2, ["height"] = 7, ["depth"] = 2}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

