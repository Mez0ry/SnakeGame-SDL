#add_subdirectory(Text)

include_directories({PROJECT_SOURCE_DIR}/UIElements)

add_library(GUI SHARED InertialScroll/InertialScroll.hpp InertialScroll/InertialScroll.cpp base.hpp Text/Text.hpp Text/Text.cpp)