cmake_minimum_required(VERSION 3.27)
project(qrz)

set(CMAKE_CXX_STANDARD 20)

add_executable(qrz main.cpp
        Action.h
        AppCommand.cpp
        AppCommand.h
        AppController.cpp
        AppController.h
        AppFormat.h
        Configuration.h
        Configuration.cpp
        QRZClient.h
        Util.h
        Util.cpp
        exception/AuthenticationException.cpp
        model/Callsign.h
        model/CallsignMarshaler.cpp
        model/DXCC.h
        model/DXCCMarshaler.cpp
        render/BioRenderer.h
        render/CallsignConsoleRenderer.h
        render/CallsignCSVRenderer.h
        render/CallsignMarkdownRenderer.h
        render/CallsignJSONRenderer.h
        render/CallsignXMLRenderer.h
        render/DXCCConsoleRenderer.h
        render/DXCCCSVRenderer.h
        render/DXCCJSONRenderer.h
        render/DXCCMarkdownRenderer.h
        render/DXCCXMLRenderer.h
        render/Renderer.h
        render/RendererFactory.h
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