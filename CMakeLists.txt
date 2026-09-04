cmake_minimum_required(VERSION 3.16)

project(OpenGLProject LANGUAGES C CXX) # Ensure both C and CXX are declared

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# --- configure external libraries

# Define paths to where your ImGui files live
# (Assuming they are in an 'external/imgui' folder in your project directory)
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/imgui")

# Collect core ImGui files (use GLFW+OpenGL3 as backend)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
	${IMGUI_DIR}/imgui_impl_glfw.cpp
	${IMGUI_DIR}/imgui_impl_opengl3.cpp
)

# Create static library target for GLAD and imgui using its source file
add_library(glad STATIC external/glad/src/glad.c)
add_library(imgui STATIC ${IMGUI_SOURCES})
add_subdirectory(external/wiiuse)

# 2. Provide the include paths
target_include_directories(glad PUBLIC external/glad/include)
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)

# 3. Create your main application executable
file(GLOB_RECURSE PROJECT_SOURCE CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c"
)
add_executable(wiiviz
	${PROJECT_SOURCE}
)

target_include_directories( wiiviz PUBLIC Source)

# 4. Link GLAD and GLFW to your application
target_link_libraries(wiiviz PRIVATE glad)
target_link_libraries(wiiviz PRIVATE glfw)
target_link_libraries(wiiviz PRIVATE imgui)
target_link_libraries(wiiviz PRIVATE wiiuse)

# 5. (System-specific dependency) Link the standard thread or system math/dl libraries if needed on Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(wiiviz PRIVATE ${CMAKE_DL_LIBS})
endif()
