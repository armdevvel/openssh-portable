project('Win32OpenSSH', 'c', version: '9.4.0.0') # from version.rc

# common VC++ tuning
add_global_arguments('-D_CRT_DECLARE_NONSTDC_NAMES=0', language: 'c')
add_global_arguments('-D_LIB', language: 'c')
add_global_arguments('-DUSE_MSCNG', language: 'c')
add_global_arguments('-D_WIN32_WINNT=0x600', language: 'c')
add_global_arguments('-DWIN3', language: 'c')
add_global_arguments('-DNDEBU', language: 'c')
add_global_arguments('-D_LIB', language: 'c')

# compatibility
add_global_arguments('-DEOTHER=EIO', language: 'c')
wingw_linker_caveats = ['-Wl,--allow-multiple-definition']

# porter's assumptions
add_global_arguments('-DGSSAPI', language: 'c')

# supply chain
add_global_arguments('-DWITH_OPENSSL=1', language: 'c')

# debugging
add_global_arguments('-DSTDERR_LOG_LEVEL=SYSLOG_LEVEL_INFO', language: 'c')

# common includes: config.h, sshTelemetry.h (dumbed)
common_header_dir = 'contrib/win32/openssh'
win32iocompat_dir = 'contrib/win32/win32compat'
win32iocompat_inc = win32iocompat_dir + '/inc'
openbsdcompat_dir = 'openbsd-compat'

subdir(win32iocompat_dir)

lib_win32io = shared_library('win32iocompat', win32iocompat_srcs,
    include_directories: [win32iocompat_dir, common_header_dir],
    link_args: wingw_linker_caveats + [
        '-lkernel32',
        '-lshlwapi',
        '-lwsock32',
        '-lws2_32',
        '-lcrypt32',
        '-lsecur32',
        '-luserenv',
        '-lntoskrnl',
    ])

subdir(openbsdcompat_dir)

dep_openssl = dependency('openssl', method: 'pkg-config')

lib_openbsd = shared_library('openbsdcompat', openbsdcompat_srcs + files('hash.c'),
    include_directories: [win32iocompat_inc],
    link_with: [lib_win32io],
    dependencies: [dep_openssl],
    link_args: wingw_linker_caveats + ['-lws2_32'])

# lib_logging = shared_library('logging', ['log.c', 'fatal.c'],
#     include_directories: win32iocompat_inc,
#     link_args: ['-Wl,--allow-multiple-definition'])

