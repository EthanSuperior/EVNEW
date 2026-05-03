// EVNEW - Escape Velocity: Nova Editor for Windows
// Image / PICT / RLE / PPAT helpers: `CImageFormatHelper::surface` is `shared_ptr<graphite::qd::surface>`; Graphite stays in this .cpp.

#ifndef CIMAGEFORMATHELPER_H_INCLUDED
#define CIMAGEFORMATHELPER_H_INCLUDED

#include <cstdint>
#include <memory>
#include <vector>

#include <windows.h>

namespace graphite::qd {
	class surface;
}

class CImageFormatHelper
{
public:
	using surface = std::shared_ptr<graphite::qd::surface>;

	enum EImageFormat
	{
		IMAGE_FORMAT_BMP  = 0,
		IMAGE_FORMAT_PNG  = 1,
		IMAGE_FORMAT_JPEG = 2,
		IMAGE_FORMAT_TIFF = 3
	};

	// --- Surface preview (PICT, RLE, PPAT, import pipeline) ---
	static int PreviewSurface(const surface &surf, HBITMAP *pOutBitmap, int *pWidth, int *pHeight, const char *szContext);

	// --- PICT <-> surface (`pictResourceId` / `pictResourceName` for Graphite ctor diagnostics) ---
	static int PictToSurface(const std::vector<UCHAR> &pictBytes, std::int64_t pictResourceId, const char *pictResourceName, surface &outSurface, const char *szContext);

	static int SurfaceToPict(const surface &surf, std::vector<UCHAR> &outPictBytes, const char *szContext, bool rgb555 = false);

	// --- RLE <-> surface (reserved for Graphite `qd::rle` / CRLEResource; not implemented yet) ---
	static int RLEToSurface(const std::vector<UCHAR> &rleBytes, std::int64_t rleResourceId, const char *rleResourceName, surface &outSurface, const char *szContext);

	static int SurfaceToRLE(const surface &surf, std::vector<UCHAR> &outRleBytes, const char *szContext);

	// --- PPAT <-> surface (reserved; not implemented yet) ---
	static int PpatToSurface(const std::vector<UCHAR> &ppatBytes, std::int64_t ppatResourceId, const char *ppatResourceName, surface &outSurface, const char *szContext);

	static int SurfaceToPpat(const surface &surf, std::vector<UCHAR> &outPpatBytes, const char *szContext);

	// --- Raster image file <-> surface (GDI+ decode / encode) ---
	static int ImportSurface(const char *szInputFilename, surface &outSurface, short *pWidth, short *pHeight, const char *szContext);

	static int ExportSurface(const surface &surf, const char *szOutputFilename, EImageFormat iFormat, const char *szContext);
};

#endif
