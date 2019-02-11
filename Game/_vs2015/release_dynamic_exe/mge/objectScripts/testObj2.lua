local scripts = {}
local meta = {["name"] = "Test2", ["objPath"] = "mge/models/suzanna_smooth.obj", ["texture"] = "land.jpg", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

