local scripts = {}
local meta = {["name"] = "coin", ["objPath"] = "mge/models/CornPickup.obj", ["texture"] = "diffuse4.jpg", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
colliderMin = { ["width"] = -0.5, ["height"] = -0.5, ["depth"] = -0.5}
colliderMax = { ["width"] = 0.5, ["height"] = 0.5, ["depth"] = 0.5}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

