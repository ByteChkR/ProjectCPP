local scripts = {}
local meta = {["name"] = "2Bhouse2", ["objPath"] = "mge/models/CityBiome/3_CityB_HotelTall_v1.obj", ["specular"]  = "black.png", ["texture"] = "green.png", ["emissive"] = "black.png", ["posX"] = -2, ["posY"] = -0.8, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

