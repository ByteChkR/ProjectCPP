local scripts = {}
local meta = {["name"] = "1BHighObstacle2", ["objPath"] = "mge/models/placeholder.obj", ["texture"] = "red.png", ["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

