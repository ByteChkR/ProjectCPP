local scripts = {}
local meta = {["name"] = "Test1", ["objPath"] = "mge/models/cylinder_smooth.obj" , ["specular"]  = "black.png", ["emissive"] = "black.png", ["texture"] = "runicfloor.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

