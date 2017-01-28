/* 
 * Copyright (C) 2001-2006 Bastien Nocera <hadess@hadess.net>
 *
 * encoding list copied from gnome-terminal/encoding.c
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * The Totem project hereby grant permission for non-gpl compatible GStreamer
 * plugins to be used and distributed together with GStreamer and Totem. This
 * permission are above and beyond the permissions granted by the GPL license
 * Totem is covered by.
 *
 * Monday 7th February 2005: Christian Schaller: Add exception clause.
 * See license_change file for details.
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib.h>

#include "parole-subtitle-encoding.h"

typedef enum
{
  SUBTITLE_ENCODING_CURRENT_LOCALE,

  SUBTITLE_ENCODING_ISO_8859_6,
  SUBTITLE_ENCODING_IBM_864,
  SUBTITLE_ENCODING_MAC_ARABIC,
  SUBTITLE_ENCODING_WINDOWS_1256,

  SUBTITLE_ENCODING_ARMSCII_8,

  SUBTITLE_ENCODING_ISO_8859_4,
  SUBTITLE_ENCODING_ISO_8859_13,
  SUBTITLE_ENCODING_WINDOWS_1257,

  SUBTITLE_ENCODING_ISO_8859_14,

  SUBTITLE_ENCODING_ISO_8859_2,
  SUBTITLE_ENCODING_IBM_852,
  SUBTITLE_ENCODING_MAC_CE,
  SUBTITLE_ENCODING_WINDOWS_1250,

  SUBTITLE_ENCODING_GB18030,
  SUBTITLE_ENCODING_GB2312,
  SUBTITLE_ENCODING_GBK,
  SUBTITLE_ENCODING_HZ,

  SUBTITLE_ENCODING_BIG5,
  SUBTITLE_ENCODING_BIG5_HKSCS,
  SUBTITLE_ENCODING_EUC_TW,

  SUBTITLE_ENCODING_MAC_CROATIAN,

  SUBTITLE_ENCODING_ISO_8859_5,
  SUBTITLE_ENCODING_IBM_855,
  SUBTITLE_ENCODING_ISO_IR_111,
  SUBTITLE_ENCODING_KOI8_R,
  SUBTITLE_ENCODING_MAC_CYRILLIC,
  SUBTITLE_ENCODING_WINDOWS_1251,

  SUBTITLE_ENCODING_CP_866,

  SUBTITLE_ENCODING_MAC_UKRAINIAN,
  SUBTITLE_ENCODING_KOI8_U,

  SUBTITLE_ENCODING_GEOSTD8,

  SUBTITLE_ENCODING_ISO_8859_7,
  SUBTITLE_ENCODING_MAC_GREEK,
  SUBTITLE_ENCODING_WINDOWS_1253,

  SUBTITLE_ENCODING_MAC_GUJARATI,

  SUBTITLE_ENCODING_MAC_GURMUKHI,

  SUBTITLE_ENCODING_ISO_8859_8_I,
  SUBTITLE_ENCODING_IBM_862,
  SUBTITLE_ENCODING_MAC_HEBREW,
  SUBTITLE_ENCODING_WINDOWS_1255,

  SUBTITLE_ENCODING_ISO_8859_8,

  SUBTITLE_ENCODING_MAC_DEVANAGARI,

  SUBTITLE_ENCODING_MAC_ICELANDIC,

  SUBTITLE_ENCODING_EUC_JP,
  SUBTITLE_ENCODING_ISO_2022_JP,
  SUBTITLE_ENCODING_SHIFT_JIS,

  SUBTITLE_ENCODING_EUC_KR,
  SUBTITLE_ENCODING_ISO_2022_KR,
  SUBTITLE_ENCODING_JOHAB,
  SUBTITLE_ENCODING_UHC,

  SUBTITLE_ENCODING_ISO_8859_10,

  SUBTITLE_ENCODING_MAC_FARSI,

  SUBTITLE_ENCODING_ISO_8859_16,
  SUBTITLE_ENCODING_MAC_ROMANIAN,

  SUBTITLE_ENCODING_ISO_8859_3,

  SUBTITLE_ENCODING_TIS_620,

  SUBTITLE_ENCODING_ISO_8859_9,
  SUBTITLE_ENCODING_IBM_857,
  SUBTITLE_ENCODING_MAC_TURKISH,
  SUBTITLE_ENCODING_WINDOWS_1254,

  SUBTITLE_ENCODING_UTF_7,
  SUBTITLE_ENCODING_UTF_8,
  SUBTITLE_ENCODING_UTF_16,
  SUBTITLE_ENCODING_UCS_2,
  SUBTITLE_ENCODING_UCS_4,

  SUBTITLE_ENCODING_ISO_8859_1,
  SUBTITLE_ENCODING_ISO_8859_15,
  SUBTITLE_ENCODING_IBM_850,
  SUBTITLE_ENCODING_MAC_ROMAN,
  SUBTITLE_ENCODING_WINDOWS_1252,

  SUBTITLE_ENCODING_TCVN,
  SUBTITLE_ENCODING_VISCII,
  SUBTITLE_ENCODING_WINDOWS_1258,

  SUBTITLE_ENCODING_LAST
} SubtitleEncodingIndex;


typedef struct
{
  int index;
  const char *charset;
  const char *name;
} SubtitleEncoding;


static SubtitleEncoding encodings[] = {

  {SUBTITLE_ENCODING_CURRENT_LOCALE,
      NULL, ("Current Locale")},

  {SUBTITLE_ENCODING_ISO_8859_6,
      "ISO-8859-6", ("Arabic")},
  {SUBTITLE_ENCODING_IBM_864,
      "IBM864", ("Arabic")},
  {SUBTITLE_ENCODING_MAC_ARABIC,
      "MAC_ARABIC", ("Arabic")},
  {SUBTITLE_ENCODING_WINDOWS_1256,
      "WINDOWS-1256", ("Arabic")},

  {SUBTITLE_ENCODING_ARMSCII_8,
      "ARMSCII-8", ("Armenian")},

  {SUBTITLE_ENCODING_ISO_8859_4,
      "ISO-8859-4", ("Baltic")},
  {SUBTITLE_ENCODING_ISO_8859_13,
      "ISO-8859-13", ("Baltic")},
  {SUBTITLE_ENCODING_WINDOWS_1257,
      "WINDOWS-1257", ("Baltic")},

  {SUBTITLE_ENCODING_ISO_8859_14,
      "ISO-8859-14", ("Celtic")},

  {SUBTITLE_ENCODING_ISO_8859_2,
      "ISO-8859-2", ("Central European")},
  {SUBTITLE_ENCODING_IBM_852,
      "IBM852", ("Central European")},
  {SUBTITLE_ENCODING_MAC_CE,
      "MAC_CE", ("Central European")},
  {SUBTITLE_ENCODING_WINDOWS_1250,
      "WINDOWS-1250", ("Central European")},

  {SUBTITLE_ENCODING_GB18030,
      "GB18030", ("Chinese Simplified")},
  {SUBTITLE_ENCODING_GB2312,
      "GB2312", ("Chinese Simplified")},
  {SUBTITLE_ENCODING_GBK,
      "GBK", ("Chinese Simplified")},
  {SUBTITLE_ENCODING_HZ,
      "HZ", ("Chinese Simplified")},

  {SUBTITLE_ENCODING_BIG5,
      "BIG5", ("Chinese Traditional")},
  {SUBTITLE_ENCODING_BIG5_HKSCS,
      "BIG5-HKSCS", ("Chinese Traditional")},
  {SUBTITLE_ENCODING_EUC_TW,
      "EUC-TW", ("Chinese Traditional")},

  {SUBTITLE_ENCODING_MAC_CROATIAN,
      "MAC_CROATIAN", ("Croatian")},

  {SUBTITLE_ENCODING_ISO_8859_5,
      "ISO-8859-5", ("Cyrillic")},
  {SUBTITLE_ENCODING_IBM_855,
      "IBM855", ("Cyrillic")},
  {SUBTITLE_ENCODING_ISO_IR_111,
      "ISO-IR-111", ("Cyrillic")},
  {SUBTITLE_ENCODING_KOI8_R,
      "KOI8-R", ("Cyrillic")},
  {SUBTITLE_ENCODING_MAC_CYRILLIC,
      "MAC-CYRILLIC", ("Cyrillic")},
  {SUBTITLE_ENCODING_WINDOWS_1251,
      "WINDOWS-1251", ("Cyrillic")},

  {SUBTITLE_ENCODING_CP_866,
      "CP866", ("Cyrillic/Russian")},

  {SUBTITLE_ENCODING_MAC_UKRAINIAN,
      "MAC_UKRAINIAN", ("Cyrillic/Ukrainian")},
  {SUBTITLE_ENCODING_KOI8_U,
      "KOI8-U", ("Cyrillic/Ukrainian")},

  {SUBTITLE_ENCODING_GEOSTD8,
      "GEORGIAN-PS", ("Georgian")},

  {SUBTITLE_ENCODING_ISO_8859_7,
      "ISO-8859-7", ("Greek")},
  {SUBTITLE_ENCODING_MAC_GREEK,
      "MAC_GREEK", ("Greek")},
  {SUBTITLE_ENCODING_WINDOWS_1253,
      "WINDOWS-1253", ("Greek")},

  {SUBTITLE_ENCODING_MAC_GUJARATI,
      "MAC_GUJARATI", ("Gujarati")},

  {SUBTITLE_ENCODING_MAC_GURMUKHI,
      "MAC_GURMUKHI", ("Gurmukhi")},

  {SUBTITLE_ENCODING_ISO_8859_8_I,
      "ISO-8859-8-I", ("Hebrew")},
  {SUBTITLE_ENCODING_IBM_862,
      "IBM862", ("Hebrew")},
  {SUBTITLE_ENCODING_MAC_HEBREW,
      "MAC_HEBREW", ("Hebrew")},
  {SUBTITLE_ENCODING_WINDOWS_1255,
      "WINDOWS-1255", ("Hebrew")},

  {SUBTITLE_ENCODING_ISO_8859_8,
      "ISO-8859-8", ("Hebrew Visual")},

  {SUBTITLE_ENCODING_MAC_DEVANAGARI,
      "MAC_DEVANAGARI", ("Hindi")},

  {SUBTITLE_ENCODING_MAC_ICELANDIC,
      "MAC_ICELANDIC", ("Icelandic")},

  {SUBTITLE_ENCODING_EUC_JP,
      "EUC-JP", ("Japanese")},
  {SUBTITLE_ENCODING_ISO_2022_JP,
      "ISO2022JP", ("Japanese")},
  {SUBTITLE_ENCODING_SHIFT_JIS,
      "SHIFT-JIS", ("Japanese")},

  {SUBTITLE_ENCODING_EUC_KR,
      "EUC-KR", ("Korean")},
  {SUBTITLE_ENCODING_ISO_2022_KR,
      "ISO2022KR", ("Korean")},
  {SUBTITLE_ENCODING_JOHAB,
      "JOHAB", ("Korean")},
  {SUBTITLE_ENCODING_UHC,
      "UHC", ("Korean")},

  {SUBTITLE_ENCODING_ISO_8859_10,
      "ISO-8859-10", ("Nordic")},

  {SUBTITLE_ENCODING_MAC_FARSI,
      "MAC_FARSI", ("Persian")},

  {SUBTITLE_ENCODING_ISO_8859_16,
      "ISO-8859-16", ("Romanian")},
  {SUBTITLE_ENCODING_MAC_ROMANIAN,
      "MAC_ROMANIAN", ("Romanian")},

  {SUBTITLE_ENCODING_ISO_8859_3,
      "ISO-8859-3", ("South European")},

  {SUBTITLE_ENCODING_TIS_620,
      "TIS-620", ("Thai")},

  {SUBTITLE_ENCODING_ISO_8859_9,
      "ISO-8859-9", ("Turkish")},
  {SUBTITLE_ENCODING_IBM_857,
      "IBM857", ("Turkish")},
  {SUBTITLE_ENCODING_MAC_TURKISH,
      "MAC_TURKISH", ("Turkish")},
  {SUBTITLE_ENCODING_WINDOWS_1254,
      "WINDOWS-1254", ("Turkish")},

  {SUBTITLE_ENCODING_UTF_7,
      "UTF-7", ("Unicode")},
  {SUBTITLE_ENCODING_UTF_8,
      "UTF-8", ("Unicode")},
  {SUBTITLE_ENCODING_UTF_16,
      "UTF-16", ("Unicode")},
  {SUBTITLE_ENCODING_UCS_2,
      "UCS-2", ("Unicode")},
  {SUBTITLE_ENCODING_UCS_4,
      "UCS-4", ("Unicode")},

  {SUBTITLE_ENCODING_ISO_8859_1,
      "ISO-8859-1", ("Western")},
  {SUBTITLE_ENCODING_ISO_8859_15,
      "ISO-8859-15", ("Western")},
  {SUBTITLE_ENCODING_IBM_850,
      "IBM850", ("Western")},
  {SUBTITLE_ENCODING_MAC_ROMAN,
      "MAC_ROMAN", ("Western")},
  {SUBTITLE_ENCODING_WINDOWS_1252,
      "WINDOWS-1252", ("Western")},

  {SUBTITLE_ENCODING_TCVN,
      "TCVN", ("Vietnamese")},
  {SUBTITLE_ENCODING_VISCII,
      "VISCII", ("Vietnamese")},
  {SUBTITLE_ENCODING_WINDOWS_1258,
      "WINDOWS-1258", ("Vietnamese")}
};

static const SubtitleEncoding *
find_encoding_by_charset (const char *charset)
{
  int i;

  i = 1;                        /* skip current locale */
  while (i < SUBTITLE_ENCODING_LAST) {
    if (strcasecmp (charset, encodings[i].charset) == 0)
      return &encodings[i];

    ++i;
  }

  if (strcasecmp (charset,
          encodings[SUBTITLE_ENCODING_CURRENT_LOCALE].charset) == 0)
    return &encodings[SUBTITLE_ENCODING_CURRENT_LOCALE];

  return NULL;
}

