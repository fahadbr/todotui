cmake_minimum_required(VERSION 3.14)

set(HUNTER_URL "https://github.com/cpp-pm/hunter/archive/v0.23.260.tar.gz")
set(HUNTER_SHA1 "13775235910a3fa85644568d1c5be8271de72e1c")
set(HUNTER_PACKAGES
  GTest
  ncursesw
)

include(FetchContent)
FetchContent_Declare(SetupHunter GIT_REPOSITORY https://github.com/cpp-pm/gate)
FetchContent_MakeAvailable(SetupHunter)
