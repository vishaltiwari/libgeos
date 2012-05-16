#################################################################################
#
# GEOS XML tests runner build configuration for CMake build system
#
# Copyright (C) 2009 Mateusz Loskot <mateusz@loskot.net>
#
# This is free software; you can redistribute and/or modify it under
# the terms of the GNU Lesser General Public Licence as published
# by the Free Software Foundation. 
# See the COPYING file for more information.
#
#################################################################################

set(STATUS_MESSAGE "Enable GEOS XML Tester build")
set(STATUS_RESULT "OFF")

if(GEOS_ENABLE_TESTS)

  include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tinyxml)

  set(simplewkttester_SOURCES SimpleWKTTester.cpp)

  set(xmltester_SOURCES
    XMLTester.cpp
    tinyxml/tinyxml.cpp
    tinyxml/tinystr.cpp
    tinyxml/tinyxmlerror.cpp
    tinyxml/tinyxmlparser.cpp
    BufferResultMatcher.cpp
    SingleSidedBufferResultMatcher.cpp)

  add_executable(simplewkttester ${simplewkttester_SOURCES})
  if(APPLE AND GEOS_ENABLE_MACOSX_FRAMEWORK)
    target_link_libraries(simplewkttester GEOS)
 	else()
    target_link_libraries(simplewkttester geos)
 	endif()

  add_executable(xmltester ${xmltester_SOURCES})
  if(APPLE AND GEOS_ENABLE_MACOSX_FRAMEWORK)
    target_link_libraries(xmltester GEOS)
 	else()
    target_link_libraries(xmltester geos)
  endif()

  set(XMLTESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
  set(SAVE_XMLTESTS
	${XMLTESTS_DIR}/tests/testLeaksBig.xml 
	${XMLTESTS_DIR}/tests/split.xml 
	${XMLTESTS_DIR}/tests/hexwkb.xml 
	${XMLTESTS_DIR}/tests/test.xml 
	${XMLTESTS_DIR}/tests/linemerge.xml 
	${XMLTESTS_DIR}/tests/TestIsValid.xml 
	${XMLTESTS_DIR}/tests/robustness.xml 
	${XMLTESTS_DIR}/tests/buffer.xml 
	${XMLTESTS_DIR}/tests/singlesidedbuffer.xml 
	${XMLTESTS_DIR}/tests/ticket/bug176.xml 
	${XMLTESTS_DIR}/tests/ticket/bug188.xml 
	${XMLTESTS_DIR}/tests/ticket/bug244.xml 
	${XMLTESTS_DIR}/tests/ticket/bug275.xml 
	${XMLTESTS_DIR}/tests/ticket/bug350.xml 
	${XMLTESTS_DIR}/tests/ticket/bug356.xml 
	${XMLTESTS_DIR}/tests/ticket/bug358.xml 
	${XMLTESTS_DIR}/tests/ticket/bug360.xml 
	${XMLTESTS_DIR}/tests/ticket/bug366.xml 
	${XMLTESTS_DIR}/tests/ticket/bug392.xml 
	${XMLTESTS_DIR}/tests/ticket/bug398.xml 
	${XMLTESTS_DIR}/tests/ticket/bug434.xml 
	${XMLTESTS_DIR}/tests/ticket/bug488.xml 
	${XMLTESTS_DIR}/tests/ticket/bug527.xml 
	${XMLTESTS_DIR}/tests/general/TestBoundary.xml 
	${XMLTESTS_DIR}/tests/general/TestBuffer.xml 
	${XMLTESTS_DIR}/tests/general/TestBufferMitredJoin.xml 
	${XMLTESTS_DIR}/tests/general/TestCentroid.xml 
	${XMLTESTS_DIR}/tests/general/TestConvexHull.xml 
	${XMLTESTS_DIR}/tests/general/TestConvexHull-big.xml 
	${XMLTESTS_DIR}/tests/general/TestDistance.xml 
	${XMLTESTS_DIR}/tests/general/TestFunctionAAPrec.xml 
	${XMLTESTS_DIR}/tests/general/TestFunctionAA.xml 
	${XMLTESTS_DIR}/tests/general/TestFunctionLAPrec.xml 
	${XMLTESTS_DIR}/tests/general/TestFunctionLA.xml 
	${XMLTESTS_DIR}/tests/general/TestFunctionLLPrec.xml 
	${XMLTESTS_DIR}/tests/general/TestFunctionLL.xml 
	${XMLTESTS_DIR}/tests/general/TestFunctionPA.xml 
	${XMLTESTS_DIR}/tests/general/TestFunctionPLPrec.xml 
	${XMLTESTS_DIR}/tests/general/TestFunctionPL.xml 
	${XMLTESTS_DIR}/tests/general/TestFunctionPP.xml 
	${XMLTESTS_DIR}/tests/general/TestInteriorPoint.xml 
	${XMLTESTS_DIR}/tests/general/TestRectanglePredicate.xml 
	${XMLTESTS_DIR}/tests/general/TestRelateAA.xml 
	${XMLTESTS_DIR}/tests/general/TestRelateLA.xml 
	${XMLTESTS_DIR}/tests/general/TestRelateLL.xml 
	${XMLTESTS_DIR}/tests/general/TestRelatePL.xml 
	${XMLTESTS_DIR}/tests/general/TestRelateAC.xml 
	${XMLTESTS_DIR}/tests/general/TestRelateLC.xml 
	${XMLTESTS_DIR}/tests/general/TestRelatePA.xml 
	${XMLTESTS_DIR}/tests/general/TestRelatePP.xml 
	${XMLTESTS_DIR}/tests/general/TestSimple.xml 
	${XMLTESTS_DIR}/tests/general/TestUnaryUnion.xml 
	${XMLTESTS_DIR}/tests/general/TestUnaryUnionFloating.xml 
	${XMLTESTS_DIR}/tests/general/TestValid.xml 
	${XMLTESTS_DIR}/tests/general/TestValid2.xml 
	${XMLTESTS_DIR}/tests/general/TestValid2-big.xml 
	${XMLTESTS_DIR}/tests/general/TestWithinDistance.xml 
	${XMLTESTS_DIR}/tests/stmlf/stmlf-cases-20061020.xml 
	${XMLTESTS_DIR}/tests/stmlf/stmlf-cases-20061020-invalid-output.xml 
	${XMLTESTS_DIR}/tests/stmlf/stmlf-cases-20070119.xml 
	${XMLTESTS_DIR}/tests/robust/TestRobustOverlayFixed.xml 
	${XMLTESTS_DIR}/tests/robust/TestRobustRelate.xml 
	${XMLTESTS_DIR}/tests/fme.xml 
	${XMLTESTS_DIR}/tests/TestBufferExternal.xml 
	${XMLTESTS_DIR}/tests/TestBufferExternal2.xml 
	${XMLTESTS_DIR}/tests/heisenbugs.xml 
	${XMLTESTS_DIR}/tests/badguy3.xml 
	${XMLTESTS_DIR}/tests/hole_from_shell.xml 
	${XMLTESTS_DIR}/tests/hole_red.xml 
	${XMLTESTS_DIR}/tests/safe/16595.xml 
	${XMLTESTS_DIR}/tests/safe/16596.xml 
	${XMLTESTS_DIR}/tests/safe/TestBufferJagged.xml
	)

  add_test(xmltester ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xmltester ${SAVE_XMLTESTS})

  set(STATUS_RESULT "ON")
endif()

message(STATUS "${STATUS_MESSAGE} - ${STATUS_RESULT}")
