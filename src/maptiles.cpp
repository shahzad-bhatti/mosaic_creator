/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 *
 * @author Shahzad Bhatti
 * @date Summer 2015
 */

#include <map>
#include "maptiles.h"

mosaic_canvas map_tiles(const source_image& source, const std::vector<tile_image>& tiles)
{
	auto rows = source.rows();
	auto cols = source.columns();
	mosaic_canvas* canvas = new mosaic_canvas(rows, cols); 
	
	// creating a dictionay ADT with average color of a tile as KEY and the 
	// tile image as VALUE. This will be used to get the image given its average color
	std::map<point<3>, tile_image> tile_color;
	
	// constructing a vector of 3D points from average color of each tile. This vector is
	// passed to kd_tree tree constuctor.
	std::vector<point<3>> aveColorVec;

	for (size_t i = 0; i < tiles.size(); ++i)
	{
		auto color = tiles[i].average_color();
		auto pt = pixel2point(color);
		aveColorVec.push_back(pt);			
		tile_color[pt] = tiles[i];
	}
	
	
	// constructing kd_tree tree. This kd_tree tree will be used to get the closest tile image to
	//	the average color of a region in the source image.
	kd_tree<3> colorTree(aveColorVec);
	
	// setting tiles in the mosaic_cavas object
	for (int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
		{
			auto sourceColor = source.region_color(i, j);
			auto sourcePoint = pixel2point(sourceColor);
			auto closestPoint = colorTree.find_nearest_neighbor(sourcePoint);
			canvas->set_tile(i, j, tile_color[closestPoint]);
		}
	}
	return *canvas;
}

auto pixel2point(const epng::rgba_pixel& pixel) -> point<3>
{
	point<3> pt;
	pt[0] = pixel.red;
	pt[1] = pixel.green;
	pt[2] = pixel.blue;
	return pt;
}