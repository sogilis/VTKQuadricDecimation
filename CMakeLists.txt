
cmake_minimum_required(VERSION 2.8)

PROJECT(QuadricDecimation)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(QuadricDecimation MACOSX_BUNDLE QuadricDecimation)

if(VTK_LIBRARIES)
  target_link_libraries(QuadricDecimation ${VTK_LIBRARIES})
else()
  target_link_libraries(QuadricDecimation vtkHybrid vtkWidgets)
endif()
