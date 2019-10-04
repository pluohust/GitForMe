#include <git2.h>

#include <iostream>

const char* path = "clone";

int cred_acquire_cb(git_cred** cred, const char* url, const char* username_from_url, unsigned int allowed_types, void* payload)
{

	//git_cred_ssh_key_new(cred, "pluohust", nullptr, "id_rsa", nullptr);
	git_cred_userpass_plaintext_new(cred, "pluohust", "251314zhxwan");

	return 0;
}

int main()
{
	git_libgit2_init();

	git_repository* rep = nullptr;
	git_clone_options opt = GIT_CLONE_OPTIONS_INIT;

	int error = 0;

	//    opt.checkout_branch = "master";
	opt.fetch_opts.callbacks.credentials = cred_acquire_cb;

	error = git_clone(&rep, "https://github.com/pluohust/Record.git", path, &opt);
	if (error < 0)
	{
		const git_error* e = giterr_last();
		std::cout << "Error: " << error << " / " << e->klass << " : " << e->message << std::endl;

		goto SHUTDOWN;
	}


SHUTDOWN:
	git_repository_free(rep);
	git_libgit2_shutdown();
}