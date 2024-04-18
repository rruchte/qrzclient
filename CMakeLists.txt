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

find_package(OpenSSL REQUIRED)
find_package(libconfig REQUIRED)
find_package(argparse REQUIRED)
find_package(tabulate REQUIRED)
find_package(indicators REQUIRED)
find_package(Poco REQUIRED)


target_link_libraries(qrz OpenSSL::SSL)
target_link_libraries(qrz OpenSSL::Crypto)
target_link_libraries(qrz libconfig::libconfig)
target_link_libraries(qrz argparse::argparse)
target_link_libraries(qrz tabulate::tabulate)
target_link_libraries(qrz indicators::indicators)
target_link_libraries(qrz Poco::Poco)