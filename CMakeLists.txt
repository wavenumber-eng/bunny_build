# This CMake file is picked by the Zephyr build system because it is defined
# as the module CMake entry point (see zephyr/module.yml).


# This is needed so that custom driver classes using system calls are taken into
# account

zephyr_syscall_include_directories(include)

zephyr_include_directories(include)

add_subdirectory_ifdef(CONFIG_BUNNY_BUILD src)