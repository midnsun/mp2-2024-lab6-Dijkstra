set(GVC "gvc")
set(CGRAPH "cgraph")

target_sources(${PROJECT_NAME} lib/gvc.lib lib/cgraph.lib )

add_library(${GVC} PUBLIC STATIC lib/gvc.lib)
add_library(${CGRAPH} PUBLIC STATIC lib/cgraph.lib)

target_link_libraries(${GVC} ${CGRAPH})