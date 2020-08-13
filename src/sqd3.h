#ifndef __SQD3_H__
#define __SQD3_H__

#include <sqd3/builtin_functions.h>
#include <sqd3/parser.h>
#include <sqd3/vtable.h>

#include "protocol.h"

void init_sqd3_context(void);
void execute_script(request_t *request, response_t *response);

#endif
