local scripts = {}
local meta = {["name"] = "0BHighObstacle1", 
["objPath"] = "mge/models/FarmForestBiome/scarecrow.obj", 
["texture"] = "Game/Maps/FarmForestBiome/scarecrow_initialShadingGroup_Diffuse.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = -1, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1., ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = -1, ["height"] = 6, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

