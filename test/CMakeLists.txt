find_package(GTest REQUIRED)

add_executable(qrz_test
        util_test.cpp
        AppControllerProxy.h
        MockClient.h
        ../src/Util.h
        ../src/Util.cpp
        configuration_test.cpp
        ../src/Configuration.h
        ../src/Configuration.cpp
        app_command_test.cpp
        ../src/AppCommand.h
        ../src/AppCommand.cpp
        app_controller_test.cpp
        ../src/AppController.h
        ../src/AppController.cpp
        ../src/exception/AuthenticationException.h
        ../src/exception/AuthenticationException.cpp
        ../src/model/CallsignMarshaler.h
        ../src/model/CallsignMarshaler.cpp
        ../src/model/DXCCMarshaler.h
        ../src/model/DXCCMarshaler.cpp
        marshaler_test.cpp
        qrz_client_test.cpp
        ../src/QRZClient.h
        render_test.cpp
        ../src/render/RendererFactory.h

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