set(ITKIODCMTK_SRC
itkImageIO.cxx
)

add_library(ITKIODCMTK ${ITKIODCMTK_SRC})
target_link_libraries(ITKIODCMTK  ${ITKDCMTK_LIBRARIES} ${ITKIOBase_LIBRARIES} ${ITKImageIntensity_LIBRARIES})
itk_module_target(ITKIODCMTK)
