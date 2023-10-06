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
dep_libzlib = dependency('zlib', method: 'pkg-config')

lib_openbsd = shared_library('openbsdcompat', openbsdcompat_srcs + files('hash.c'),
    include_directories: [win32iocompat_inc],
    link_with: [lib_win32io],
    dependencies: [dep_openssl],
    link_args: wingw_linker_caveats + ['-lws2_32'])

core_srcs_common = [
        'addr.c',
        'addrmatch.c',
        'atomicio.c',
        'authfd.c',
        'authfile.c',
        'bitmap.c',
        'canohost.c',
        'chacha.c',
        'channels.c',
        'cipher-aes.c',
        'cipher-aesctr.c',
        'cipher-chachapoly.c',
        'cipher.c',
        'cleanup.c',
        'compat.c',
        'dns.c',
        'ed25519.c',
        'entropy.c',
        'fatal.c', # diag
        'gss-genr.c',
        'hash.c',
        'hmac.c',
        'hostfile.c',
        'kex.c',
        'kexc25519.c',
        'kexgen.c',
        'kexsntrup761x25519.c',
        'krl.c',
        'log.c', # diag
        'mac.c',
        'match.c',
        'misc.c',
        'moduli.c',
        'monitor_fdpass.c',
        'msg.c',
        'nchan.c',
        'packet.c',
        'poly1305.c',
        'progressmeter.c',
        'readpass.c',
        'rijndael.c',
        'smult_curve25519_ref.c',
        'sntrup761.c',
        'ssh-ed25519.c',
        'ssh-pkcs11.c',
        'sshbuf-getput-basic.c',
        'sshbuf-getput-crypto.c',
        'sshbuf-misc.c',
        'sshbuf.c',
        'ssherr.c',
        'sshkey.c',
        'ssh_api.c',
        'umac.c',
        'xmalloc.c',
        'platform-misc.c',
        'platform-pledge.c',
        'platform-tracing.c',
        'platform.c',
        'sandbox-pledge.c',
        'contrib/win32/win32compat/ttymodes_windows.c',
        'contrib/win32/win32compat/w32-sshfileperm.c',
        'kexgexs.c',
        'ssh-ecdsa-sk.c',
        'ssh-ed25519-sk.c',
        'ssh-sk.c',
        'sshbuf-io.c',
        'cipher-chachapoly-libcrypto.c',
        'contrib/win32/win32compat/spawn-ext.c',
        # mistakenly omitted from solution
        'utf8.c',
        'dispatch.c',
    ]

core_srcs_openssl = [
        'dh.c',
        'kexdh.c',
        'kexecdh.c',
        'kexgex.c',
        'kexgexc.c',
        'ssh-dss.c',
        'ssh-ecdsa.c',
        'ssh-rsa.c',
        'digest-openssl.c',
        # see: https://github.com/openssl/openssl/issues/13631
        # and: https://github.com/openssl/openssl/issues/13411
        # and: https://github.com/openssl/openssl/issues/17369
        'openbsd-compat/libressl-api-compat.c',
    ]

core_srcs_libressl = [
        'digest-libc.c',
    ]

lib_coressh = shared_library('coressh', core_srcs_common + core_srcs_openssl,
    include_directories: [win32iocompat_inc, common_header_dir],
    link_with: [lib_win32io, lib_openbsd],
    dependencies: [dep_openssl, dep_libzlib],
    link_args: wingw_linker_caveats + ['-lws2_32'])

