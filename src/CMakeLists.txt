if (NOT TESTING)
  find_package(Boost)
  set(sources
    localRun.cpp
    Program.cpp
    Board.cpp
    Snail.cpp
    Cell.cpp )
  add_executable(localRun ${sources})
  target_include_directories(localRun PUBLIC ${Boost_INCLUDE_DIRS})
endif()
