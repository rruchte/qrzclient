from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain

class ConanApplication(ConanFile):
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.generate()

    def requirements(self):
        requirements = self.conan_data.get('requirements', [])
        for requirement in requirements:
            self.requires(requirement)

    def configure(self):
        self.options["poco"].enable_data = False
        self.options["poco"].enable_activerecord = False
        self.options["poco"].enable_data_postgresql = False
        self.options["poco"].enable_data_mysql = False
        self.options["poco"].enable_data_sqlite = False
        self.options["poco"].enable_odbc = False
        self.options["poco"].enable_apacheconnector = False
        self.options["poco"].enable_pdf = False
        self.options["poco"].enable_pagecompiler = False
        self.options["poco"].enable_pagecompiler_file2page = False