cmake_minimum_required(VERSION 3.19)
project(a10_915_Nedelcu_Alexandru_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH /Users/alexnedelcu/Qt/Tools/CMake//CMake.app/Contents/MacOS/CMake)
set(Qt5_DIR /Users/alexnedelcu/Qt/5.15.2/clang_64/lib/cmake/Qt5)
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

include_directories(BUSINESS)
include_directories(DOMAIN)
include_directories(EXCEPTIONS)
include_directories(GUI)
include_directories(PERSISTENCE)
include_directories(START)
include_directories(VALIDATION)

add_executable(a10_915_Nedelcu_Alexandru_1
        BUSINESS/AdminService.cpp
        BUSINESS/AdminService.h
        BUSINESS/UserService.cpp
        BUSINESS/UserService.h
        DOMAIN/Date.cpp
        DOMAIN/Date.h
        DOMAIN/Event.cpp
        DOMAIN/Event.h
        EXCEPTIONS/BaseException.cpp
        EXCEPTIONS/BaseException.h
        EXCEPTIONS/RepositoryException.cpp
        EXCEPTIONS/RepositoryException.h
        EXCEPTIONS/ValidationException.cpp
        EXCEPTIONS/ValidationException.h
        GUI/AdminGUI.cpp
        GUI/AdminGUI.h
        GUI/ModeOptionsGUI.cpp
        GUI/ModeOptionsGUI.h
        GUI/PersistenceOptionsGUI.cpp
        GUI/PersistenceOptionsGUI.h
        GUI/UserGUI.cpp
        GUI/UserGUI.h
        PERSISTENCE/CSVFileRepository.cpp
        PERSISTENCE/CSVFileRepository.h
        PERSISTENCE/FileRepository.cpp
        PERSISTENCE/FileRepository.h
        PERSISTENCE/HTMLEventsRepository.cpp
        PERSISTENCE/HTMLEventsRepository.h
        PERSISTENCE/MemoryRepository.cpp
        PERSISTENCE/MemoryRepository.h
        PERSISTENCE/VirtualRepository.cpp
        PERSISTENCE/VirtualRepository.h
        START/StarterGUI.cpp
        START/StarterGUI.h
        VALIDATION/Validator.cpp
        VALIDATION/Validator.h
        VALIDATION/VirtualValidator.cpp
        VALIDATION/VirtualValidator.h
        main.cpp MODEL_VIEW_DESIGN_PATTERN/EventsTableModel.cpp MODEL_VIEW_DESIGN_PATTERN/EventsTableModel.h COMMAND_DESIGN_PATTERN/ICommand.cpp COMMAND_DESIGN_PATTERN/ICommand.h COMMAND_DESIGN_PATTERN/AddCommand.cpp COMMAND_DESIGN_PATTERN/AddCommand.h COMMAND_DESIGN_PATTERN/RemoveCommand.cpp COMMAND_DESIGN_PATTERN/RemoveCommand.h COMMAND_DESIGN_PATTERN/UpdateCommand.cpp COMMAND_DESIGN_PATTERN/UpdateCommand.h COMMAND_DESIGN_PATTERN/CommandManager.cpp COMMAND_DESIGN_PATTERN/CommandManager.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})