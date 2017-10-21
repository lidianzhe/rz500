#ifndef _MIRLIN_H
#define _MIRLIN_H
/*************************************************************************************************\

 MIRLIN - Monro Iris Recognition LIbrary

 Creation date: 15/06/2007

 -------------------------------------------------------------------------------------------------

 Copyright (c) 2007 - 2012 Smart Sensors Ltd

\*************************************************************************************************/


// Basic configuration for windows
#ifdef _WIN32
	#ifdef MIRLIN_DLL
		#define MIRLIN_EXPORT __declspec(dllexport)
	#elif defined(MIRLIN_STATIC_LIB)
		#define MIRLIN_EXPORT
	#else
		#define MIRLIN_EXPORT __declspec(dllimport)
	#endif
#else
	/**
     * Defines symbol export policy for windows
     */
    #define MIRLIN_EXPORT
#endif // _WIN32


#ifdef _WIN32
    // Unfortunately there are some stupid Windows #define
	#define NOMINMAX
	#ifdef LoadImage
		#undef LoadImage
	#endif
#endif


#include <stdexcept>

/**
 * \mainpage
 *
 * # <CENTER> Reference Manual </CENTER> #
 *
 * This manual documents both the C and C++ APIs for Smart Sensors Ltd MIRLIN
 * SDK.  The C++ interface is the preferred interface, as it is typically simpler
 * to use.
 *
 * For more information on the API, the best place to start is probably the <a
 * href="modules.html">modules</a> page.
 *
 * Further information about Smart Sensors Ltd may be obtained from our <a
 * href="http://www.smartsensors.co.uk">website</a>.
 */

/**
 *@defgroup MIR C++ style interface for MIRLIN
 * This object oriented interface provides an easy and convenient way access to MIRLIN.
 * Other benefits of this interface are memory management and exceptions to get helpful messages.
 */

/// New and easy C++ interface for MIRLIN
namespace MIR
{
	// Defines an image with memory management of the image data
	class CImage;
	// Defines the input image as a view, i.e. no responsibility for the data is taken, nothing copied, nothing deleted
	class CImageView;

	// Defines an enrol template with full memory management
	class CEnrolTemplate;
	// Defines a match (or probe) template with full memory management
	class CMatchTemplate;

	// Holds information about segmented iris and pupil
	struct SSegmentationResult;
	// Holds the results of comparing two templates
	struct SComparisonResult;

    // Container holding a number of enrol templates
    class CEnrolTemplateContainer;
    // Container holding comparison results from comparing a number of enrol templates with a match template
    class CComparisonResultContainer;

	/**@brief Basic structs like exceptions and region of interest
	 *
	 *@defgroup MIR_Utilities Basic structs
	 *@ingroup MIR
	 */
	///@{
    /**@brief Exception thrown when a valid license is unavailable
     *
     * This exception is thrown when no valid license was found or
     * all licenses are in use. See the description of the error message
     * for more details.
     *@see MIR_Config_License for more information about the license in use.
     */
    class MIRLIN_EXPORT CInvalidLicenseError
    {
    public:
        /// Constructs an exception with the given error message
        CInvalidLicenseError( const char * rcErrorMsg, int nSize );
        /// Copy construction
        CInvalidLicenseError( const CInvalidLicenseError & roThat );
        /// Destructor
        ~CInvalidLicenseError();

        /// Returns the error message of the exception
        const char * what() const throw();

    private:
        /// Holds the size of the string
        int m_nSize;
        /// Holds the error message of the exception
        char * m_cErrorMsg;
    };

	/// Region of interest
	struct MIRLIN_EXPORT SROI
	{
		/// Holds the x coordinate of the start point of the region of interest
		int nStartX;
		/// Holds the y coordinate of the start point
		int nStartY;
		/// Defines the width of the rectangular region of interest
		int nWidth;
		/// Defines the height of the rectangular region of interest
		int nHeight;

		/// Default construction which sets all the values to zero
		SROI();
	};
	///@}


	/// %ISO namespace for ISO/IEC 19794-6:2011
	namespace ISO
	{
		/**@brief Everything related to %ISO iris image standard
		 *
		 *@addtogroup MIR_IS0 %ISO iris image types and quality metrics calculation
		 *@ingroup MIR
		 *
		 * Functions and structs for calculating %ISO iris image quality metrics and
		 * %ISO type images.
		 */
		///@{

		// Quality metric calculated on an input image
		struct SImageQualityMetric;

       	/**@brief Specifies an ISO/IEC 19794-6:2011 image type.
         *
	     */
	    enum EIrisImageType
	    {
		    eISOType3 = 3,  ///< Specifies a cropped iris image
	        eISOType7 = 7   ///< Specifies a cropped and masked iris image
	    };

        /**@brief Creates an ISO/IEC 19794-6:2011 image to disk.
	     *
	     *@param [out] roIrisImage Resulting %ISO iris image
	     *@param [out] roSegResult Segmentation result of the given input image
	     *@param [in] eImageType Specifies the desired %ISO iris image type
	     *@param [in] roImage Input image which gets segmented.
	     *@returns true if creating the image was successful, otherwise false
	     *@throw std::invalid_argument if input image is not valid or it is not possible to create an %ISO image
	     */
        bool MIRLIN_EXPORT CreateIrisImage( CImage & roIrisImage, SSegmentationResult & roSegResult, EIrisImageType eImageType, const CImage & roImage );
	    /**
	     *@copydoc CreateIrisImage( CImage &, SSegmentationResult &, EIrisImageType, const CImage & )
	     */
        bool MIRLIN_EXPORT CreateIrisImage( CImage & roIrisImage, SSegmentationResult & roSegResult, EIrisImageType eImageType, const CImageView & roImage );

		/**@brief Calculates %ISO iris image quality metric of the given input image.
		 *
		 *@param [out] roMetricResult Calculated %ISO iris image quality metric
		 *@param [in] roImage Input image used to calculate the quality metric
		 *@param [in] oROI Optional region of interest where the quality metrics shoud be calculated. By default the whole image is taken.
		 *@returns true if the calculation of the quality metric was successfull, otherwise false
		 *@throw std::invalid_argument if an image without valid data was passed in
		 */
		bool MIRLIN_EXPORT GetQualityMetric( SImageQualityMetric & roMetricResult, const CImage & roImage, SROI oROI = SROI() );
		/**
		 *@copydoc GetQualityMetric( SImageQualityMetric &, const CImage &, SROI )
		 */
		bool MIRLIN_EXPORT GetQualityMetric( SImageQualityMetric & roMetricResult, const CImageView & roImage, SROI oROI = SROI() );