static void
subtitle_encoding_init (void)
{
  guint i;

  g_get_charset ((const char **)
      &encodings[SUBTITLE_ENCODING_CURRENT_LOCALE].charset);

  g_assert (G_N_ELEMENTS (encodings) == SUBTITLE_ENCODING_LAST);

  for (i = 0; i < SUBTITLE_ENCODING_LAST; i++) {
    /* Translate the names */
    encodings[i].name = (encodings[i].name);
  }
}

static int
subtitle_encoding_get_index (const char *charset)
{
  const SubtitleEncoding *e;

  e = find_encoding_by_charset (charset);
  if (e != NULL)
    return e->index;
  else
    return SUBTITLE_ENCODING_CURRENT_LOCALE;
}

static const char *
subtitle_encoding_get_charset (int index_i)
{
  const SubtitleEncoding *e;

  if (index_i >= SUBTITLE_ENCODING_LAST)
    e = &encodings[SUBTITLE_ENCODING_CURRENT_LOCALE];
  else if (index_i < SUBTITLE_ENCODING_CURRENT_LOCALE)
    e = &encodings[SUBTITLE_ENCODING_CURRENT_LOCALE];
  else
    e = &encodings[index_i];
  return e->charset;
}

enum
{
  INDEX_COL,
  NAME_COL
};

