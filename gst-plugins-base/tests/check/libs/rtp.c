/* GStreamer unit tests for the RTP support library
 *
 * Copyright (C) 2007 Tim-Philipp Müller <tim centricular net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/check/gstcheck.h>

#include <gst/rtp/gstrtpbuffer.h>
#include <string.h>

#define RTP_HEADER_LEN 12

GST_START_TEST (test_rtp_buffer)
{
  GstBuffer *buf;
  guint8 *data;

  /* check GstRTPHeader structure alignment and packing */
  buf = gst_rtp_buffer_new_allocate (16, 4, 0);
  fail_unless (buf != NULL);
  fail_unless_equals_int (GST_BUFFER_SIZE (buf), RTP_HEADER_LEN + 16 + 4);
  data = GST_BUFFER_DATA (buf);

  /* check version in bitfield */
  gst_rtp_buffer_set_version (buf, 3);
  fail_unless_equals_int (gst_rtp_buffer_get_version (buf), 3);
  fail_unless_equals_int ((data[0] & 0xC0) >> 6, 3);
  gst_rtp_buffer_set_version (buf, 0);
  fail_unless_equals_int (gst_rtp_buffer_get_version (buf), 0);
  fail_unless_equals_int ((data[0] & 0xC0) >> 6, 0);

  /* check sequence offset */
  gst_rtp_buffer_set_seq (buf, 0xF2C9);
  fail_unless_equals_int (gst_rtp_buffer_get_seq (buf), 0xF2C9);
  fail_unless_equals_int (GST_READ_UINT16_BE (data + 2), 0xF2C9);
  gst_rtp_buffer_set_seq (buf, 0);
  fail_unless_equals_int (gst_rtp_buffer_get_seq (buf), 0);
  fail_unless_equals_int (GST_READ_UINT16_BE (data + 2), 0);

  /* check timestamp offset */
  gst_rtp_buffer_set_timestamp (buf, 432191);
  fail_unless_equals_int (GST_READ_UINT32_BE (data + 4), 432191);
  fail_unless_equals_int (gst_rtp_buffer_get_timestamp (buf), 432191);
  gst_rtp_buffer_set_timestamp (buf, 0);
  fail_unless_equals_int (gst_rtp_buffer_get_timestamp (buf), 0);
  fail_unless_equals_int (GST_READ_UINT32_BE (data + 4), 0);

  /* check ssrc offset */
  gst_rtp_buffer_set_ssrc (buf, 0xf04043C2);
  fail_unless_equals_int (gst_rtp_buffer_get_ssrc (buf), (gint) 0xf04043c2);
  fail_unless_equals_int (GST_READ_UINT32_BE (data + 4 + 4), (gint) 0xf04043c2);
  gst_rtp_buffer_set_ssrc (buf, 0);
  fail_unless_equals_int (gst_rtp_buffer_get_ssrc (buf), 0);
  fail_unless_equals_int (GST_READ_UINT32_BE (data + 4 + 4), 0);

  /* check csrc bits */
  fail_unless_equals_int (gst_rtp_buffer_get_csrc_count (buf), 0);
  ASSERT_CRITICAL (gst_rtp_buffer_get_csrc (buf, 0));
  fail_unless_equals_int (data[0] & 0xf, 0);
  gst_buffer_unref (buf);

  /* and again, this time with CSRCs */
  buf = gst_rtp_buffer_new_allocate (16, 4, 3);
  fail_unless (buf != NULL);
  fail_unless_equals_int (GST_BUFFER_SIZE (buf),
      RTP_HEADER_LEN + 16 + 4 + 4 * 3);

  data = GST_BUFFER_DATA (buf);

  fail_unless_equals_int (gst_rtp_buffer_get_csrc_count (buf), 3);
  ASSERT_CRITICAL (gst_rtp_buffer_get_csrc (buf, 3));
  fail_unless_equals_int (data[0] & 0xf, 3);
  fail_unless_equals_int (gst_rtp_buffer_get_csrc (buf, 0), 0);
  fail_unless_equals_int (gst_rtp_buffer_get_csrc (buf, 1), 0);
  fail_unless_equals_int (gst_rtp_buffer_get_csrc (buf, 2), 0);

  data += RTP_HEADER_LEN;       /* skip the other header stuff */
  gst_rtp_buffer_set_csrc (buf, 0, 0xf7c0);
  fail_unless_equals_int (GST_READ_UINT32_BE (data + 0 * 4), 0xf7c0);
  gst_rtp_buffer_set_csrc (buf, 1, 0xf7c1);
  fail_unless_equals_int (GST_READ_UINT32_BE (data + 1 * 4), 0xf7c1);
  gst_rtp_buffer_set_csrc (buf, 2, 0xf7c2);
  fail_unless_equals_int (GST_READ_UINT32_BE (data + 2 * 4), 0xf7c2);
  ASSERT_CRITICAL (gst_rtp_buffer_set_csrc (buf, 3, 0xf123));
  gst_buffer_unref (buf);
}

GST_END_TEST;

static Suite *
rtp_suite (void)
{
  Suite *s = suite_create ("rtp support library");
  TCase *tc_chain = tcase_create ("general");

  suite_add_tcase (s, tc_chain);
  tcase_add_test (tc_chain, test_rtp_buffer);
  return s;
}

int
main (int argc, char **argv)
{
  int nf;

  Suite *s = rtp_suite ();
  SRunner *sr = srunner_create (s);

  gst_check_init (&argc, &argv);

  srunner_run_all (sr, CK_NORMAL);
  nf = srunner_ntests_failed (sr);
  srunner_free (sr);

  return nf;
}
