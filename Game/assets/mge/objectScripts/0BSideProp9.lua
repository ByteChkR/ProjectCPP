local scripts = {}
--local scripts = {"mge/gamescripts/exampleScript.lua"}
local meta = {["name"] = "0BSideProp9", 
["objPath"] = "mge/models/FarmForestBiome/wheatfield_right.obj", 
["specular"] = "Game/Maps/FarmForestBiome/wheatfield_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/wheatfield_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/wheatfield_initialShadingGroup_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/wheatfield_initialShadingGroup_Normal.png",
["posX"] = 0, 
["posY"] = -0.6, 
["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 2, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end

