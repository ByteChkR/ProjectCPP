local scripts = {}
local meta = {["name"] = "0Bhouse1", ["objPath"] = "mge/models/2_CityB_OldHouse_v1.obj", ["specular"]  = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0}
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

