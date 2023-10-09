#include <windows.h>
#include <errno.h>
#include "misc_internal.h"
#include "inc/pwd.h"
#include "inc/spawn.h"
#include "unistd.h"
#include "Debug.h"

int posix_spawn_internal(pid_t *pidp, const char *path, const posix_spawn_file_actions_t *file_actions, const posix_spawnattr_t *attrp, char *const argv[], char *const envp[], HANDLE user_token, BOOLEAN prepend_module_path);

int
__posix_spawn_asuser(pid_t *pidp, const char *path, const posix_spawn_file_actions_t *file_actions, const posix_spawnattr_t *attrp, char *const argv[], char *const envp[], char* user)
{
	extern HANDLE password_auth_token;
	extern HANDLE sspi_auth_user;

	int r = -1;
	/* use token generated from password auth if already present */
	HANDLE user_token = NULL;
	
	if (password_auth_token)
		user_token = password_auth_token;
	else if (sspi_auth_user) 
		user_token = sspi_auth_user;

	if (!user_token && (user_token = get_user_token(user, 1)) == NULL) {
		error("unable to get security token for user %s", user);
		errno = EOTHER;
		return -1;
	}
	else if (am_system()) {
		load_user_profile(user_token, user);
	}
	else {
		// last resort: drop user token is the requested user is ourselves
		char* current_principal = get_principal_username();
		if(current_principal) {
			if(!strcmp(user, current_principal)) {
				user_token = NULL;
			}
			free(current_principal);
		}
	}
	
	r = posix_spawn_internal(pidp, path, file_actions, attrp, argv, envp, user_token, TRUE);
	CloseHandle(user_token);
	return r;
}