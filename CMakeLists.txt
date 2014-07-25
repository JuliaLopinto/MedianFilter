# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 2.8) 

# This project is designed to be built outside the Insight source tree.
project(MedianFilter) # PROJECT NAME

# Find ITK.
find_package(ITK REQUIRED) # FINDING ITK
include(${ITK_USE_FILE})

# Find SlicerExecutionModel
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

SEMMacroBuildCLI(
  NAME MedianFilter
  EXECUTABLE_ONLY
  TARGET_LIBRARIES ${ITK_LIBRARIES}
  LINK_DIRECTORIES ${ITK_LIBRARY_DIRS}
  INCLUDE_DIRECTORIES ${ITK_INCLUDE_DIR}
  )

set(MedianFilter_SOURCE MedianFilter.cxx)

# NAME OF EXECUTABLE TO BUILD AND SOURCE CODE
#add_executable(MedianFilter MedianFilter.cxx ) 

# NAME OF EXECUTABLE TO BUILD AND LISTE OF ALL ITK LIBRAIRIES AVAILABLE
target_link_libraries(MedianFilter ${ITK_LIBRARIES}) 


# IF YOU WANT TO MAKE SOME TEST 
option(BUILD_TESTING "Build the testing tree" ON) # activation des tests

IF(BUILD_TESTING)
  include(CTest)  
  ADD_SUBDIRECTORY(Testing) 
# appel de CTest qui va aller chercher un autre CMakeLists.txt dans le dossier Testing 
ENDIF(BUILD_TESTING)

