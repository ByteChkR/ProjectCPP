local scripts = {}
local meta = {["name"] = "1Bcoin", ["objPath"] = "mge/models/sphere_smooth.obj", ["texture"] = "diffuse4.jpg", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

