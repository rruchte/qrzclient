find_package(GTest REQUIRED)

add_executable(qrz_test
        ../src/Action.h
        ../src/AppCommand.cpp
        ../src/AppCommand.h
        ../src/AppController.cpp
        ../src/AppController.h
        ../src/Configuration.h
        ../src/Configuration.cpp
        ../src/OutputFormat.h
        ../src/QRZClient.h
        ../src/Util.h
        ../src/Util.cpp
        ../src/exception/AuthenticationException.cpp
        ../src/model/Callsign.h
        ../src/model/CallsignMarshaler.cpp
        ../src/model/DXCC.h
        ../src/model/DXCCMarshaler.cpp
        ../src/progressbar/BlockProgressBar.h
        ../src/progressbar/DefaultProgressBar.h
        ../src/progressbar/ProgressBar.h
        ../src/render/BioRenderer.h
        ../src/render/CallsignConsoleRenderer.h
        ../src/render/CallsignCSVRenderer.h
        ../src/render/CallsignMarkdownRenderer.h
        ../src/render/CallsignJSONRenderer.h
        ../src/render/CallsignXMLRenderer.h
        ../src/render/DXCCConsoleRenderer.h
        ../src/render/DXCCCSVRenderer.h
        ../src/render/DXCCJSONRenderer.h
        ../src/render/DXCCMarkdownRenderer.h
        ../src/render/DXCCXMLRenderer.h
        ../src/render/Renderer.h
        ../src/render/RendererFactory.h
        util_test.cpp
        AppControllerProxy.h
        MockClient.h
        configuration_test.cpp
        app_command_test.cpp
        app_controller_test.cpp
        marshaler_test.cpp
        qrz_client_test.cpp
        render_test.cpp
)

find_package(libconfig REQUIRED)
find_package(tabulate REQUIRED)
find_package(indicators REQUIRED)
find_package(Poco REQUIRED)

target_link_libraries(qrz_test
        PRIVATE
        Poco::Poco
        libconfig::libconfig
        tabulate::tabulate
        indicators::indicators
        GTest::gtest_main)

add_test(NAME qrz_gtests
        COMMAND qrz_test --gtest_color=1

)