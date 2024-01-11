#pragma once

typedef enum {
    INT, STRING, CHAR, BOOL, DOUBLE,

    LEFT_PAREN, RIGHT_PAREN, VALUE,

    TRUE, FALSE,

    ADD_COLUMN, ADD_ROW,

    END_OF_TEXT,
} TokenType;