static gint
compare (GtkTreeModel * model, GtkTreeIter * a, GtkTreeIter * b, gpointer data)
{
  gchar *str_a, *str_b;
  gint result;

  gtk_tree_model_get (model, a, NAME_COL, &str_a, -1);
  gtk_tree_model_get (model, b, NAME_COL, &str_b, -1);

  result = strcmp (str_a, str_b);

  g_free (str_a);
  g_free (str_b);

  return result;
}

static void
is_encoding_sensitive (GtkCellLayout * cell_layout,
    GtkCellRenderer * cell,
    GtkTreeModel * tree_model, GtkTreeIter * iter, gpointer data)
{

  gboolean sensitive;

  sensitive = !gtk_tree_model_iter_has_child (tree_model, iter);
  g_object_set (cell, "sensitive", sensitive, NULL);
}

static GtkTreeModel *
subtitle_encoding_create_store (void)
{
  gchar *label;
  gchar *lastlang = "";
  GtkTreeIter iter, iter2;
  GtkTreeStore *store;
  int i;

  store = gtk_tree_store_new (2, G_TYPE_INT, G_TYPE_STRING);

  for (i = 0; i < SUBTITLE_ENCODING_LAST; i++) {
    if (strcmp (lastlang, encodings[i].name)) {
      lastlang = g_strdup(encodings[i].name);
      gtk_tree_store_append (store, &iter, NULL);
      gtk_tree_store_set (store, &iter, INDEX_COL,
          -1, NAME_COL, lastlang, -1);
    }
    label = g_strdup_printf("%s (%s)", lastlang, encodings[i].charset);
    gtk_tree_store_append (store, &iter2, &iter);
    gtk_tree_store_set (store, &iter2, INDEX_COL,
        encodings[i].index, NAME_COL, label, -1);
    g_free(label);
  }
  gtk_tree_sortable_set_default_sort_func (GTK_TREE_SORTABLE (store),
      compare, NULL, NULL);
  gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (store),
      NAME_COL, GTK_SORT_ASCENDING);
  return GTK_TREE_MODEL (store);
}

