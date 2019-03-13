local scripts = {}
local meta = {["name"] = "car",
["objPath"] = "mge/models/Car.obj",
["texture"] = "Game/Shared/Car/CarCentered_1001_AlbedoTransparency.png",
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = -0.5, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -2}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 2}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

