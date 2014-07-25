set(Data Data) 

set(TEMP_DIR ${MedianFilter_BINARY_DIR}/Testing/Temporary )
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${Data} )

set(BaselineT2Radius2 ${SOURCE_DIR}/baselineT2Radius2.nrrd )
set(BaselineT2Radius4 ${SOURCE_DIR}/baselineT2Radius4.nrrd )
set(Output ${SOURCE_DIR}/Output.nrrd )
set(Input ${SOURCE_DIR}/inputT2.nrrd )
include_directories( ${CMAKE_SOURCE_DIR} )
add_executable(MedianFilterTest MedianFilterTest.cxx)
target_link_libraries(MedianFilterTest MedianFilterLib)
set( MedianFilterWithRadius2 ${TEMP_DIR}/MedianFilterWithRadius2.nrrd )
set( MedianFilterWithRadius4 ${TEMP_DIR}/MedianFilterWithRadius4.nrrd )

#######################################################################################
##########################	 TESTS ABOUT THE SYNTAX      ##########################
#######################################################################################


# Test 1 : the programm can't run without arguments
add_test(NAME OpenFileTest COMMAND $<TARGET_FILE:MedianFilter>)
set_tests_properties(OpenFileTest PROPERTIES WILL_FAIL true )



# Test 2 : the value of radius can't be under 1
add_test(NAME RadiusValue COMMAND $<TARGET_FILE:MedianFilter> # Name of the executable
${Input} # Name of the input file
${Output} # Name of the output file
-r 0 # Value of the radius
)
set_tests_properties(RadiusValue PROPERTIES WILL_FAIL true )


# Test 3 : the name of the intput value is not correct or unknown
add_test(NAME WrongInput COMMAND $<TARGET_FILE:MedianFilter> # Name of the executable
UnknownOrWrongInput.nrrd  # Name of the input file
${Output} # Name of the output file
-r 4 # Value of the radius
)
set_tests_properties(WrongInput PROPERTIES WILL_FAIL true )


#######################################################################################
##########################	  TESTS FOR COMPARAISON      ##########################
#######################################################################################

# Test 4 : Comparaison with a picture of radius 2
add_test(NAME MedianFilterRadius2 COMMAND $<TARGET_FILE:MedianFilterTest>
 --compare
   ${BaselineT2Radius2}
   ${MedianFilterWithRadius2}
 ModuleEntryPoint
   ${Input}
   ${MedianFilterWithRadius2}
   -r 2
)

# Test 5 : Comparaison with a picture of radius 4
add_test(NAME MedianFilterRadius4 COMMAND $<TARGET_FILE:MedianFilterTest>
 --compare
   ${BaselineT2Radius4}
   ${MedianFilterWithRadius4}
 ModuleEntryPoint
   ${Input}
   ${MedianFilterWithRadius4}
   -r 4
)


# Test 6 : Add command --help
add_test(NAME Help COMMAND $<TARGET_FILE:MedianFilter> --help)
