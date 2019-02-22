local scripts = {}
local meta = {["name"] = "1Bobstacle0", ["objPath"] = "mge/models/VillageForestBiome/sphere_smooth.obj" , ["specular"]  = "black.png", ["emissive"] = "black.png", ["texture"] = "blue.png", ["posX"] = 2, ["posY"] = -0.8, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

