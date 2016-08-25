# mosaic_creator
Creates a mosaic from small images

### Compile and Run
  
```
make photomosaic 
./photomosaic [input_image.png] [tile_directory/] [number of tiles] [pixels per tile] [output_image.png]
```
  Parameters in detail:

* tile_directory/: /mosaic_pngs
  
* number of tiles: 100

  The number of tiles to be placed along the shorter dimension of the source image

* pixels per tile: 50

  The width/height of a tile_image in the result mosaic. Don’t make this larger than 75 for the tile_images in /mosaic_pngs

* output_image: mosaic.png

