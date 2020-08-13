#include "sqd3.h"

void init_sqd3_context(void) { init_vtable(); }

void execute_script(request_t *request, response_t *response) {

  SQD3_OBJECT *print_ref = build_builtin_function_ref("print", &print_function);
  declare_local_variable("print", print_ref);

  char filename[256];

  sprintf(filename, "routes/%s.sqd3", request->path);
  if (access(filename, F_OK) != -1) {

    FILE *buffer = fopen(filename, "r");
    init_lexer(buffer);
    stmt_list();
    fclose(buffer);

    VTABLE_ENTRY *body = recover_variable("body");

    long long content = read_integer_from_object(body->ref);
    response->body = malloc(100);
    sprintf(response->body, "%lld", content);
    response->status = 200;
  } else {
    response->status = 404;
  }

  dispose_local_variables();
}
