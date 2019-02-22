# Object Folder Structure:

## Definitions:
```lua
["usage"] = sp(Specular)/ 
		em(Emissive)/ 
		tx(Texture or Albedo)/ 
		nm(Normal Map)

["objectKey"] = Key of object script(ex. "0Bhouse0")

["FolderNameIndicatingStoredObject"] = Either object key or something equally "unique"
```

## Models:
```lua
* OBJ(Expected Path): mge/models/CityBiome/["FolderNameIndicatingStoredObject"]/*
	+ Each Object is named {objectKey}.obj
```

## Textures:
```lua
* Textures(Expected Path): Game/Maps/CityBiome/["FolderNameIndicatingStoredObject"]/*
	+ Each texture is named ["usage"]_["objectKey"].png.
```