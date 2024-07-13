/*
 * This file is part of cparser.
 * Copyright (C) 2013 Matthias Braun <matze@braunis.de>
 */
#include "enable_posix.h"
#include "tempfile.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "adt/array.h"
#include "adt/panic.h"
#include "adt/obst.h"
#include "diagnostic.h"

static char         **temp_files;
static struct obstack file_obst;
static const char    *tempsubdir;

static const char *try_dir(const char *dir)
{
	if (dir == NULL)
		return dir;
	if (access(dir, R_OK | W_OK | X_OK) == 0)
		return dir;
	return NULL;
}

static const char *get_tempdir(void)
{
	static const char *tmpdir = NULL;

	if (tmpdir != NULL)
		return tmpdir;

	if (tmpdir == NULL)
		tmpdir = try_dir(getenv("TMPDIR"));
	if (tmpdir == NULL)
		tmpdir = try_dir(getenv("TMP"));
	if (tmpdir == NULL)
		tmpdir = try_dir(getenv("TEMP"));

#ifdef P_tmpdir
	if (tmpdir == NULL)
		tmpdir = try_dir(P_tmpdir);
#endif

	if (tmpdir == NULL)
		tmpdir = try_dir("/tmp");
	if (tmpdir == NULL)
		tmpdir = try_dir("/var/tmp");
	if (tmpdir == NULL)
		tmpdir = try_dir("/usr/tmp");

	if (tmpdir == NULL)
		tmpdir = ".";

	return tmpdir;
}

#ifndef HAVE_MKDTEMP
/* cheap and nasty mkdtemp replacement */
static char *mkdtemp(char *templ)
{
	char *res = mktemp(templ);
	if (res && mkdir(templ, 0700) != 0)
		res = NULL;
	return res;
}
#endif

static const char *make_tempsubdir(const char *tempdir)
{
	assert(obstack_object_size(&file_obst) == 0);
	obstack_printf(&file_obst, "%s/XXXXXX", tempdir);

	char       *const templ = obstack_nul_finish(&file_obst);
	char const *const dir   = mkdtemp(templ);
	if (dir == NULL) {
		position_t const pos = { templ, 0, 0, 0 };
		errorf(&pos, "mkdtemp could not create a directory from template");
		panic("abort");
	}
	return dir;
}

FILE *make_temp_file(const char *name_orig, const char **name_result)
{
	if (tempsubdir == NULL)
		tempsubdir = make_tempsubdir(get_tempdir());

	assert(obstack_object_size(&file_obst) == 0);
	obstack_printf(&file_obst, "%s/%s", tempsubdir, name_orig);

	char *const name = obstack_nul_finish(&file_obst);
	FILE *const out  = fopen(name, "w");
	if (out == NULL) {
		position_t const pos = { name, 0, 0, 0 };
		errorf(&pos, "could not create temporary file: %s", strerror(errno));
		panic("abort");
	}

	ARR_APP1(char*, temp_files, name);
	*name_result = name;
	return out;
}

void init_temp_files(void)
{
	obstack_init(&file_obst);

	tempsubdir = NULL;
	temp_files = NEW_ARR_F(char*, 0);
	atexit(exit_temp_files);
}

void exit_temp_files(void)
{
	if (temp_files == NULL)
		return;

	size_t n_temp_files = ARR_LEN(temp_files);
	size_t i;
	for (i = 0; i < n_temp_files; ++i) {
		char *file = temp_files[i];
		unlink(file);
	}
	DEL_ARR_F(temp_files);
	temp_files = NULL;

	if (tempsubdir != NULL) {
		remove(tempsubdir);
		tempsubdir = NULL;
	}

	obstack_free(&file_obst, NULL);
}
