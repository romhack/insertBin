insertBin
=========
Simple tool for inserting binary data in files.

Usage
-----------
```
insertBin patch.bin target.bin [-o offset][-s size] [-f fillValue]
```
**offset** - default 0
**size** - target size of patch, if patch.bin is greater, insertBin returns error, if greater allign to size with 0's or fillValue.
**fillValue** - if patch is greater, alligns patch.bin with given value.