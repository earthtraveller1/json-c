#ifndef D000424B_64A5_449A_BB64_37EE58E7F6F5
#define D000424B_64A5_449A_BB64_37EE58E7F6F5

// Internal JSON parsing utilities.

#include <stddef.h>
#include <stdint.h>

#include <json/json.h>

struct json_object json_parse_object_from_tokens(const char **tokens, uint32_t token_count,
                                     uint8_t *status);

struct json_array json_parse_array_from_tokens(const char **tokens, uint32_t token_count,
                                   uint8_t *status);

#endif /* D000424B_64A5_449A_BB64_37EE58E7F6F5 */
