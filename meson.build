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

# debugging (win32io)
add_global_arguments('-DSTDERR_LOG_LEVEL=SYSLOG_LEVEL_INFO', language: 'c')

# clutter
add_global_arguments('-Wno-comment', language: 'c')
add_global_arguments('-Wno-parentheses', language: 'c')
add_global_arguments('-Wno-unused-variable', language: 'c')
add_global_arguments('-Wno-pointer-sign', language: 'c')
add_global_arguments('-Wno-deprecated-declarations', language: 'c')

# common includes: config.h, sshTelemetry.h (dumbed)
common_header_dir = 'contrib/win32/openssh'
win32iocompat_dir = 'contrib/win32/win32compat'
win32iocompat_inc = win32iocompat_dir + '/inc'
openbsdcompat_dir = 'openbsd-compat'

subdir(win32iocompat_dir)

platform_libraries = [
        '-lkernel32',
        '-lshlwapi',
        '-lwsock32',
        '-lws2_32',
        '-lcrypt32',
        '-lsecur32',
        '-luserenv',
        '-lntdll',
    ]

lib_win32io = shared_library('win32iocompat', win32iocompat_srcs,
    include_directories: [win32iocompat_dir, common_header_dir],
    link_args: wingw_linker_caveats + platform_libraries,
    install: true)

subdir(openbsdcompat_dir)

dep_openssl = dependency('openssl', method: 'pkg-config')
dep_libzlib = dependency('zlib', method: 'pkg-config')

lib_openbsd = shared_library('openbsdcompat', openbsdcompat_srcs + files('hash.c'),
    include_directories: [win32iocompat_inc],
    link_with: [lib_win32io],
    dependencies: [dep_openssl],
    link_args: wingw_linker_caveats + ['-lws2_32'],
    install: true)

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
        'contrib/win32/win32compat/ttymodes_windows.c', #  etc. push down
        'kexgexs.c',
        'ssh-ecdsa-sk.c',
        'ssh-ed25519-sk.c',
        'ssh-sk.c',
        'sshbuf-io.c',
        'cipher-chachapoly-libcrypto.c',
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
    link_args: wingw_linker_caveats + ['-lws2_32'],
    install: true)

# version.rc is compiled externally to version.o
wingw_linked_version = ['version.o']

wingw_linked_console = ['-mconsole', '-municode']

# Executables: keygen scp sftp sftp-server ssh-add ssh-agent ssh-keyscan ssh-pkcs11-helper ssh-shellhost [ssh-sk-helper] ssh sshd

winmain = files(
    'contrib/win32/win32compat/wmain_common.c',
    'contrib/win32/win32compat/win32-utf8.c',
)

sftpsrc = files(
    'sftp-client.c',
    'sftp-common.c',
    'sftp-glob.c',
    'sftp-usergroup.c',
)

subdir('contrib/win32/win32compat/ssh_agent')

toolkit = [
    ['ssh-keygen', winmain + files(
        'ssh-keygen.c',
        'sshsig.c',
        'ssh-sk-client.c',
    ), []],
    ['ssh', winmain + files(
        'clientloop.c',
        'readconf.c',
        'ssh.c',
        'sshconnect.c',
        'sshconnect2.c',
        'contrib/win32/win32compat/win32_sshtty.c', # push down
        'ssh-sk-client.c',
        'sshkey.c',
    ), ['-lws2_32']],
    ['sshd', files(
        'audit-bsm.c',
        'audit-linux.c',
        'audit.c',
        'auth-bsdauth.c',
        'auth-krb5.c',
        'auth-options.c',
        'auth-pam.c',
        'auth-passwd.c',
        'auth-rhosts.c',
        'auth-shadow.c',
        'auth-sia.c',
        'auth.c',
        'auth2-chall.c',
        'auth2-gss.c',
        'auth2-hostbased.c',
        'auth2-kbdint.c',
        'auth2-none.c',
        'auth2-passwd.c',
        'auth2-pubkey.c',
        'auth2.c',
        'gss-serv-krb5.c',
        'gss-serv.c',
        'loginrec.c',
        'monitor.c',
        'monitor_wrap.c',
        'platform.c',
        'sandbox-capsicum.c',
        'sandbox-darwin.c',
        'sandbox-null.c',
        'sandbox-rlimit.c',
        'sandbox-seccomp-filter.c',
        'sandbox-systrace.c',
        'servconf.c',
        'serverloop.c',
        'session.c',
        'sftp-common.c',
        'sshd.c',
        'sshlogin.c',
        'auth2-pubkeyfile.c',
        'srclimit.c',
        'ssh-sk-client.c',
        'sshkey.c',
        'contrib/win32/win32compat/win32_groupaccess.c', # ...push down...
        'contrib/win32/win32compat/win32_sshpty.c',
        'contrib/win32/win32compat/wmain_sshd.c', # not wmain_common!
        'contrib/win32/win32compat/w32-doexec.c',
        'contrib/win32/win32compat/win32-utf8.c',
    ), ['-lws2_32', '-lcrypt32']],
    ['scp', winmain + sftpsrc + files('scp.c'), ['-lws2_32']],
    ['sftp', winmain + sftpsrc + files(
        'sftp.c',
        'progressmeter.c',
    ), ['-lws2_32']],
    ['sftp-server', winmain + files(
        'sftp-common.c',
        'sftp-server-main.c',
        'sftp-server.c',
    ), ['-lws2_32']],
    ['ssh-add', winmain + files(
        'ssh-add.c',
        'ssh-sk-client.c', # ?
    ), ['-lws2_32']],
    ['ssh-keyscan', winmain + files(
        'ssh-keyscan.c',
        'ssh-sk-client.c', # ?
    ), ['-lws2_32']],
    ['ssh-agent', ssh_agent_srcs + files(
        'ssh-pkcs11-client.c',
        'ssh-sk-client.c'
    ), ['agent-events.o', '-lcrypt32']],
    ['ssh-pkcs11-helper', winmain + files(
        'ssh-pkcs11-helper.c',
        'ssh-pkcs11.c',
        'ssh-sk-client.c', # ?
    ), []],
    ['ssh-shellhost', files(
        'contrib/win32/win32compat/shell-host.c', # ...push down
        'contrib/win32/win32compat/utf.c'
    ), []],
    # ['ssh-sk-helper', winmain + files(
    #     'ssh-sk-helper.c',
    #     'ssh-sk.c',
    #     'sk-usbhid.c',
    # ), []],
]

foreach tool : toolkit
    executable(tool[0], tool[1],
        include_directories: [win32iocompat_inc, common_header_dir],
        link_with: [lib_win32io, lib_openbsd, lib_coressh],
        dependencies: [dep_openssl, dep_libzlib],
        link_args: wingw_linker_caveats + wingw_linked_version + wingw_linked_console + tool[2],
        install: true)
endforeach

# TODO install headers and export libraries
