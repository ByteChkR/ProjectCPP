local scripts = {}
local meta = {["name"] = "0Bobstacle0", ["objPath"] = "mge/models/FarmForestBiome/hay.obj" , ["specular"]  = "black.png", ["emissive"] = "black.png", ["texture"] = "red.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
colliderMin = { ["width"] = -0.5, ["height"] = -0.5, ["depth"] = -0.5}
colliderMax = { ["width"] = 0.5, ["height"] = 0.5, ["depth"] = 0.5}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

