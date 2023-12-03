find_package(PkgConfig REQUIRED)
function(setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  if(NOT TARGET Catch2::Catch2WithMain)
    find_package(Catch2 3 REQUIRED)
  endif()

  if(NOT TARGET PkgConfig::TBB)
    pkg_search_module(TBB REQUIRED tbb IMPORTED_TARGET)
  endif()

  find_package(fmt 10 REQUIRED )


  set( Boost_USE_STATIC_LIBS OFF )
  set(Boost_USE_MULTITHREADED ON)
  set( Boost_USE_STATIC_RUNTIME OFF )
  find_package(Boost COMPONENTS program_options REQUIRED)
  include_directories(${Boost_INCLUDE_DIR})
  link_libraries(${Boost_LIBRARIES})

endfunction()
