local scripts = {}
local meta = {["name"] = "Test", ["objPath"] = "mge/models/sphere_smooth.obj", ["texture"] = "runicfloor.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end
