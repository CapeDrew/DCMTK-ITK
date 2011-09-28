option(ITK_USE_SYSTEM_DCMTK "Use an outside build of DCMTK." OFF)
mark_as_advanced(ITK_USE_SYSTEM_DCMTK)

if(ITK_USE_SYSTEM_DCMTK)
  find_package(DCMTK REQUIRED)
endif()
