/*
 * Copyright(c) 2006 to 2018 ADLINK Technology Limited and others
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License v. 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0, or the Eclipse Distribution License
 * v. 1.0 which is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * SPDX-License-Identifier: EPL-2.0 OR BSD-3-Clause
 */
#include <stdlib.h>

#include "CUnit/Theory.h"
#include "dds/ddsrt/environ.h"
#include "dds/ddsrt/misc.h"

CU_TheoryDataPoints(ddsrt_environ, bad_name) = {
  CU_DataPoints(const char *, "", "foo=")
};

CU_Theory((const char *name), ddsrt_environ, bad_name)
{
  dds_retcode_t rc;
  static const char value[] = "bar";
  static char dummy[] = "foobar";
  char *ptr;

  rc = ddsrt_setenv(name, value);
  CU_ASSERT_EQUAL(rc, DDS_RETCODE_BAD_PARAMETER);
  rc = ddsrt_unsetenv(name);
  CU_ASSERT_EQUAL(rc, DDS_RETCODE_BAD_PARAMETER);
  ptr = dummy;
  rc = ddsrt_getenv(name, &ptr);
  CU_ASSERT_EQUAL(rc, DDS_RETCODE_BAD_PARAMETER);
  CU_ASSERT_PTR_EQUAL(ptr, dummy);
}

DDSRT_WARNING_MSVC_OFF(4996)
CU_Test(ddsrt_environ, setenv)
{
  dds_retcode_t rc;
  static const char name[] = "foo";
  static char value[] = "bar";
  char *ptr;

  rc = ddsrt_setenv(name, value);
  CU_ASSERT_EQUAL(rc, DDS_RETCODE_OK);
  ptr = getenv(name);
  CU_ASSERT_PTR_NOT_NULL(ptr);
  CU_ASSERT_STRING_EQUAL(ptr, "bar");
  /* Ensure value is copied into the environment. */
  value[2] = 'z';
  ptr = getenv(name);
  CU_ASSERT_PTR_NOT_NULL(ptr);
  CU_ASSERT_STRING_EQUAL(ptr, "bar");
  rc = ddsrt_setenv(name, "");
  CU_ASSERT_EQUAL(rc, DDS_RETCODE_OK);
  ptr = getenv(name);
  CU_ASSERT_PTR_NULL(ptr);
}
DDSRT_WARNING_MSVC_ON(4996)

CU_Test(ddsrt_environ, getenv)
{
  dds_retcode_t rc;
  static const char name[] = "foo";
  static const char value[] = "bar";
  static char dummy[] = "foobar";
  char *ptr;

  /* Ensure "not found" is returned. */
  rc = ddsrt_unsetenv(name);
  CU_ASSERT_EQUAL_FATAL(rc, DDS_RETCODE_OK);

  ptr = dummy;
  rc = ddsrt_getenv(name, &ptr);
  CU_ASSERT_EQUAL(rc, DDS_RETCODE_NOT_FOUND);
  CU_ASSERT_PTR_EQUAL(ptr, dummy);

  /* Ensure "ok" is returned and value is what it should be. */
  rc = ddsrt_setenv(name, value);
  CU_ASSERT_EQUAL_FATAL(rc, DDS_RETCODE_OK);

  ptr = dummy;
  rc = ddsrt_getenv(name, &ptr);
  CU_ASSERT_EQUAL(rc, DDS_RETCODE_OK);
  CU_ASSERT_PTR_NOT_EQUAL(ptr, dummy);
  CU_ASSERT_PTR_NOT_EQUAL(ptr, NULL);
  if (ptr != NULL) {
    CU_ASSERT_STRING_EQUAL(ptr, "bar");
  }

  /* Ensure environement is as it was. */
  rc = ddsrt_unsetenv(name);
  CU_ASSERT_EQUAL(rc, DDS_RETCODE_OK);
}

