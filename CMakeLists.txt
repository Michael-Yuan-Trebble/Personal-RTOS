cmake_minimum_required(VERSION 3.21)

project(PersonalRTOS LANGUAGES C ASM_MASM)

set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)

if (MSVC)
	enable_language(ASM_MASM)
endif()

set (RTOS_SOURCES
	main.c
	cpu.c
	queue.c
	scheduler.c
	tasks.c
	time.c)

set (RTOS_ASM_SOURCES cpu.asm)

add_executable(PersonalRTOS ${RTOS_SOURCES} ${RTOS_ASM_SOURCES})
