cmake_minimum_required (VERSION 3.8)


project(TheGreatSnailRace CXX)
add_compile_options(-Wall -Wextra -Werror)

if ( TESTING_ONLY )
  set ( TESTING 1)
endif()

# Build student code
add_subdirectory(src)

# If we're testing build the tester directory
if ( TESTING )
  enable_testing()
  message(STATUS "Enabling testing!")
  add_subdirectory(tester)
endif()
