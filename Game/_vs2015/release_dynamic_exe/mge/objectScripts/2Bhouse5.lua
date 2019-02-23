local scripts = {}
local meta = {["name"] = "2Bhouse5", ["objPath"] = "mge/models/CityBiome/City_house_1.obj", ["specular"]  = "black.png", ["texture"] = "green.png", ["emissive"] = "black.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0  }
colliderMin = { ["width"] = -0.5, ["height"] = -0.5, ["depth"] = -0.5}
colliderMax = { ["width"] = 0.5, ["height"] = 0.5, ["depth"] = 0.5}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

