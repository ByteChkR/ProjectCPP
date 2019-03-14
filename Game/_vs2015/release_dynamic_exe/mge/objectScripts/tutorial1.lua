local scripts = {}
local meta = {["name"] = "tutorial1", ["texture"] = "red.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
colliderMin = { ["width"] = -0.5, ["height"] = -1, ["depth"] = -4}
colliderMax = { ["width"] = 0.5, ["height"] = 100, ["depth"] = -3}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

