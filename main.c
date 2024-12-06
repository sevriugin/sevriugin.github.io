#include <stdio.h>
#include "Field.h"

// Rust DCS decoder function
struct DecoderResult* decode_dcs(const char* input);

// Rust function for cleanup; defined as extern in Rust
void cleanup_elements(struct Field* elements, size_t len);

void cleanup_decoder_result(struct DecoderResult* result);

// Process elements
//  The order of `Element` in the array defined in the DCS JSON Schema
void process_elements(const struct Field* elements, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        switch (elements[i].data_type) {
            case String:
                // Example process...
                    printf("STRING: %s\n", elements[i].data.string);
            break;
            case Number:
                // Example processing...
                    printf("NUMBER: %u\n", elements[i].data.number);
            break;
            case TwoArrays: {
                // Process enabled
                printf("ENABLED: ");
                for (size_t j = 0; j < elements[i].data.enabled_disabled.enabled_len; ++j) {
                    printf("%hu ", elements[i].data.enabled_disabled.enabled[j]);
                }
                printf("\n");

                // Process disabled
                printf("DISABLED: ");
                for (size_t j = 0; j < elements[i].data.enabled_disabled.disabled_len; ++j) {
                    printf("%hu ", elements[i].data.enabled_disabled.disabled[j]);
                }
                printf("\n");
                break;
            }
            case None: {
                // Process NONE
                printf("NONE: Optional Value is missing in the result\n");
                break;
            }
            default:
                break;
        }
    }
}


int main(void) {
    const char* dcs_str = "CGHWv4UYba5-dZnABdKu__D6iWHsD6iWHsAAKn2J57YEACKUqIAEUpVAAAIixwAACIsY";

    // Prepare elements in Rust
    struct DecoderResult* result = decode_dcs(dcs_str);

    if (result->result_code != 0) {
        fprintf(stderr, "Failed to decode.\n");
        return 1;
    }

    const size_t len = result->len;

    printf("Number of elements: %zu\n", len);

    // Example: Here you could access and process each element
    process_elements(result->fields, len);
    cleanup_decoder_result(result);

    return 0;
}
