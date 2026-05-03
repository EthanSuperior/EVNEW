// EVNEW - Escape Velocity: Nova Editor for Windows
// Image / PICT I/O and conversion helpers (no libGraphite in consumers).

#ifndef CIMAGEFORMATHELPER_H_INCLUDED
#define CIMAGEFORMATHELPER_H_INCLUDED

#include <vector>

#include <windows.h>

class CImageFormatHelper
{
public:
	enum EImageFormat
	{
		IMAGE_FORMAT_BMP  = 0,
		IMAGE_FORMAT_PNG  = 1,
		IMAGE_FORMAT_JPEG = 2,
		IMAGE_FORMAT_TIFF = 3
	};

	/// General image file -> 24-bit BMP; used by RLE import and the Pict pipeline.
	static int ImportToBmp(const char *szInputFilename, const char *szOutputBmpFilename, int *pWidth, int *pHeight, const char *szContext);

	/// 24-bit BMP file -> user-selected image format; used by RLE export and Pict file export.
	static int ExportFromBmp(const char *szInputBmpFilename, const char *szOutputFilename, EImageFormat iFormat, const char *szContext);

	/// General image file -> in-memory PICT (via temp BMP and Graphite in the .cpp only).
	static int ImportToPict(const char *szInputFilename, std::vector<UCHAR> &outPictBytes, short *pWidth, short *pHeight, const char *szContext);

	/// PICT -> user-selected file format (via temp BMP and GDI+ in the .cpp only).
	static int ExportFromPict(const std::vector<UCHAR> &pictBytes, const char *szOutputFilename, EImageFormat iFormat, const char *szContext);

	/// 24-bit BMP on disk -> PICT bytes in memory.
	static int ConvertBmpToPict(const char *szInputBmpFilename, std::vector<UCHAR> &outPictBytes, short *pWidth, short *pHeight, const char *szContext);

	/// PICT bytes -> 24-bit BMP file.
	static int ConvertPictToBmp(const std::vector<UCHAR> &pictBytes, const char *szOutputBmpFilename, const char *szContext);

	/// PICT bytes -> 24bpp DIB for GDI preview.
	static int ConvertPictToDib(const std::vector<UCHAR> &pictBytes, HBITMAP *pOutBitmap, int *pWidth, int *pHeight, const char *szContext);
};

#endif
