local scripts = {}
local meta = {["name"] = "2Bobstacle3", ["objPath"] = "mge/models/23_CityB_TrafficLight_v1.obj", ["texture"] = "green.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end
