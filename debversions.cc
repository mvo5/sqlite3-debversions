/*
 * Written by Michael Vogt <michael.vogt@ubuntu.com>
 *
 * This code is licensed under the same terms as the "apt" package
 * which is GPLv2+.
 *
 * See /usr/share/common-licenses/GPL-2 on a debian system.
 */

#include <apt-pkg/debversion.h>

#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

extern "C"
{
   static
   int debversioncmp(void *handle,
                     int len_l, const void *v_lstr, 
                     int len_r, const void *v_rstr)
   {
      int res;
      const char *lstr = (const char*)v_lstr;
      const char *rstr = (const char*)v_rstr;
      const char *lstr_end = (const char*)lstr+len_l;
      const char *rstr_end = (const char*)rstr+len_r;

      res = debVS.DoCmpVersion(lstr, lstr_end,
                               rstr, rstr_end);
      return res;
   }

   int sqlite3_extension_init(sqlite3 *db, char **err, const sqlite3_api_routines *api)
   {
      SQLITE_EXTENSION_INIT2(api);
      sqlite3_create_collation(db, "debversion_compare", SQLITE_UTF8, NULL, 
                               debversioncmp);
      return 0;
   }
}
