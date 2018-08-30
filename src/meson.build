#
# target: libcefi.dep
#

libcefi_dep = declare_dependency(
        include_directories: include_directories('.'),
        version: meson.project_version(),
)

if not meson.is_subproject()
        install_headers('c-efi.h')

        mod_pkgconfig.generate(
                version: meson.project_version(),
                name: 'libcefi',
                filebase: 'libcefi',
                description: project_description,
        )
endif

#
# target: test-*
#

test_api = executable('test-api', ['test-api.c'], native: true, dependencies: libcefi_dep)
test('API Symbol Visibility', test_api)

test_basic = executable('test-basic', ['test-basic.c'], native: true, dependencies: libcefi_dep)
test('Basic Functionality', test_basic)

test_native = executable('test-native', ['test-native.c'], dependencies: libcefi_dep)
test('Basic Native UEFI Tests', test_native)
