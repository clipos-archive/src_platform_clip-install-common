// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2007-2018 ANSSI. All Rights Reserved.
/**
 * clip_install.c - C wrapper for clip-install.
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 * Copyright (C) 2012 SGDSN/ANSSI
 * All rights reserved.
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#define CLIP_INSTALL BINDIR"/_clip_install"

int 
main(int argc, char *argv[])
{
	char *envp[] = { NULL, NULL };

	if (argc < 1)
		return EXIT_FAILURE; /* ?? */

	if (getuid() || geteuid()) {
		fputs("Only runnable by root\n", stderr);
		return EXIT_FAILURE;
	}

	envp[0] = strdup("PATH=/bin:/sbin:/usr/bin:/usr/sbin");
	if (!envp[0]) {
		fputs("Out of memory ???\n", stderr);
		return EXIT_FAILURE;
	}

	argv[0] = strdup(CLIP_INSTALL);
	if (!argv[0]) {
		fputs("Out of memory ???\n", stderr);
		return EXIT_FAILURE;
	}

	if (execve(CLIP_INSTALL, argv, envp)) {
		fprintf(stderr, "Failed to execute %s: %s\n", 
					CLIP_INSTALL, strerror(errno));
		return EXIT_FAILURE;
	}

	/* Not reached */
	return EXIT_FAILURE;
}
