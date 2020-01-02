#	 Upanix - An x86 based Operating System
#	 Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa_prajwal@yahoo.co.in'
#																			 
#	 This program is free software: you can redistribute it and/or modify
#	 it under the terms of the GNU General Public License as published by
#	 the Free Software Foundation, either version 3 of the License, or
#	 (at your option) any later version.
#																			 
#	 This program is distributed in the hope that it will be useful,
#	 but WITHOUT ANY WARRANTY; without even the implied warranty of
#	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	 GNU General Public License for more details.
#																			 
#	 You should have received a copy of the GNU General Public License
#	 along with this program.  If not, see <http://www.gnu.org/licenses/
cmake_minimum_required(VERSION 3.15)
project(UpanixApps)

set(CROSS_TOOL_PATH $ENV{HOME}/opt/cross)
set(OUTPUT_DIR ${PROJECT_SOURCE_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

set(CMAKE_CXX_COMPILER ${CROSS_TOOL_PATH}/bin/i686-elf-g++)
set(CMAKE_C_COMPILER ${CROSS_TOOL_PATH}/bin/i686-elf-gcc)
set(CMAKE_LINKER ${CROSS_TOOL_PATH}/i686-elf/bin/ld)
set(CMAKE_AR ${CROSS_TOOL_PATH}/i686-elf/bin/ar)

set(SO_COMPILE_FLAGS -shared -fPIC)
set(SO_LD_FLAGS " -Wl,-shared -Wl,-fPIC")

#set(CMAKE_CXX_FLAGS " -O0 -Wall -ffreestanding -nodefaultlibs -nostdlib -nostartfiles -nostdinc -std=c++11 -nostdinc++ -fno-threadsafe-statics -fpermissive ${EXCEPTION_SUP}")
set(COMMON_COMPILE_FLAGS " -Wall -nostdlib -nodefaultlibs -ffreestanding -nostdinc -nostartfiles -D__GCC__")
set(CMAKE_C_FLAGS ${COMMON_COMPILE_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS ${COMMON_COMPILE_FLAGS})
set(CMAKE_SHARED_LINKER_FLAGS "${COMMON_COMPILE_FLAGS} ${SO_LD_FLAGS}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${PROJECT_SOURCE_DIR}/libc/include)
include_directories(${PROJECT_SOURCE_DIR}/libc/stdio)
include_directories(${PROJECT_SOURCE_DIR}/libc/sysdeps/mos/common)
include_directories(${PROJECT_SOURCE_DIR}/libc/sysdeps/mos/common/bits)

include_directories(${PROJECT_SOURCE_DIR}/libm/include)
include_directories(${PROJECT_SOURCE_DIR}/libm/include/bits)

include_directories(${PROJECT_SOURCE_DIR}/libmcal/include)

include_directories(${PROJECT_SOURCE_DIR}/libmterm/include)

#LIBC
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./libc -name '*.c' | grep -v CMakeFile" OUTPUT_VARIABLE LIBC_SRC)
string(REPLACE "\n" ";" LIBC_SRC ${LIBC_SRC})
add_library(c SHARED "${LIBC_SRC}")
target_compile_options(c PRIVATE -O0 ${SO_COMPILE_FLAGS})

#LIBIT
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./libit -name '*.c' | grep -v CMakeFile" OUTPUT_VARIABLE LIBIT_SRC)
string(REPLACE "\n" ";" LIBIT_SRC ${LIBIT_SRC})
add_library(it STATIC "${LIBIT_SRC}")

#LIBM
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./libm -name '*.c' | grep -v CMakeFile" OUTPUT_VARIABLE LIBM_SRC)
string(REPLACE "\n" ";" LIBM_SRC ${LIBM_SRC})
add_library(m SHARED "${LIBM_SRC}")
target_compile_options(m PRIVATE ${SO_COMPILE_FLAGS})

#LIBMCAL
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./libmcal -name '*.c' | grep -v CMakeFile" OUTPUT_VARIABLE LIBMCAL_SRC)
string(REPLACE "\n" ";" LIBMCAL_SRC ${LIBMCAL_SRC})
add_library(mcal SHARED "${LIBMCAL_SRC}")
target_compile_options(mcal PRIVATE ${SO_COMPILE_FLAGS})

#LIBMTERM
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./libmterm -name '*.c' | grep -v CMakeFile" OUTPUT_VARIABLE LIBMTERM_SRC)
string(REPLACE "\n" ";" LIBMTERM_SRC ${LIBMTERM_SRC})
add_library(mterm SHARED "${LIBMTERM_SRC}")
target_compile_options(mterm PRIVATE ${SO_COMPILE_FLAGS})

link_directories(${OUTPUT_DIR})

#NASM
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./nasm/nasm_src -name '*.c' | grep -v CMakeFile" OUTPUT_VARIABLE NASM_SRC)
string(REPLACE "\n" ";" NASM_SRC ${NASM_SRC})
add_executable(nasm "${NASM_SRC}")
add_dependencies(nasm c)
target_compile_options(nasm PRIVATE -O2)
target_link_options(nasm PRIVATE -e main)
target_include_directories(nasm PRIVATE ${PROJECT_SOURCE_DIR}/nasm/include)
target_link_libraries(nasm c)

#NDISASM
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./nasm/ndisasm_src -name '*.c' | grep -v CMakeFile" OUTPUT_VARIABLE NDISASM_SRC)
string(REPLACE "\n" ";" NDISASM_SRC ${NDISASM_SRC})
add_executable(ndisasm "${NDISASM_SRC}")
add_dependencies(ndisasm c)
target_compile_options(ndisasm PRIVATE -O2)
target_link_options(ndisasm PRIVATE -e main)
target_include_directories(ndisasm PRIVATE ${PROJECT_SOURCE_DIR}/nasm/include)
target_link_libraries(ndisasm c)

#SHELL
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./shell -name '*.c' | grep -v CMakeFile" OUTPUT_VARIABLE MSH_SRC)
string(REPLACE "\n" ";" MSH_SRC ${MSH_SRC})
add_executable(msh "${MSH_SRC}")
add_dependencies(msh c)
target_include_directories(msh PRIVATE ${PROJECT_SOURCE_DIR}/shell)
target_compile_options(msh PRIVATE -O2)
target_link_options(msh PRIVATE -e main)
target_link_libraries(msh c)

#EDITOR
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./editor -name '*.c' | grep -v CMakeFile" OUTPUT_VARIABLE EDITOR_SRC)
string(REPLACE "\n" ";" EDITOR_SRC ${EDITOR_SRC})
add_executable(edit "${EDITOR_SRC}")
add_dependencies(edit c)
target_include_directories(edit PRIVATE ${PROJECT_SOURCE_DIR}/editor)
target_compile_options(edit PRIVATE -O2)
target_link_options(edit PRIVATE -e main)
target_link_libraries(edit c)
target_link_libraries(edit mterm)