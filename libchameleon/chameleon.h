#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif
#define CHAMELEON_VERSION 0x01000000

	enum ChameleonColor
	{
		CHAMELEON_BACKGROUND1,
		CHAMELEON_FOREGROUND1,
		CHAMELEON_BACKGROUND2,
		CHAMELEON_FOREGROUND2,
		CHAMELEON_AVERAGE,
		CHAMELEON_LIGHT1,
		CHAMELEON_LIGHT2,
		CHAMELEON_LIGHT3,
		CHAMELEON_LIGHT4,
		CHAMELEON_DARK1,
		CHAMELEON_DARK2,
		CHAMELEON_DARK3,
		CHAMELEON_DARK4,
		CHAMELEON_COLORS
	};

	struct Chameleon;

	struct ChameleonParams
	{
		float countWeight;
		float edgeWeight;
		float bg1distanceWeight;
		float fg1distanceWeight;
		float saturationWeight;
		float contrastWeight;
	};

	uint32_t chameleonVersion();

	Chameleon* createChameleon(void);
	void destroyChameleon(Chameleon* chameleon);

	/*
		Processes a line of image data
		 chameleon: pointer to the Chameleon data structure
		 lineData: pointer to the X8R8G8B8 image data line
		 lineWidth: width of the data in pixels
		 edgeLine: true if first/last line of image, else false
	*/
	void chameleonProcessLine(Chameleon *chameleon, const uint32_t *lineData, size_t lineWidth, bool edgeLine, bool alpha = false);

	void chameleonProcessImage(Chameleon *chameleon, const uint32_t *imgData, size_t imgWidth, size_t imgHeight, bool alpha = false);

	/*
		Calculates the key FG/BG colors for the image
	*/
	void chameleonFindKeyColors(Chameleon *chameleon, const ChameleonParams *params, bool forceContrast = true);

	/*
		Get the specified color from the processed data
	*/
	uint32_t chameleonGetColor(Chameleon *chameleon, ChameleonColor color);

	float chameleonGetLuminance(Chameleon *chameleon, ChameleonColor color);

	/*
		Get the default parameters for processing a non-transparent image
	*/
	const ChameleonParams* chameleonDefaultImageParams();

	/*
		Get the default parameters for processing a semi-transparent image
	*/
	const ChameleonParams* chameleonDefaultIconParams();
#ifdef __cplusplus
}
#endif
