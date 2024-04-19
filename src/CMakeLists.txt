set(SOURCES
    CircularBuffer.hpp
    ConcurrentQueue.hpp
)

add_library(containers ${SOURCES})
set_target_properties(containers PROPERTIES LINKER_LANGUAGE CXX)
