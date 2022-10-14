#ifndef D000424B_64A5_449A_BB64_37EE58E7F6F5
#define D000424B_64A5_449A_BB64_37EE58E7F6F5

/*
A list of functions and structures used for decoding JSON files. Note that none
of them have actually been implemented yet so I would avoid using them whenever
possible. Most of them should be self explanatory.
*/

#include <stddef.h>
#include <stdint.h>

#include <json/json.h>

struct json_object json_parse_object_from_tokens(const char **tokens, uint32_t token_count,
                                     uint8_t *status);

struct json_array json_parse_array_from_tokens(const char **tokens, uint32_t token_count,
                                   uint8_t *status);

void json_free_object(struct json_object *object);

#endif /* D000424B_64A5_449A_BB64_37EE58E7F6F5 */