		/// %ISO iris image quality metrics calculated on an image only
		struct MIRLIN_EXPORT SImageQualityMetric
		{
			/// Focus of the image. Value range: 0 - 100 (Higher = Better)
			double dFocus;
			/// Contrast of the image. Value range: 0 - 100 (Higher = Better)
			double dContrast;
			/// Entropy or histogram utilisation of the histogram. Values are negative (Smaller = Better)
			double dEntropy;

			/// Default construction, sets all the values to -1 to indicate invalid values.
			SImageQualityMetric();
		};

		///@}
	} // namespace ISO


	/**@brief Everything related to images, i.e. segmentation, import and export, ...
	 *
	 *@defgroup MIR_Image Images
	 *@ingroup MIR
	 */
	/**@brief Visualisation of segmentation
	 *
	 *@addtogroup MIR_ImageFunctions Visualisation of segmentation
	 *@ingroup MIR_Image
	 */
	///@{
	/**@brief Performs visualisation of the segmentation result overlaid on the image.
	 *
	 * Draws the segmentation result, i.e. pupil and iris, on the given input image.
	 *@param [out] roImage Image, on which the segmentation result is drawn
	 *@param [in] roSegResult Segmentation result obtained by GetTemplate()
	 *@returns true if drawing was successful
	 *@throws std::invalid_argument if an image without valid data was passed in
	 */
	bool MIRLIN_EXPORT VisualiseSegmentation( CImageView & roImage, const SSegmentationResult & roSegResult );
	/**
	 *@copydoc VisualiseSegmentation( CImageView &, const SSegmentationResult & )
	 */
	bool MIRLIN_EXPORT VisualiseSegmentation( CImage & roImage, const SSegmentationResult & roSegResult );
	///@}

	/**@brief All necessary functions to load and save images
	 *@addtogroup MIR_ImageIO Image import and export
	 *@ingroup MIR_Image
	 */
	///@{
	/**
	 *@name Save Images
	 */
	///@{
	/**@brief Saves the given image to disk (in BMP format).
	 *
	 *@param [in] roImage Image to save
	 *@param [in] pFilename Output filename
	 *@returns true if saving the image was successful, otherwise false
	 *@throws std::invalid_argument if an invalid image was passed in
	 */
	bool MIRLIN_EXPORT SaveImage( const CImage & roImage, const char * pFilename );
	/**
	 *@copydoc SaveImage( const CImage &, const char * )
	 */
	bool MIRLIN_EXPORT SaveImage( const CImageView & roImage, const char * pFilename );
	///@}

	/**
	 *@name Load Image
	 */
	///@{
	/**@brief Loads an image from file.
	 *
	 *@param [out] roImage Loaded image
	 *@param [in] pFilename Input filename
	 *@returns true if loading the image was successful, otherwise false
	 */
	bool MIRLIN_EXPORT LoadImage( CImage & roImage, const char * pFilename );
	///@}
	///@}


	/**@brief Template types, template generation and comparison
	 *@addtogroup MIR_Template Templates
	 *@ingroup MIR
	 */
	/**@brief Generate and compare templates
	 *@addtogroup MIR_TemplateFunctions Template generation and comparison
	 *@ingroup MIR_Template
	 */
	///@{
	/**
	 *@name Enrol template generation
	 */
	///@{
	/**@brief Calculates an enrol template from the given image.
	 *
	 *@param [out] roTemplate Template for the given image
	 *@param [in] roImage The input image
	 *@throws std::invalid_argument if an invalid image was passed in
	 *@returns true if the template creation was successful, otherwise false
	 */
	bool MIRLIN_EXPORT GetTemplate( CEnrolTemplate & roTemplate, const CImage & roImage );
	/**
	 *@copydoc GetTemplate( CEnrolTemplate &, const CImage & )
	 */
	bool MIRLIN_EXPORT GetTemplate( CEnrolTemplate & roTemplate, const CImageView & roImage );
	/**@brief Calculates an enrol template from the given image.
	 *
	 *@param [out] roTemplate Template for the given image
	 *@param [out] roSegResult Segmentation result of the image
	 *@param [in] roImage The input image
	 *@throws std::invalid_argument if an invalid image was passed in
	 *@returns true if the template creation was successful, otherwise false
	 */
	bool MIRLIN_EXPORT GetTemplate( CEnrolTemplate & roTemplate, SSegmentationResult & roSegResult, const CImage & roImage );
	/**
	 *@copydoc GetTemplate( CEnrolTemplate &, SSegmentationResult &, const CImage & )
	 */
	bool MIRLIN_EXPORT GetTemplate( CEnrolTemplate & roTemplate, SSegmentationResult & roSegResult, const CImageView & roImage );
	///@}

	/**
	 *@name Match template generation
	 */
	///@{
	/**@brief Calculates a match template from the given image.
	 *
	 *@param [out] roTemplate Template for the given image
	 *@param [in] roImage The input image
	 *@throws std::invalid_argument if an invalid image was passed in
	 *@returns true if the template creation was successful, otherwise false
	 */
	bool MIRLIN_EXPORT GetTemplate( CMatchTemplate & roTemplate, const CImage & roImage );
	/**
	 *@copydoc GetTemplate( CMatchTemplate &, const CImage & )
	 */
	bool MIRLIN_EXPORT GetTemplate( CMatchTemplate & roTemplate, const CImageView & roImage );
	/**@brief Calculates a match template from the given image.
	 *
	 *@param [out] roTemplate Template for the given image
	 *@param [out] roSegResult Segmentation result of the image
	 *@param [in] roImage The input image
	 *@throws std::invalid_argument if an invalid image was passed in
	 *@returns true if the template creation was successful, otherwise false
	 */
	bool MIRLIN_EXPORT GetTemplate( CMatchTemplate & roTemplate, SSegmentationResult & roSegResult, const CImage & roImage );
	/**
	 *@copydoc GetTemplate( CMatchTemplate &, SSegmentationResult &, const CImage & )
	 */
	bool MIRLIN_EXPORT GetTemplate( CMatchTemplate & roTemplate, SSegmentationResult & roSegResult, const CImageView & roImage );
	///@}

