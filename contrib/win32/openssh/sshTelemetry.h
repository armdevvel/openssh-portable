#pragma once

// sends authentication type and status
inline void send_auth_telemetry(const int status, const char* auth_type) {}

// sends authentication methods configured by SSHD
inline void send_auth_method_telemetry(const char* auth_methods) {}

// sends crypto information like cipher, kex, and mac
inline void send_encryption_telemetry(const char* direction, 
	const char* cipher, const char* kex, const char* mac, 
	const char* comp, const char* host_key, 
	const char** cproposal, const char** sproposal) {}

// sends status if using key-based auth
inline void send_pubkey_telemetry(const char* pubKeyStatus) {}

// sends shell configuration and if pty session is used
inline void send_shell_telemetry(const int pty, const int shell_type) {}

// sends signing status if using key-based auth
inline void send_pubkey_sign_telemetry(const char* pubKeySignStatus) {}

// sends connection status from ssh client
inline void send_ssh_connection_telemetry(const char* conn, const char* port) {}

// sends connection status from ssh server
inline void send_sshd_connection_telemetry(const char* conn) {}

// sends version and peer version from ssh & sshd
inline void send_ssh_version_telemetry(const char* ssh_version,
	const char* peer_version, const char* remote_protocol_error) {}
