#ifndef VIX_TMXMAP_H
#define VIX_TMXMAP_H

#include <vix_platform.h>
#include <vix_stringutil.h>

namespace Vixen {

	enum TMXOrientation
	{
		ORTHOGONAL,
		ISOMETRIC,
		STAGGERED
	};

	enum TMXRenderOrder
	{
		RIGHTDOWN,
		RIGHTUP,
		LEFTDOWN,
		LEFTUP
	};

	struct TMXMapInfo
	{
		double			version;	  //TMX format version (usually 1.0)
		TMXOrientation	orientation;  //Map orientation. Orthogonal, Isometric, Staggered
		TMXRenderOrder  renderOrder;
		size_t          width;		  //Width of map in TILES
		size_t          height;		  //Height of map in TILES
		size_t          tileWidth;    //Pixel width of tile
		size_t          tileHeight;   //Pixel height of tile
	};

	struct TMXTileImageInfo
	{

	};

	struct TMXTilesetInfo
	{
		int		globalID;
		UString name;
		size_t  width;   
		size_t  height;
		size_t  spacing;
		size_t  margin;
	};

	

	class VIX_API TMXMap
	{
	public:
		TMXMap(void);

	private:
		TMXMapInfo m_info;
		
	};

}

#endif