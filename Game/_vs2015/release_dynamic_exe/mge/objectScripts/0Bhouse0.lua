local scripts = {"mge/gamescripts/exampleScript.lua"}
local meta = {["name"] = "0Bhouse0", ["objPath"] = "mge/models/FarmForestBiome/house.obj", ["specular"]  = "black.png", ["normal"] = "testNormal.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = -3, ["posY"] = 0, ["posZ"] = 0}
collider = { ["width"] = 8, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