static void
subtitle_encoding_combo_render (GtkComboBox * combo)
{
  GtkCellRenderer *renderer;

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, TRUE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer,
      "text", NAME_COL, NULL);
  gtk_cell_layout_set_cell_data_func (GTK_CELL_LAYOUT (combo),
      renderer, is_encoding_sensitive, NULL, NULL);
}

const char *
parole_subtitle_encoding_get_selected (GtkComboBox * combo)
{
  GtkTreeModel *model;
  GtkTreeIter iter;
  gint index_i = -1;

  model = gtk_combo_box_get_model (combo);
  if (gtk_combo_box_get_active_iter (combo, &iter)) {
    gtk_tree_model_get (model, &iter, INDEX_COL, &index_i, -1);
  }
  if (index_i == -1)
    return NULL;
    
  return subtitle_encoding_get_charset (index_i);
}

void
parole_subtitle_encoding_set (GtkComboBox * combo, const char *encoding)
{
  GtkTreeModel *model;
  GtkTreeIter iter, iter2;
  gint index_i, i;

  g_return_if_fail (encoding != NULL);

  model = gtk_combo_box_get_model (combo);
  index_i = subtitle_encoding_get_index (encoding);
  
  if (gtk_tree_model_get_iter_first (model, &iter))
  {
  
      do {
        if (!gtk_tree_model_iter_has_child (model, &iter))
          continue;
        if (!gtk_tree_model_iter_children (model, &iter2, &iter))
          continue;
        do {
          gtk_tree_model_get (model, &iter2, INDEX_COL, &i, -1);
          if (i == index_i)
            break;
        } while (gtk_tree_model_iter_next (model, &iter2));
        if (i == index_i)
          break;
      } while (gtk_tree_model_iter_next (model, &iter));
      gtk_combo_box_set_active_iter (combo, &iter2);
  }
}

void
parole_subtitle_encoding_init (GtkComboBox *combo)
{
  GtkTreeModel *model;
  subtitle_encoding_init ();
  model = subtitle_encoding_create_store ();
  gtk_combo_box_set_model (combo, model);
  g_object_unref (model);
  subtitle_encoding_combo_render (combo);
}

/*
 * vim: sw=2 ts=8 cindent noai bs=2
 */
