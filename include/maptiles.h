/**
 * @file maptiles.h
 *
 * map_tiles() function
 *
 * @author Shahzad Bhatti
 * @date Summer 2015
 */

#ifndef MAPTILES_H_
#define MAPTILES_H_

#include <map>
#include <vector>

#include "epng.h"
#include "kdtree.h"
#include "mosaiccanvas.h"
#include "sourceimage.h"
#include "tileimage.h"

/**
 * Map the image tiles into a mosaic canvas which closely
 * matches the input image.
 *
 * @param source The input image to construct a photomosaic of
 * @param tiles The tiles image to use in the mosaic
 */
mosaic_canvas map_tiles(const source_image& source,
                        const std::vector<tile_image>& tiles);

/*
* converts a pixel to a point<3>
*/
auto pixel2point(const epng::rgba_pixel& pixel) -> point<3>;

#endif // MAPTILES_H_