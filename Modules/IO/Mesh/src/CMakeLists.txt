set(ITKIOMesh_SRC
  itkBYUMeshIO.cxx
  itkBYUMeshIOFactory.cxx
  itkFreeSurferAsciiMeshIO.cxx
  itkFreeSurferAsciiMeshIOFactory.cxx
  itkFreeSurferBinaryMeshIO.cxx
  itkFreeSurferBinaryMeshIOFactory.cxx
  itkGiftiMeshIO.cxx
  itkGiftiMeshIOFactory.cxx
  itkMeshIOBase.cxx
  itkMeshIOFactory.cxx
  itkOBJMeshIO.cxx
  itkOBJMeshIOFactory.cxx
  itkOFFMeshIO.cxx
  itkOFFMeshIOFactory.cxx
  itkVTKPolyDataMeshIO.cxx
  itkVTKPolyDataMeshIOFactory.cxx
)

add_library(ITKIOMesh ${ITKIOMesh_SRC})
target_link_libraries(ITKIOMesh ${ITKCommon_LIBRARIES} ${ITKGIFTI_LIBRARIES} ${ITKIOBase_LIBRARIES})

itk_module_target(ITKIOMesh)
