local scripts = {}
local meta = {["name"] = "1Bhouse7", ["objPath"] = "mge/models/1_CityB_NewHouse_v1.obj", ["specular"]  = "black.png", ["texture"] = "blue.png", ["emissive"] = "black.png", ["posX"] = -2, ["posY"] = -0.8, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end
