# Define the files we need to compile.
# Anything not in this list will not be compiled into libGDL.
set(SOURCES
  node.hpp
  basic_construct.hpp
  basic_construct_impl.hpp
  function_policy.hpp
  function_policy.cpp
  relation_policy.hpp
  relation_policy.cpp
  clause_policy.hpp
  clause_policy.cpp
)

# add directory name to sources
set(DIR_SRCS)
foreach(file ${SOURCES})
  set(DIR_SRCS ${DIR_SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/${file})
endforeach()
# Append sources (with directory name) to list of all libgdl sources (used at
# the parent scope).
set(GDL_SRCS ${GDL_SRCS} ${DIR_SRCS} PARENT_SCOPE)
