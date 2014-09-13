#find_library(MGL mgl PATHS /usr/local/lib)

ADD_EXECUTABLE(
  eye-see-you
  main.cpp
  findEyeCenter.cpp
  findEyeCenter.h
  constants.h
  helpers.cpp
  helpers.h
  findEyes.cpp
  findEyes.h
  )
TARGET_LINK_LIBRARIES( eye-see-you ${OpenCV_LIBS} )
#target_link_libraries( eye-see-you ${MGL})