	/**
	 *@name Template Comparison
	 */
	///@{
	/**@brief Compares a match template and an enrol template.
	 *
	 *@param [out] roResult Comparison result containing the Hamming Distance and Co-occlusion between both templates
	 *@param [in] roEnrolTemplate Enrol template
	 *@param [in] roMatchTemplate Match template
	 *@returns true if comparison was successful (i.e. both templates are valid), otherwise false
	 */
	bool MIRLIN_EXPORT CompareTemplates( SComparisonResult & roResult,
										 const CEnrolTemplate & roEnrolTemplate,
										 const CMatchTemplate & roMatchTemplate );

	/**@brief Compares a match template and against several enrol templates.
	 *
	 * The container holding comparsion results will be filled with the comparison results and will hold as many comparison results as enrol templates.
	 *@param [out] roResults Container of comparison result holding the Hamming Distance and Co-occlusion
	 *@param [in] roEnrolTemplates Container holding the enrol templates to be compared with the match template
	 *@param [in] roMatchTemplate Match template
	 *@returns true if comparison was successful (i.e. templates are valid), otherwise false
	 */
	bool MIRLIN_EXPORT CompareTemplates( CComparisonResultContainer & roResults,
									     const CEnrolTemplateContainer & roEnrolTemplates,
										 const CMatchTemplate & roMatchTemplate );
	///@}

	/**
	 *@name Template Import and Export
	 */
	///@{
	/**@brief Saves the given template to disk.
	 *
	 *@param [in] roTemplate Template to save
	 *@param [in] pFilename Output filename
	 *@returns true if saving was successful, otherwise false
	 *@throw std::invalid_argument if an empty or invalid template was passed in
	 */
	bool MIRLIN_EXPORT SaveTemplate( const CEnrolTemplate & roTemplate, const char * pFilename );
	/**
	 *@copydoc SaveTemplate( const CEnrolTemplate &, const char * )
	 */
	bool MIRLIN_EXPORT SaveTemplate( const CMatchTemplate & roTemplate, const char * pFilename );

	/**@brief Loads a stored template from file.
	 *
	 *@param [out] roTemplate Loaded template
	 *@param [in] pFilename Input filename
	 *@returns true if loading was successful, otherwise false
	 *@throw std::invalid_argument if the data of the template is not valid, e.g. if the template on disk is of a type other than that of roTemplate
	 */
    bool MIRLIN_EXPORT LoadTemplate( CEnrolTemplate & roTemplate, const char * pFilename );
	/**
	 *@copydoc LoadTemplate( CEnrolTemplate & , const char * )
	 */
	bool MIRLIN_EXPORT LoadTemplate( CMatchTemplate & roTemplate, const char * pFilename );
	///@}
	///@}


	/**@brief Definition of images, segmentation result, and enumeration types
	 *
	 *@defgroup MIR_ImageStructs Image classes and result structs
	 *@ingroup MIR_Image
	 */
	///@{
	/**@brief Holds the segmentation result
     * \par
     * The segmentation result consists of pupil and iris,
     * assuming the individual structures have been found.
     */
	struct MIRLIN_EXPORT SSegmentationResult
	{
		/// True if a pupil was found, otherwise false
		bool bFoundPupil;
		/// True if a Iris was found, otherwise false
		bool bFoundIris;

		/// Holds centre and radius for pupil or iris
		struct SEyeComponent
		{
			/// X-coordinate of the centre
			int nCentreX;
			/// Y-coordinate of the centre
			int nCentreY;
			/// Radius of pupil or iris
			int nRadius;
		};
		/// Holds the pupil information
		SEyeComponent oPupil;
		/// Holds the iris information
		SEyeComponent oIris;

	    /**@brief Percentage of usable iris area.
         *@par 
         * This metric details the amount of usable iris area of the segmented
         * image.  The Segmented pupil and iris, eyelids and specular
         * reflections are considered when calculating the percentage of the
         * visible iris area.  Value range: 0 - 100 (Higher = Better)
		 */
        double dUsableIrisArea;

		/// Default construction
		SSegmentationResult();
	};


	/// Specially supported capture devices
	enum ECaptureDevice
    {
        eUnspecified = 0,	///< Indicates an arbitrary capture device
        eEY2H			    ///< Image was captured by an EY2H
    };

	/// Possible image types
	enum EImageType
    {
        eDefault = 0,	///< Indicates a default image type
        eISOType2,      ///< Image is an %ISO type 2 iris image
        eISOType3,      ///< Image is an %ISO type 3 iris image
        eISOType7       ///< Image is an %ISO type 7 iris image
    };

	/**@brief Implementation of an arbitray-sized image with memory management.
	 *
	 * This class takes care of the image data and is usually used to load an image from
	 * disk. If a CImage is created using given image data as a block of memory, the image
	 * data gets copied internally.
	 *
	 *@see CImageView for user-managed image data
	 */
	class MIRLIN_EXPORT CImage
	{
	public:
		/// Default construction
		CImage();
		/**@brief Constructs with the given image data and size.
         *@note The data is copied internally
		 *@param [in] pImageData Pointer to the block of memory holding the image data
		 *@param [in] nImageWidth Width of the image
		 *@param [in] nImageHeight Height of the image
		 */
		explicit CImage( const unsigned char * pImageData, int nImageWidth, int nImageHeight );
		/// Copy construction
		CImage( const CImage & roThat );
		/// Destructor
		~CImage();
		/// Assignment operator
		CImage & operator=( const CImage & roThat );

		/// Returns whether the image is valid, e.g. has valid data
		bool IsValid() const;

        /// Returns the width of the image
        int GetWidth() const;
        /// Returns the height of the image
        int GetHeight() const;

		/// Returns the image type
		EImageType GetImageType() const;
		/// Sets the image type of the image
		void SetImageType( EImageType eType );

		/// Returns the type of the capture device
		ECaptureDevice GetCaptureDevice() const;
		/// Sets the capture device which was used to capture the image
		void SetCaptureDevice( ECaptureDevice eType );

