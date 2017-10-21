#ifndef __ROITEMPLATEGNERATOR_HPP__
#define __ROITEMPLATEGNERATOR_HPP__
/**************************************************************************************************\

    Author:     Henry
    Created:    22.08.2013

---------------------------------------------------------------------------------------------------

    Copyright (c) 2013 Smartsensors Ltd.

\**************************************************************************************************/
// Basic configuration for windows
#ifdef _WIN32
	#ifdef BUILD_SHARED
		#define MIRLIN_EXT_EXPORT __declspec(dllexport)
	#else
		#define MIRLIN_EXT_EXPORT __declspec(dllimport)
	#endif
#else
    #define MIRLIN_EXT_EXPORT
#endif // _WIN32
#include "Mirlin.h"

namespace MIR
{

/**
* Gets an enrol template from an input image and an ROI.
* \param [out] roTemplate The output template.
* \param [out] roSegResult Segmentation results.  NOTE: this is in the input
* image domain co-ords.
* \param [in] roImage The input image.  Must be <= 640x480
* \param [in] roi The input ROI.  Must be fully within the input image.
* \return true if segmentation succeded (pupil and iris were found), otherwise
* false.
* \throw CLicensingError if there is a problem with the license
* \throw std::invalid_argument if input image too large or ROI is not completely
* with the input image.
*/
bool MIRLIN_EXT_EXPORT GetTemplate( 
        CEnrolTemplate & roTemplate, 
        SSegmentationResult & roSegResult, 
        const CImage & roImage, 
        const SROI & roi );

/**
 * \copydoc GetTemplate(CEnrolTemplate&,SSegmentationResult&,const CImage&,const SROI&)
 */
bool MIRLIN_EXT_EXPORT GetTemplate( 
        CEnrolTemplate & roTemplate, 
        SSegmentationResult & roSegResult, 
        const CImageView & roImage, 
        const SROI & roi);

/**
* Gets a match template from an input image and an ROI.
* \param [out] roTemplate The output template.
* \param [out] roSegResult Segmentation results.  NOTE: this is in the input
* image domain co-ords.
* \param [in] roImage The input image.  Must be <= 640x480
* \param [in] roi The input ROI.  Must be fully within the input image.
* \return true if segmentation succeded (pupil and iris were found), otherwise
* false.
* \throw CLicensingError if there is a problem with the license
* \throw std::invalid_argument if input image too large or ROI is not completely
* with the input image.
*/
bool MIRLIN_EXT_EXPORT GetTemplate( 
        CMatchTemplate & roTemplate, 
        SSegmentationResult & roSegResult, 
        const CImage & roImage, 
        const SROI & roi );

/**
 * \copydoc GetTemplate(CMatchTemplate&,SSegmentationResult&,const CImage&,const SROI&)
 */
bool MIRLIN_EXT_EXPORT GetTemplate( 
        CMatchTemplate & roTemplate, 
        SSegmentationResult & roSegResult, 
        const CImageView & roImage, 
        const SROI & roi);

}  // namespace MIR


#endif  // __ROITEMPLATEGNERATOR_HPP__
