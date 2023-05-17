include_directories({PROJECT_SOURCE_DIR}/UIElements)
include_directories({PROJECT_SOURCE_DIR}/Easing)
add_library(GUI SHARED InertialScroll/InertialScroll.hpp InertialScroll/InertialScroll.cpp Text/Text.hpp Text/Text.cpp)