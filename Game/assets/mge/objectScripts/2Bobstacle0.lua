local scripts = {}
local meta = {["name"] = "2Bobstacle0", ["objPath"] = "mge/models/9_CityB_Umbrella_v1.obj" , ["specular"]  = "green.png", ["emissive"] = "black.png", ["texture"] = "red.png", ["posX"] = 2, ["posY"] = -0.8, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

