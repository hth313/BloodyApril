tiler --big-endian --tile-lut=1 --tile-set=0 --extract-palette --noise-on-color 0 --noise-color 22 --noise-color 26 --noise-level 6 trench1.bmp
mv trench1.index trench1-big-endian.index
# tiler --tile-lut=1 --tile-set=0 --extract-palette --noise-on-color 0 --noise-color 22 --noise-color 26 --noise-level 6 trench1.bmp
# mv trench1.index trench1-little-endian.index

tiler --big-endian --tile-lut=1 --tile-set=1 towns.bmp
mv towns.index towns-big-endian.index
# tiler --tile-lut=1 --tile-set=1 towns.bmp
# mv towns.index towns-little-endian.index

tiler --big-endian --width=32 --height=32 --sprites --sprite-count=32 sprites.bmp

# tiler --big-endian map-feb.bmp --bitplanes=3 --max-tiles=1024
# tiler --big-endian map-apr.bmp --bitplanes=3 --max-tiles=1024

# tiler --big-endian --width=32 --height=32 --sprites --sprite-count=32 sprites.bmp --bitplanes=5
