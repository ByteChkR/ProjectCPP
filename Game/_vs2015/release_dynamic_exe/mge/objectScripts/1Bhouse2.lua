local scripts = {}
local meta = {["name"] = "1Bhouse2", ["objPath"] = "mge/models/VillageForestBiome/sphere_smooth.obj", ["specular"]  = "black.png", ["texture"] = "blue.png", ["emissive"] = "black.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0  }
colliderMin = { ["width"] = -0.5, ["height"] = -0.5, ["depth"] = -0.5}
colliderMax = { ["width"] = 0.5, ["height"] = 0.5, ["depth"] = 0.5}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

