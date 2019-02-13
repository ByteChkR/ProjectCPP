local scripts = {}
local meta = {["name"] = "1Bhouse0", ["objPath"] = "mge/models/cube_smooth.obj", ["specular"]  = "sp_runicfloor.png", ["texture"] = "runicfloor.png", ["emissive"] = "em_runicfloor.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

