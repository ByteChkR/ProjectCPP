local scripts = {}
local meta = {["name"] = "staticvan",
["objPath"] = "mge/models/Van.obj",
["texture"] = "Game/Shared/Van/VanCentered_1001_AlbedoTransparency.png",
["specular"] = "Game/Shared/Van/VanCentered_1001_MetallicSmoothness.png",
["posX"] = 0, ["posY"] = -0.5, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -2}
colliderMax = { ["width"] = 1, ["height"] = 2, ["depth"] = 2}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

