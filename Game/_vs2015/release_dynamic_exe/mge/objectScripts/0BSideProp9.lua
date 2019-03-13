local scripts = {}
--local scripts = {"mge/gamescripts/exampleScript.lua"}
local meta = {["name"] = "0BSideProp9", 
["objPath"] = "mge/models/FarmForestBiome/wheatfield_right.obj", 
["texture"] = "Game/Maps/FarmForestBiome/wheatfield_diffuse.png",
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = -0.6, 
["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 2, ["depth"] = 1}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

