local scripts = {}
local meta = {["name"] = "0Bobstacle0", ["objPath"] = "mge/models/2_CityB_OldHouse_v1.obj" , ["specular"]  = "black.png", ["emissive"] = "black.png", ["texture"] = "red.png", ["posX"] = 2, ["posY"] = -0.8, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

