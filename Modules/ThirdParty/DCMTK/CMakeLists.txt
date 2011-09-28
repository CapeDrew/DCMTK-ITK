project(ITKDCMTK)
set(ITKDCMTK_THIRD_PARTY 1)

if(ITK_USE_SYSTEM_DCMTK)
  set(ITKDCMTK_SYSTEM_INCLUDE_DIRS
    ${DCMTK_INCLUDE_DIRS}
    )
  set(ITKDCMTK_INCLUDE_DIRS ${DCMTK_INCLUDE_DIRS})
  set(ITKDCMTK_LIBRARIES ITKDCMTK)
else()
  set(ITKDCMTK_INCLUDE_DIRS
    ${ITKDCMTK_BINARY_DIR}
    ${ITKDCMTK_BINARY_DIR}/include
    ${ITKDCMTK_BINARY_DIR}/include/dcmtk/config
    ${ITKDCMTK_SOURCE_DIR}/config/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmdata/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmimage/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmimgle/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmjpeg/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmjpls/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmnet/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmpstat/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmqrdb/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmsign/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmsr/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmtls/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/dcmwlm/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/oflog/include/dcmtk
    ${ITKDCMTK_SOURCE_DIR}/ofstd/include/dcmtk
    )
  set(ITKDCMTK_LIBRARIES  dcmdata dcmdsig dcmimage dcmimgle dcmjpeg dcmnet dcmpstat dcmqrdb dcmsr dcmtls dcmwlm ijg8 ijg12 ijg16 oflog ofstd )
endif()

itk_module_impl()