        /**@brief Copies the image data to the given address.
         *
         * Note that the memory must have been allocated prior to calling this function. The allocated size
         * has to be of size image width * image height
         *@param [in] pImageData Pointer to a block of memory where the image data should be written to.
         *@throw std::invalid_argument if the data of the image is not valid
         */
		void GetData( unsigned char * pImageData ) const;

	private:
		/// internal implementation of an image
		friend class CImageImplAcc;
		class CImageImpl * m_pImpl;
	};

	/**@brief Class for an image with external image data.
	 *
	 * Usually this class is used if image data has already been allocated elsewhere and a copy is not wanted.
	 * Internally this class holds only a pointer to the given image data, so data is not copied at all.
	 * Note that this class only operates as a view to the image data, therefore the user has to take care of releasing the memory.
	 *
	 *@see CImage for internally managed image data
	 */
	class MIRLIN_EXPORT CImageView
	{
	public:
		/// Default construction
		CImageView();
		/**@brief Constructs with the given image data and size.
		 *
		 *@param [in] pImageData Pointer to the block of memory holding the image data
		 *@param [in] nImageWidth Width of the image
		 *@param [in] nImageHeight Height of the image
		 */
		explicit CImageView( const unsigned char * pImageData, int nImageWidth, int nImageHeight );
		/// Copy construction, the data itself does not get copied
		CImageView( const CImageView & roThat );
		/// Destructor
		~CImageView();
		/**
         *@brief Assignment operator.
         * Note that this does not copy the image data, instead both objects refer to the same original block of memory
         */
		CImageView & operator=( const CImageView & roThat );

		/// Returns whether the image is valid, e.g. has valid data
		bool IsValid() const;

		/// Returns the image type
		EImageType GetImageType() const;
		/// Sets the image type of the image
		void SetImageType( EImageType eType );

		/// Returns the type of the capture device
		ECaptureDevice GetCaptureDevice() const;
		/// Sets the capture device which was used to capture the image
		void SetCaptureDevice( ECaptureDevice eType );

	private:
		/// internal implementation of the image view
		friend class CImageImplAcc;
		class CImageViewImpl * m_pImpl;
	};
	///@}

	/**@brief Definition of template classes and result structs
	 *@addtogroup MIR_TemplateStructs Template types and comparison result
	 *@ingroup MIR_Template
	 */
	///@{
	/**@brief Holds the result of a template comparison
	 *
	 *@see CompareTemplates
	 */
	struct MIRLIN_EXPORT SComparisonResult
	{
		/// Holds whether the comparison was successful and therefore whether the results are valid
		bool bIsValid;
		/// Resultant Co-Occlusion in %
		double dCoOcclusion;
		/// Resultant Hamming distance
		double dHammingDistance;

		/// Default construction
		SComparisonResult();
	};

	/// Eye type used to initalise a template
	enum EEyeType
	{
		eUnknownEye = 0,	///< Defines an unknown eye which is taken as default for template generation
		eRightEye,			///< Right eye
		eLeftEye			///< Left eye
	};

	/// Possible number of rotations in a match template
	enum ENumRotations
	{
		eSingleRotation  =  1,	///< Single rotation is mandatory for enrol templates and optional for match templates
		eNumRotations5   =  5,	///< Defines a match template with 5 Rotations
		eNumRotations7   =  7,	///< Defines a match template with 7 Rotations
		eNumRotations9   =  9,	///< Defines a match template with 9 Rotations
		eNumRotations13  = 13,	///< Defines a match template with 13 Rotations which is the default setting for a match template
		eNumRotations25  = 25	///< Defines a match template with 25 Rotations
	};

	/**@brief Implementation of an enrol template.
	 *
	 *  An enrol template is initalised with the eye type.
	 *@see CMatchTemplate
	 */
	class MIRLIN_EXPORT CEnrolTemplate
	{
	public:
		/**@brief Constructs an enrol template with the given eye type
		 *
		 *@param [in] oEyeType Defines if the template is generated from a left or a right eye; default is unknown.
		 */
		explicit CEnrolTemplate( EEyeType oEyeType = eUnknownEye );
		/**@brief Constructs an enrol template with the given block of memory
		 *
		 *@param [in] pTemplateData Pointer to a block of memory holding the template data. Note that the data is copied and managed internally.
		 *@throw std::invalid_argument if the data of the template is not a valid enrol template
		 */
		explicit CEnrolTemplate( const unsigned char * pTemplateData );
		/// Copy construction, the data itself does not get copied
		CEnrolTemplate( const CEnrolTemplate & roThat );
		/// Destructor
		~CEnrolTemplate();
        /// Assignment operator.  The data itself does not get copied.
		CEnrolTemplate & operator=( const CEnrolTemplate & roThat );

		/// Returns whether the template is valid, e.g. has valid data
		bool IsValid() const;
		/// Returns the eye type of the template
		EEyeType GetEyeType() const;
		/// Returns the size of the template
		int GetSize() const;
		/**@brief Copies the template data to the given adress.
		 *
		 * Note that the memory must have been allocated prior to calling this function. The allocated size has to be of size returned by GetSize()
		 *@param [in] pTemplateData Pointer to a block of memory where the template data should be written to.
		 *@throw std::invalid_argument if the data of the template is not valid
		 */
		void GetData( unsigned char * pTemplateData ) const;
	private:
		/// internal implementation of the template
		friend class CTemplateImplAcc;
		class CEnrolTemplateImpl * m_pImpl;
	};

	/**@brief Implementation of a match template.
	 *
	 *  A match template is initalised with the number of rotations and the eye type.
	 @see CEnrolTemplate
	 */
	class MIRLIN_EXPORT CMatchTemplate
	{
	public:
		/**@brief Construct a match template with the given eye type and number of rotations.
		 *
		 *@param [in] oEyeType Defines if the template is generated from a left or a right eye; default is unknown.
		 *@param [in] oNumRotations Number of rotations used for template generation; default is 13.
		 *@throw std::invalid_argument if an invalid parameter was passed in
		 */
		explicit CMatchTemplate( EEyeType oEyeType = eUnknownEye, ENumRotations oNumRotations = eNumRotations13 );
		/**@brief Construct a match template with the given block of memory
		 *
		 *@param [in] pTemplateData Pointer to a block of memory holding the template data. Note that the data is copied and managed internally.
		 *@throw std::invalid_argument if the given data is not a valid template
		 */
		explicit CMatchTemplate( const unsigned char * pTemplateData );
		/// Copy construction, the data itself does not get copied
		CMatchTemplate( const CMatchTemplate & roThat );
		/// Destructor
		~CMatchTemplate();
		/// Assignment operator.  The data itself does not get copied.
		CMatchTemplate & operator=( const CMatchTemplate & roThat );

