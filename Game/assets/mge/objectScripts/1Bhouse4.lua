local scripts = {}
local meta = {["name"] = "1BHouse4", 
["objPath"] = "mge/models/placeholder.obj", 
["specular"] = "black.png", 
["texture"] = "red.png", 
["emissive"] = "black.png", 
["posX"] = 0, 
["posY"] = -0.5, 
["posZ"] = 0 }
colliderMin = { ["width"] = -5, ["height"] = 0, ["depth"] = -5}
colliderMax = { ["width"] = 5, ["height"] = 7, ["depth"] = 5}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

