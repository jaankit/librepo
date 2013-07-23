/* librepo - A library providing (libcURL like) API to downloading repository
 * Copyright (C) 2012  Tomas Mlcoch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#ifndef LR_REPOMD_H
#define LR_REPOMD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <glib.h>
#include "xmlparser.h"
#include "types.h"

/** \defgroup repomd        Repomd parser
 *  \addtogroup repomd
 *  @{
 */

/** Yum repomd distro tag. */
typedef struct {
    char *cpeid;    /*!< Tag cpeid value or NULL. */
    char *tag;      /*!< Tag value. */
} lr_YumDistroTag;

/** Yum repomd record. */
typedef struct {
    char *type;                 /*!< Type of record (e.g. "primary") */
    char *location_href;        /*!< Location href attribute */
    char *location_base;        /*!< Location base attribute */
    char *checksum;             /*!< Checksum value */
    char *checksum_type;        /*!< Type of checksum */
    char *checksum_open;        /*!< Checksum of uncompressed file */
    char *checksum_open_type;   /*!< Type of checksum of uncompressed file */
    gint64 timestamp;           /*!< File timestamp */
    gint64 size;                /*!< File size */
    gint64 size_open;           /*!< Size of uncompressed file */
    int db_version;             /*!< Version of database */

    GStringChunk *chunk;        /*!< String chunk */
} lr_YumRepoMdRecord;

/** Yum repomd.xml. */
typedef struct {
    char *revision;         /*!< Revision string*/
    char *repoid;           /*!< RepoId */
    char *repoid_type;      /*!< RepoId type ("sha256", ...) */
    GSList *repo_tags;      /*!< List of strings */
    GSList *content_tags;   /*!< List of strings */
    GSList *distro_tags;    /*!< List of lr_YumDistroTag* */
    GSList *records;        /*!< List with lr_YumRepoMdRecords */

    GStringChunk *chunk;    /*!< String chunk for repomd strings
                                 (Note: lr_YumRepomdRecord strings are stored
                                 in lr_YumRepomdRecord->chunk) */
} lr_YumRepoMd;

/** Create new empty repomd object.
 * @return              New repomd object.
 */
lr_YumRepoMd *
lr_yum_repomd_init();

/** Free repomd content and repomd object itself.
 * @param repomd        Repomd object.
 */
void
lr_yum_repomd_free(lr_YumRepoMd *repomd);

/** Parse repomd.xml file.
 * @param repomd            Empty repomd object.
 * @param fd                File descriptor.
 * @param warningcb         Callback for warnings
 * @param warningcb_data    Warning callback user data
 * @param err               GError **
 * @return                  Librepo return code ::lr_Rc.
 */
int
lr_yum_repomd_parse_file(lr_YumRepoMd *repomd,
                         int fd,
                         lr_XmlParserWarningCb warningcb,
                         void *warningcb_data,
                         GError **err);

/** Get repomd record from the repomd object.
 * @param repomd        Repomd record.
 * @param type          Type of record e.g. "primary", "filelists", ...
 * @return              Record of desired type or NULL.
 */
lr_YumRepoMdRecord *
lr_yum_repomd_get_record(lr_YumRepoMd *repomd,
                         const char *type);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