		/// Returns whether the template is valid, e.g. has valid data
		bool IsValid() const;
		/// Returns the eye type of the template
		EEyeType GetEyeType() const;
		/// Returns the size of the template
		int GetSize() const;
        /// Returns the number of rotations
        ENumRotations GetRotations() const;

		/**@brief Copies the template data to the given address.
		 *
		 * Note that the memory must have been allocated before. The allocated size has to be of size returned by GetSize()
		 *@param [in] pTemplateData Pointer to a block of memory where the template data should be written to.
		 *@throw std::invalid_argument if the data of the template is not valid, or if pTemplateData is NULL.
		 */
		void GetData( unsigned char * pTemplateData ) const;
	private:
		/// internal implementation of the image
		friend class CTemplateImplAcc;
		class CMatchTemplateImpl * m_pImpl;
	};


	/**@brief Implementation of a enrol template container.
	 *
	 * This container holds a number of enrol templates to be used for comparison of templates in a multi-threaded way.
     *
	 *  @see CEnrolTemplate
     *  @see CompareTemplates
	 */
	class MIRLIN_EXPORT CEnrolTemplateContainer
	{
	public:
		/**@brief Construct the container and initialises it with the given number of templates.
		 *
		 *@param [in] nNumTemplates Number of templates the container should get initialised with
		 */
        explicit CEnrolTemplateContainer( int nNumTemplates = 0 );
        /// Copy construction
        CEnrolTemplateContainer( const CEnrolTemplateContainer & roThat );
        /// Destructor
        ~CEnrolTemplateContainer();
		/// Assignment operator.
		CEnrolTemplateContainer & operator=( const CEnrolTemplateContainer & roThat );

        /// Returns the size of the enrol template container
        int size() const;

        /**@brief Returns a reference to the enrol template at the given position
         *
         *@param [in] nIndex position of the requested enrol template in the container
         *@throw out_of_range exception if the index is out of range
         */
        const CEnrolTemplate & operator[]( int nIndex ) const;
	    /**
	     *@copydoc operator[]( int ) const
	     */
        CEnrolTemplate & operator[]( int nIndex );
        /** Adds a new enrol template at the end of the container.
         *
         *@param [in] roTemplate enrol template to be added to the container.
         */
        void push_back( const CEnrolTemplate & roTemplate );

    private:
		/// internal implementation of the container
		friend class CContainerImplAcc;
		class CEnrolTemplateContainerImpl * m_pImpl;
    };

    /**@brief Implementation of a comparison result container.
     *
     * This container holds the comparison results of comparing a number of enrol templates with a match template.
     *
     *  @see SComparisonResult
     *  @see CompareTemplates
     */
	class MIRLIN_EXPORT CComparisonResultContainer
	{
	public:
		/**@brief Construct the container and initialises it with the given number of result structs.
		 *
		 *@param [in] nNumResults Number of comparison results the container should get initialised with
		 */
        explicit CComparisonResultContainer( int nNumResults = 0 );
        /// Copy construction
        CComparisonResultContainer( const CComparisonResultContainer & roThat );
        /// Destructor
        ~CComparisonResultContainer();
		/// Assignment operator.
		CComparisonResultContainer & operator=( const CComparisonResultContainer & roThat );

        /// Returns the size of the comparison result container
        int size() const;

        /**@brief Returns a reference to the enrol template at the given position
         *
         *@param [in] nIndex position of the requested comparison result in the container
         *@throw out_of_range exception if the index is out of range
         */
        const SComparisonResult & operator[]( int nIndex ) const;
	    /**
	     *@copydoc operator[]( int ) const
	     */
        SComparisonResult & operator[]( int nIndex );

    private:
		/// internal implementation of the container
		friend class CContainerImplAcc;
		class CComparisonResultContainerImpl * m_pImpl;
    };
	///@}


    /// MIRLIN SDK Configuration
	namespace Config
	{
		/**@brief Information about MIRLIN SDK and Licenses
		 *
		 *@addtogroup MIR_Config Configuration and License Control
		 *@ingroup MIR
		 */

        /**@brief Information such as the version number of MIRLIN SDK and build date can be found here
         * @addtogroup MIR_Config_Info Information about MIRLIN SDK
         * @ingroup MIR_Config
         */
        ///@{
        /**@brief Returns the version number of MIRLIN SDK.
         *
         */
        MIRLIN_EXPORT const char * GetVersion();
        /**@brief Returns the build date of MIRLIN SDK.
         *
         */
        MIRLIN_EXPORT const char * GetBuildDate();
        ///@}

        /**@brief Check whether a valid license was found, set license files and get information about the current license.
         * @addtogroup MIR_Config_License License related settings
         * @ingroup MIR_Config
         */
        ///@{
        /**@brief Sets the license source to be used by license control system.
         *
         * If the license is specified as a file, then this file will be used. The license can also be specified
         * as a path, so that all licenses files in this path will be considered. In case of a license server the
         * license is specified as "port@host", e.g. "5053@SomeHost".
         * Note that the license file should be set BEFORE any template generation or matching functions
         * are called. If a new license is set whilst other license protected functions are in use the method will
         * throw an std::logic_error exception
         *@param [in] pLicense License to be used for license control
         */
        MIRLIN_EXPORT void SetLicense( const char * pLicense );
        /**@brief Returns whether or not the license for the given product is valid.
         *
         *@param [in] pProduct Name of the product as defined in the license file.
         */
        MIRLIN_EXPORT bool HaveValidLicense( const char * pProduct );
        /**@brief Returns the status of the license.
         *
         *@param [out] pStatusMsg Status message of the license for the requested product.
         *@param [in] nMsgSize Size allocated for the status message (pStatusMsg[nMsgSize]).
         *                      If the status message is longer than the allocated buffer size then the message is truncated.
         *@param [in] pProduct Name of the product as defined in the license file.
         */
        MIRLIN_EXPORT void GetLicenseStatus( char * pStatusMsg, int nMsgSize, const char * pProduct );
        ///@}
    }

} // namespace MIR


