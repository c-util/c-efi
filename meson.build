project(
        'c-efi',
        'c',
        version: '1',
        license: 'Apache',
        default_options: [
                'c_std=c11'
        ],
)
project_description = 'UEFI Reference Specification Protocol Constants and Definitions'

mod_pkgconfig = import('pkgconfig')

#
# Get canonical FS paths
#

prefixdir = get_option('prefix')
datadir = join_paths(prefixdir, get_option('datadir'))

mesoncrossdir = get_option('mesoncrossdir')
if mesoncrossdir == ''
        mesoncrossdir = join_paths(datadir, 'meson/cross')
endif

#
# Config: mesoncross
#

use_mesoncross = get_option('mesoncross')

#
# Recurse into subdirs
#

subdir('src')
