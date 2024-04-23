cmake_minimum_required(VERSION 3.27)
project(qrz)

set(CMAKE_CXX_STANDARD 20)

add_executable(qrz src/main.cpp
        src/Action.h
        src/AppCommand.cpp
        src/AppCommand.h
        src/AppController.cpp
        src/AppController.h
        src/AppFormat.h
        src/Configuration.h
        src/Configuration.cpp
        src/QRZClient.h
        src/Util.h
        src/Util.cpp
        src/exception/AuthenticationException.cpp
        src/model/Callsign.h
        src/model/CallsignMarshaler.cpp
        src/model/DXCC.h
        src/model/DXCCMarshaler.cpp
        src/progressbar/BlockProgressBar.h
        src/progressbar/DefaultProgressBar.h
        src/progressbar/ProgressBar.h
        src/render/BioRenderer.h
        src/render/CallsignConsoleRenderer.h
        src/render/CallsignCSVRenderer.h
        src/render/CallsignMarkdownRenderer.h
        src/render/CallsignJSONRenderer.h
        src/render/CallsignXMLRenderer.h
        src/render/DXCCConsoleRenderer.h
        src/render/DXCCCSVRenderer.h
        src/render/DXCCJSONRenderer.h
        src/render/DXCCMarkdownRenderer.h
        src/render/DXCCXMLRenderer.h
        src/render/Renderer.h
        src/render/RendererFactory.h
)

find_package(argparse REQUIRED)
find_package(indicators REQUIRED)
find_package(libconfig REQUIRED)
find_package(Poco REQUIRED)
find_package(tabulate REQUIRED)

target_link_libraries(qrz
    libconfig::libconfig
    argparse::argparse
    tabulate::tabulate
    indicators::indicators
    Poco::Poco
)