local scripts = {}
local meta = {["name"] = "traktor",
["objPath"] = "mge/models/CityBiome/Traktor.obj",
["texture"] = "Game/Shared/TraktorAO/Traktor_Traktor_initialShadingGroup_AlbedoTransparency.png",
["specular"] = "Game/Shared/TraktorAO/Traktor_Traktor_initialShadingGroup_MetallicSmoothness.png",
["posX"] = 1, ["posY"] = -0, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -2}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 2}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

