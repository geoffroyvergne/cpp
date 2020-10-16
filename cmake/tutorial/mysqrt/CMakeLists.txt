# [STATIC | SHARED | MODULE]
add_library(mysqrt STATIC mysqrt.cpp)

target_include_directories( mysqrt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )

install(TARGETS mysqrt DESTINATION lib)
install(FILES mysqrt.h DESTINATION include)
