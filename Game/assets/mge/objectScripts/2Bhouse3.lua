local scripts = {}
local meta = {["name"] = "2BHouse3", ["objPath"] = "mge/models/CityBiome/3_CityB_HotelTall_v1.obj", ["specular"] = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = -2, ["posY"] = -0.5, ["posZ"] = 0  }
colliderMin = { ["width"] = -4, ["height"] = 0, ["depth"] = -4}
colliderMax = { ["width"] = 3, ["height"] = 7, ["depth"] = 4}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