/**
 * @defgroup MIR_C C style interface for MIRLIN
 * C-style interface for experts. Be careful when using it. Memory has to be allocated and released by
 * the user.
 */
extern "C"
{
    /**@brief Error codes and typedefs
     *
     *@defgroup MIR_C_Def Error codes and typedefs
     *@ingroup MIR_C
     */
    ///@{

    /** @name Typedefs
    */
    ///@{
    /**
     * A type definition for an unsigned char
     */
    typedef unsigned char UINT8;
    /**
     * A type definition for a signed int
     */
    typedef signed int INT32;
    ///@}

    /** @name MIRLIN error codes
     *
     */
    ///@{
    #define MIR_SUCCESS                 0   ///< Defines success, so everything went well
    #define MIR_GENERIC_ERROR          -1   ///< Generic error indicating that something not obvious went wrong
    #define MIR_LICENSE_ERROR          -2   ///< License is not valid, see @ref MIR_GetLicenseStatus for more information
    #define MIR_NULL_POINTER           -3   ///< A null pointer was passed in as parameter
    #define MIR_SEGMENTATION_FAILED    -4   ///< Indicates that pupil/iris segmentation was not successful
    #define MIR_INVALID_ROTATION_VALUE -5   ///< Wrong number of rotations for a match template was specified; see @ref MIR_InitialiseMatchTemplate for more information
    #define MIR_READ_FILE_ERROR        -6   ///< Reading from disk failed
    #define MIR_WRITE_FILE_ERROR       -7   ///< Writing to disk failed
    #define MIR_INVALID_ARGUMENT       -8   ///< An invalid parameter was specified

    ///@}
    ///@}


	/**@brief Everything related to images, i.e. visualisation, import and export, ...
	 *
	 *@defgroup MIR_C_Image Images
	 *@ingroup MIR_C
	 */

	/**@brief Definition of an image, segmentation result and enumeration types
	 *
	 *@addtogroup MIR_C_ImageStructs Image and result structs
	 *@ingroup MIR_C_Image
	 */
	///@{

	/// Specially supported capture devices
	enum MIR_CAPTURE_DEVICE
    {
        Unspecified,	    ///< Indicates an arbitrary capture device
        EY2H			    ///< Image was captured by an EY2H
    };

	/// Possible image types
	enum MIR_IMAGE_TYPE
    {
        Default,	   ///< Indicates a default image type
        ISOType2,      ///< Image is an %ISO type 2 iris image
        ISOType3,      ///< Image is an %ISO type 3 iris image
        ISOType7       ///< Image is an %ISO type 7 iris image
    };

	/**@brief Structure for an image with external image data.
     * @note This class only operates as a view to the image data, therefore the user has to take care
     * of allocating and releasing the memory.
     *
     *@see MIR_InitImage to initalise the fields of the structure
	 */
    typedef struct MIR_IMAGE
    {
        /// Specifies the capture device which was used to capture the image
        MIR_CAPTURE_DEVICE CaptureDevice;
        /// Specifies the image type of the image
        MIR_IMAGE_TYPE ImageType;

        /// Image width
        INT32 Width;
        /// Image height
        INT32 Height;
        /// Pointer to the image data
        UINT8 * pImageData;

    } MIR_IMAGE;

	/**@brief Holds the segmentation result
     *@par 
     * The segmentation result consists of pupil and iris if segmentation was
     * successful
     */
    typedef struct MIR_SEGMENTATION_RESULT
    {
        /// True if segmentation was successful, otherwise false
        bool Success;

        /// X-coordinate of the pupil centre
        INT32 PupilCentreX;
        /// Y-coordinate of the pupil centre
        INT32 PupilCentreY;
        /// Radius of the pupil
        INT32 PupilRadius;

        /// X-coordinate of the iris centre
        INT32 IrisCentreX;
        /// Y-coordinate of the iris centre
        INT32 IrisCentreY;
        /// Radius of the iris
        INT32 IrisRadius;

	    /**@brief Percentage of usable iris area
         *@par 
         * This metric details the amount of usable iris area of the segmented
         * image.  The Segmented pupil and iris, eyelids and specular
         * reflections are considered when calculating the percentage of the
         * visible iris area.  Value range: 0 - 100 (Higher = Better)
		 */
        double UsableIrisArea;

    } MIR_SEGMENTATION_RESULT;
	///@}

	/**@brief Functions to initialise an image and visualise segmentation result
	 *
	 *@addtogroup MIR_C_ImageFunctions Image functions
	 *@ingroup MIR_C_Image
	 */
	///@{
    /**@brief Initialises all the fields of an MIR_IMAGE
     *
     *@param [out] pImage Image where where the size and data is set to 0
     *@param [in] CaptureDevice Capture device which was used to capture the image
     *@param [in] ImageType Image type of the image
     *@see MIR_IMAGE
     */
    MIRLIN_EXPORT void MIR_InitImage( MIR_IMAGE * pImage, MIR_CAPTURE_DEVICE CaptureDevice, MIR_IMAGE_TYPE ImageType );

	/**@brief Visualises the segmentation result on the given image.
	 *
	 * Draws the segmentation result, i.e. pupil and iris, on the given input image.
	 *@param [out] pImage Image, on which the segmentation result is drawn
	 *@param [in] pSegResult Segmentation result obtained by MIR_GetTemplateSegResult()
	 *@returns MIR_SUCCESS if drawing was successful
	 */
    MIRLIN_EXPORT INT32 MIR_VisualiseSegResult( MIR_IMAGE * pImage, const MIR_SEGMENTATION_RESULT * pSegResult );
	///@}

	/**@brief All necessary functions to load and save images
	 *@defgroup MIR_C_ImageIO Image import and export
	 *@ingroup MIR_C_Image
	 */
	///@{
	/**
	 *@name Load Image
	 */
	///@{
    /**
     * Loads the header from disk and writes to width and height.  NOTE that
     * pImage::pImageData is set to NULL. Further, image type and capture device
     * are set to default values and have to be adjusted after reading the image data.
     *
     * \param [out] pImage The structure that is written to.
     * \param [in] pFilename The filename of the image to read.
     */
    MIRLIN_EXPORT INT32 MIR_ReadImageHeader( MIR_IMAGE * pImage, const char * pFilename );
	/**@brief Loads an image from file.
	 *
     *@pre The memory for the image was allocated by the user before reading the image from disk.
     *@see MIR_ReadImageHeader to get the size of the image and thus the size needed to be allocated.
     *
     * Please note that image type and capture device
     * are set to default values and have to be adjusted after loading the image.
     *
	 *@param [out] pImage Loaded image
	 *@param [in] pFilename Input filename
	 *@returns MIR_SUCCESS if loading the image from disk was successful.
	 */
    MIRLIN_EXPORT INT32 MIR_LoadImage( MIR_IMAGE * pImage, const char * pFilename );
    ///@}
	/**
	 *@name Save Images
	 */
	///@{
    /**@brief Saves and image to disk.
     *
     *@param [in] pImage The image to be saved.
     *@param [in] pFilename The file name to store the image to
     *@return MIR_SUCCESS if the image was written successfully
     */
    MIRLIN_EXPORT INT32 MIR_SaveImage( const MIR_IMAGE * pImage, const char * pFilename );
    ///@}
    ///@}

	/**@brief Everything related to the ISO iris image standard
	 *
	 *@addtogroup MIR_C_IS0 ISO iris image types and quality metrics calculation
	 *@ingroup MIR_C
	 *
	 * Functions and structs for calculating ISO iris image quality metrics and
	 * ISO type images.
	 */
	///@{
    /// ISO iris image quality metrics calculated on an image only
	typedef struct MIR_QUALITY_METRIC
	{
		/// Focus of the image. Value range: 0 - 100 (Higher = Better)
		double Focus;
		/// Contrast of the image. Value range: 0 - 100 (Higher = Better)
		double Contrast;
		/// Entropy or histogram utilisation of the histogram. Values are negative (Smaller = Better)
		double Entropy;

	} MIR_QUALITY_METRIC;

    /**@brief Calculates ISO iris image quality metric of the given input image.
	 *
	 *@param [out] pMetricResult Calculated ISO iris image quality metric
	 *@param [in] pImage Input image used to calculate the quality metric
	 *@returns @ref MIR_SUCCESS if the calculation was successful
	 */
    MIRLIN_EXPORT INT32 MIR_GetQualityMetric( MIR_QUALITY_METRIC * pMetricResult, const MIR_IMAGE * pImage );

    /**@brief Specifies an ISO/IEC 19794-6:2011 image type.
     *
	 */
    enum MIR_IRIS_IMAGE_OUTPUT_TYPE
    {
        OutputISOType3,  ///< Specifies a cropped iris image
        OutputISOType7   ///< Specifies a cropped and masked iris image
    };
    /**@brief Creates an ISO/IEC 19794-6:2011 image.
	 *
	 *@param [out] pIrisImage Resulting ISO iris image. Allocate the same size as the input image, width and height are set to
     * the new size of the image.
	 *@param [out] pSegResult Segmentation result of the given input image
	 *@param [in] eImageType Specifies the desired ISO iris image type
	 *@param [in] pSrcImage Input image which gets segmented.
	 *@returns @ref MIR_SUCCESS if creating the image was successful
	 */
    MIRLIN_EXPORT INT32 MIR_CreateIrisImage( MIR_IMAGE * pIrisImage, MIR_SEGMENTATION_RESULT * pSegResult,
                                             MIR_IRIS_IMAGE_OUTPUT_TYPE eImageType, const MIR_IMAGE * pSrcImage );
    ///@}


	/**@brief Template types, template generation and comparison
	 *@addtogroup MIR_C_Template Templates
	 *@ingroup MIR_C
	 */
	/**@brief Definition of template and comparison result structs
	 *@addtogroup MIR_C_TemplateStructs Template types and comparison result
	 *@ingroup MIR_C_Template
	 */
	///@{
    /// Template comparison result
	typedef struct MIR_COMPARISON_RESULT
	{
		/// Resultant Co-Occlusion %
		double CoOcclusion;
        /// Resultant Hamming distance
		double HammingDistance;

	} MIR_COMPARISON_RESULT;

    /**
      * \brief Stores both Enrol and Match templates
      */
	typedef struct MIR_TEMPLATE
	{
		/**
		 * Pointer to the data; initialise to NULL.
		 */
		UINT8 * pData;

	} MIR_TEMPLATE;

    /// Defines the eye type
	enum MIR_EYETYPE
	{
		UnknownEye = 0,	    ///< Defines an unknown eye which is taken as default for template generation
		RightEye,			///< Right eye
		LeftEye			    ///< Left eye
	};
    ///@}

	/**@brief Template generation, comparison and I/O
	 *@addtogroup MIR_C_TemplateFunctions Template generation, comparison and I/O
	 *@ingroup MIR_C_Template
	 */
	///@{
	/**
	 *@name Initialise templates
	 */
	///@{
    /**
     *@brief Returns the overall enrol template size.
     * This is most likely to be useful if the user is to take care of all memory
     * allocation
     *@return the enrol template size
     */
    MIRLIN_EXPORT INT32 MIR_GetEnrolTemplateSize();

    /**
     *@brief Returns the overall template size for a given rotation.
     * This is most likely to be useful if the user is to take care of all memory
     * allocation
     *@param [in] nNumRotations Number of rotations of a match template, may be one of 25, 13, 9, 7, 5, or 1
     *@return the match template size
     */
    MIRLIN_EXPORT INT32 MIR_GetMatchTemplateSize( UINT8 nNumRotations );

    /**
     *@brief  This function initialises an allocated enrol template.
     *
     *@param [in] pEnrolTemplate This must be a valid pointer to an allocated enrol template
     *@param [in] EyeType eyetype of the template
     *@see MIR_GetEnrolTemplateSize
     */
    MIRLIN_EXPORT INT32 MIR_InitialiseEnrolTemplate( MIR_TEMPLATE * pEnrolTemplate, MIR_EYETYPE EyeType );

    /**@brief  This function initialises an allocated match template
     *
     *@param [in] pMatchTemplate This must be a valid pointer to an allocated match template
     *@param [in] EyeType eyetype of the template
     *@param [in] nNumRotations Number of rotations of a match template, may be one of 25, 13, 9, 7, 5, or 1
     *@see MIR_GetMatchTemplateSize
     */
    MIRLIN_EXPORT INT32 MIR_InitialiseMatchTemplate( MIR_TEMPLATE * pMatchTemplate, MIR_EYETYPE EyeType, UINT8 nNumRotations );
	///@}

	/**
	 *@name Generate templates
	 */
	///@{
	/**@brief This function takes in an image, and returns a template.
	 *
	 *@param [out] pTemplate Pointer to a MIR_TEMPLATE. pTemplate should
     *                        be initialised using the function @ref MIR_InitialiseEnrolTemplate or @ref MIR_InitialiseMatchTemplate
	 *@param [in] pImage Pointer to the image array.
     *
	 *@return @ref MIR_SUCCESS if there is no error.
	 */
    MIRLIN_EXPORT INT32 MIR_GetTemplate( MIR_TEMPLATE * pTemplate, const MIR_IMAGE * pImage );

    /**@brief This function takes in an image, and returns a template and the segmentation result.
     *
     * @param [out] pTemplate pointer to a MIR_TEMPLATE.  Should be initialised using the function @ref MIR_InitialiseEnrolTemplate or @ref MIR_InitialiseMatchTemplate.
     * @param [out] pSegResult pointer to a segmentation result struct
     * @param [in] pImage Pointer to the image array.
     *
     * @return @ref MIR_SUCCESS if there is no error.
     */
    MIRLIN_EXPORT INT32 MIR_GetTemplateSegResult( MIR_TEMPLATE * pTemplate, MIR_SEGMENTATION_RESULT * pSegResult, const MIR_IMAGE * pImage );
	///@}

	/**
	 *@name Compare templates
	 */
	///@{
	/**@brief Compares two templates and stores the result
	 *
	 * @param [out] pResult Pointer to a valid MIR_COMPARISON_RESULT object
	 * @param [in] pEnrolTemplate Enrol template
	 * @param [in] pMatchTemplate Match template
	 * @return @ref MIR_SUCCESS if there is no error.
     *
	 * @see MIR_GetTemplate
     */
	MIRLIN_EXPORT INT32 MIR_CompareTemplates( MIR_COMPARISON_RESULT * pResult,
        const MIR_TEMPLATE * pEnrolTemplate, const MIR_TEMPLATE * pMatchTemplate );

    /**
     * Compares a single match template against a database of enrol templates,
     * using multi-threading where available.
     *
     * @param [out] pResultList pointer to a block of memory containing nListSize results structures.
     * @param [in] nListSize The number of enrol templates.
     * @param [in] pEnrolTemplateList pointer to a block memory containing of nListSize enrol templates
     * @param [in] pMatchTemplate match template
     *
     * @return @ref MIR_SUCCESS if there is no error.
     */
    MIRLIN_EXPORT INT32 MIR_CompareMultiTemplates( MIR_COMPARISON_RESULT * pResultList, int nListSize,
        const MIR_TEMPLATE *pEnrolTemplateList, const MIR_TEMPLATE * pMatchTemplate );
	///@}

	/**
	 *@name Template I/O
	 */
	///@{
    /**
     * Reads the header of the template and determines the size of the template.
     *
     *@param [in] pFilename : The name of the template
     *@return the size of the template
     */
    MIRLIN_EXPORT INT32 MIR_ReadTemplateSize( const char * pFilename );

    /**
     * Load a template from disk.
     *@param [out] pTemplate Pointer to a template, where the template on disk is to be stored.
     *@param [in] pFilename : The name of the template to be loaded.
     *@return @ref MIR_SUCCESS if no error has occured
     *@pre Ensure `pTemplate` is valid and correct size has been allocated
     */
    MIRLIN_EXPORT INT32 MIR_LoadTemplate( MIR_TEMPLATE * pTemplate, const char * pFilename );

    /**
     * Saves a template to disk.
     *@param [in] pTemplate The template to store.
     *@param [in] pFilename The file name to save the template to.
     *@return @ref MIR_SUCCESS if no error has occured
     */
    MIRLIN_EXPORT INT32 MIR_SaveTemplate( const MIR_TEMPLATE * pTemplate, const char * pFilename );
	///@}
	///@}


	/**@brief Information about MIRLIN SDK and Licenses
     *
	 *@addtogroup MIR_C_Config Configuration and License Control
	 *@ingroup MIR_C
	 */
    /**@brief Information such as the version number of MIRLIN SDK and build date can be found here
     * @addtogroup MIR_C_Config_Info Information about MIRLIN SDK
     * @ingroup MIR_C_Config
     */
    ///@{
    /**@brief Returns the version number of MIRLIN SDK.
     *
     */
    MIRLIN_EXPORT const char * MIR_GetVersion();
    /**@brief Returns the build date of MIRLIN SDK.
     *
     */
    MIRLIN_EXPORT const char * MIR_GetBuildDate();
    ///@}

    /**@brief Check whether a valid license was found, set license files and get information about the current license.
     * @addtogroup MIR_C_Config_License License related settings
     * @ingroup MIR_C_Config
     */
    ///@{
    /**@brief Sets the license source to be used by license control system.
     *
     * If the license is specified as a file, then this file will be used. The license can also be specified
     * as a path, so that all licenses files in this path will be considered. In case of a license server the
     * license is specified as "port@host", e.g. "5053@SomeHost".
     * Note that the license file should be set BEFORE any template generation or matching functions
     * are called. If a new license is set whilst other license protected functions are in use the method will
     * return a @ref MIR_LICENSE_ERROR
     *@param [in] pLicense License to be used for license control
     */
    MIRLIN_EXPORT INT32 MIR_SetLicense( const char * pLicense );
    /**@brief Returns whether or not the license for the given product is valid.
     *
     *@param [in] pProduct Name of the product as defined in the license file.
     */
    MIRLIN_EXPORT bool MIR_HaveValidLicense( const char * pProduct );
    /**@brief Returns the status of the license.
     *
     *@param [out] pStatusMsg Status message of the license for the requested product.
     *@param [in] nMsgSize Size allocated for the status message (pStatusMsg[nMsgSize]).
     *                      If the status message is longer than the allocated buffer size then the message is truncated.
     *@param [in] pProduct Name of the product as defined in the license file.
     */
    MIRLIN_EXPORT void MIR_GetLicenseStatus( char * pStatusMsg, int nMsgSize, const char * pProduct );
    ///@}

} // extern "C"

#endif // _MIRLIN_H
