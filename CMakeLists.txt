cmake_minimum_required(VERSION 3.28)
project(base64 C)

set(CMAKE_C_STANDARD 17)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
# -Wall: This enables all the warnings about constructions that some users consider questionable
# -Wextra: This enables some extra warning flags that are not enabled by -Wall.
# -Wpedantic: Issue all the warnings demanded by strict ISO C and ISO C++;
#       diagnose all programs that use forbidden extensions, and some other programs that do
#       not follow ISO C and ISO C++. This follows the version of the ISO C or C++ standard
#       specified by any -std option used.
# -Werror: Make all warnings into errors.

add_executable(base64 src/main.c
        src/alphabet.h
        src/encoding.h
        src/group.h
        src/encoding.c)
