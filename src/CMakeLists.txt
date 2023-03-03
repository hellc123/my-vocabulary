add_executable(my_vocabulary "main.cpp" "word.h" "word.cpp" "wordMap.h" "wordMap.cpp")

#用于提高警告等级
if(MSVC)
  target_compile_options(my_vocabulary PRIVATE /W4 )
else()
  target_compile_options(my_vocabulary PRIVATE -Wall -Wextra )
  #-Wpedantic -Werror)
endif()