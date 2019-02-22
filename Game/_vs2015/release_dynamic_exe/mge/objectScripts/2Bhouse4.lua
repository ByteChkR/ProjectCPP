local scripts = {}
local meta = {["name"] = "2Bhouse4", ["objPath"] = "mge/models/CityBiome/City_house_1_1.obj", ["specular"]  = "black.png", ["texture"] = "green.png", ["emissive"] = "black.png", ["posX"] = -2, ["posY"] = -0.8, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

