#include "../src/protocol.h"
#include <check.h>
#include <stdio.h>

#define REQUEST_MAX_SIZE 1024

START_TEST(test_get_without_params) {
  char input[] = "GET /path HTTP/1.0\n\n";

  FILE *buffer = fmemopen(input, strlen(input), "r");
  request_t *http_request = parse(buffer);

  ck_assert_int_eq(GET, http_request->method);
  ck_assert_str_eq("/path", http_request->path);
  ck_assert_str_eq("HTTP/1.0", http_request->protocol_version);

  free(http_request);
  fclose(buffer);
}
END_TEST

START_TEST(test_post_without_params) {
  char input[] = "POST /path HTTP/1.1\n\n";

  FILE *buffer = fmemopen(input, strlen(input), "r");
  request_t *http_request = parse(buffer);

  ck_assert_int_eq(NOT_IMPLEMENTED, http_request->method);
  ck_assert_str_eq("/path", http_request->path);
  ck_assert_str_eq("HTTP/1.1", http_request->protocol_version);

  fclose(buffer);
}
END_TEST

Suite *lexer_suite(void) {
  Suite *suite;
  TCase *tc_get;
  TCase *tc_post;

  suite = suite_create("Protocol");
  tc_get = tcase_create("GET");
  tc_post = tcase_create("POST");

  tcase_add_test(tc_get, test_get_without_params);
  tcase_add_test(tc_post, test_post_without_params);

  suite_add_tcase(suite, tc_get);
  suite_add_tcase(suite, tc_post);

  return suite;
}

int main() {
  int number_failed;
  Suite *suite;
  SRunner *suite_runner;

  suite = lexer_suite();
  suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return number_failed;
}
