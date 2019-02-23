local scripts = {}
local meta = {["name"] = "1Bobstacle4", ["objPath"] = "mge/models/VillageForestBiome/sphere_smooth.obj", ["texture"] = "blue.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
colliderMin = { ["width"] = -0.5, ["height"] = -0.5, ["depth"] = -0.5}
colliderMax = { ["width"] = 0.5, ["height"] = 0.5, ["depth"] = 0.5}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

