#pragma once

typedef enum {
    INT, STRING, CHAR, BOOL, DOUBLE,

    LEFT_PAREN, RIGHT_PAREN, VALUE,

    TRUE, FALSE, LITERAL,

    ADD_COLUMN, ADD_ROW, GET_ELEMENT,

    END_OF_TEXT,
} TokenType;