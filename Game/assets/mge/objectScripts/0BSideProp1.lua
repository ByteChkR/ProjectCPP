local scripts = {}
local meta = {["name"] = "0BSideProp1",
["objPath"] = "mge/models/FarmForestBiome/toilet.obj",
["specular"] = "Game/Maps/FarmForestBiome/toilet_initialShadingGroup_Specular.png",
["texture"] = "Game/Maps/FarmForestBiome/toilet_initialShadingGroup_Diffuse.png",
["emissive"] = "Game/Maps/FarmForestBiome/toilet_initialShadingGroup_Emissive.png",
["normal"] = "Game/Maps/FarmForestBiome/toilet_initialShadingGroup_Normal.png",
["posX"] = 0,
["posY"] = -1.5,
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -0.5}
colliderMax = { ["width"] = 1, ["height"] = 4, ["depth"] = 1.5}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

