# Define the files we need to compile.
# Anything not in this list will not be compiled into libGDL.
set(SOURCES
  setop.hpp
  gdl_stream.hpp
  nulloutstream.hpp
  prefixedoutstream.hpp
  prefixedoutstream_impl.hpp
  prefixedoutstream.cpp
  log.hpp
  logid.hpp
  timer.hpp
  sfinae_utility.hpp
  to_string.hpp
)

# add directory name to sources
set(DIR_SRCS)
foreach(file ${SOURCES})
  set(DIR_SRCS ${DIR_SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/${file})
endforeach()
# Append sources (with directory name) to list of all libgdl sources (used at
# the parent scope).
set(GDL_SRCS ${GDL_SRCS} ${DIR_SRCS} PARENT_SCOPE)
