/*
 * Written by Alexey Tourbin <at@altlinux.org>.
 *
 * The author has dedicated the code to the public domain.  Anyone is free
 * to copy, modify, publish, use, compile, sell, or distribute the original
 * code, either in source code form or as a compiled binary, for any purpose,
 * commercial or non-commercial, and by any means.
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <apt-pkg/debversion.h>

#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

extern "C"
{
static
void debversioncmp(sqlite3_context *ctx, int argc, sqlite3_value **argv)
{
   int res;
   const char *lstr, *rstr;
 
   assert(argc == 2);

   lstr = (const char *) sqlite3_value_text(argv[0]);
   if (!lstr) {
      sqlite3_result_error(ctx, "no lstr", -1);
      return;
   }

    rstr = (const char *) sqlite3_value_text(argv[1]);
    if (!rstr) {
        sqlite3_result_error(ctx, "no rstr", -1);
        return;
    }

    res = debVS.CmpVersion(lstr, rstr);
    sqlite3_result_int(ctx, res);
    return;
}

int sqlite3_extension_init(sqlite3 *db, char **err, const sqlite3_api_routines *api)
{
	SQLITE_EXTENSION_INIT2(api)
	sqlite3_create_function(db, "debversion_cmp", 2, SQLITE_UTF8, NULL, debversioncmp, NULL, NULL);
	return 0;
}
}
