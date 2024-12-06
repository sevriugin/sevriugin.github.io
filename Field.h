//
// Created by Sergey Sevriugin on 04/12/24.
//
// element.h

#pragma once
#include <stdint.h>

enum DataType {
    String,
    Number,
    TwoArrays,
    None
};

// Define EnabledDisabled struct  (This is crucial for alignment)
struct EnabledDisabled {
    uint32_t enabled_len;
    uint16_t* enabled;
    uint32_t disabled_len;
    uint16_t* disabled;
} EnabledDisabled;

union Data {
    const char* string;
    uint32_t number;
    struct EnabledDisabled enabled_disabled;
};

struct Field {
    enum DataType data_type;
    union Data data;
};

struct DecoderResult {
    uint16_t result_code;
    uint32_t len;
    struct Field *fields;
    const char* error;
};
