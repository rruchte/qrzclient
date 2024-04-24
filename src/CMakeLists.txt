add_executable(qrz main.cpp
        Action.h
        AppCommand.cpp
        AppCommand.h
        AppController.cpp
        AppController.h
        Configuration.h
        Configuration.cpp
        OutputFormat.h
        QRZClient.h
        Util.h
        Util.cpp
        exception/AuthenticationException.cpp
        model/Callsign.h
        model/CallsignMarshaler.cpp
        model/DXCC.h
        model/DXCCMarshaler.cpp
        progressbar/BlockProgressBar.h
        progressbar/DefaultProgressBar.h
        progressbar/ProgressBar.h
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