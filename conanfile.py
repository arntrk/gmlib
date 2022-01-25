from conans import CMake, ConanFile, tools
from conans.tools import load, SystemPackageTool
from conan.tools.cmake import CMakeDeps
import re
import os


class SentryRWSConan(ConanFile):
    name = "sentry-rws"
    url = "https://github.com/arntrk/SplineBasis.git"
    version = "0.0.1"
    exports = "README.md"
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "shared": [True, False],
        "examples": [True, False],
        "tests": [True, False],
    }

    default_options = {
        "shared": True,
        "examples": False,
        "tests": False,
    }

    generators = "cmake_paths"

    scm = {
        "type": "git",
        "url": url,
        "revision": "auto"
    }

    def requirements(self):
        if self.options.tests:
            self.requires("catch2/2.13.8")
        
        if self.options.examples:
            self.requires("glfw/3.3.6")
            self.requires("glew/2.2.0")

    def generate(self):
        cmake = CMakeDeps(self)
        cmake.generate()

    def configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_SHARED_LIBS"] = self.options.shared
        cmake.definitions["BUILD_EXAMPLES"] = self.options.examples
        cmake.definitions["BUILD_TESTS"] = self.options.tests     
        cmake.configure()
        return cmake

    def build(self):
        cmake = self.configure_cmake()
        cmake.build()

    def package(self):
        cmake = self.configure_cmake()
        cmake.install()

    def package_info(self):
        # Tell CMakeDeps not to generate cmake files
        self.cpp_info.set_property("cmake_find_mode", "none")
