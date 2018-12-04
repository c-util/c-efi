#
# Install meson cross-files
#

if use_mesoncross
        install_data(
                [
                        'x86_64-unknown-uefi.mesoncross.ini'
                ],
                rename: [
                        'x86_64-unknown-uefi'
                ],
                install_dir: mesoncrossdir,
        )
endif

#
# target: libcefi.dep
#

libcefi_dep = declare_dependency(
        include_directories: include_directories('.'),
        version: meson.project_version(),
)

if not meson.is_subproject()
        install_headers(
                'c-efi.h',
                'c-efi-base.h',
                'c-efi-system.h',
                'c-efi-protocol-device-path.h',
                'c-efi-protocol-device-path-from-text.h',
                'c-efi-protocol-device-path-to-text.h',
                'c-efi-protocol-device-path-utility.h',
                'c-efi-protocol-loaded-image.h',
                'c-efi-protocol-loaded-image-device-path.h',
        )

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

test_hello_world = executable('test-hello-world', ['test-hello-world.c'], dependencies: libcefi_dep)
test('UEFI Hello World', test_hello_world)

test_native = executable('test-native', ['test-native.c'], dependencies: libcefi_dep)
test('Basic Native UEFI Tests', test_native)
