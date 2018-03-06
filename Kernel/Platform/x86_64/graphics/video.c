#include <graphics.h>
#include <font.h>

void put_char(char letter, u32 color) {
    u8 index = 0;

    if (!is_char(letter)) {
        return;
    }

    if (is_num(letter)) {
        //is number
        index = (letter - '0') + FONT_NUMBER_START;
    } else if (is_capital(letter)) {
        // is capital letter
        index = (letter - 'A') + FONT_CAPITAL_START;
    } else if (is_low(letter)) {
        // is lower letter
        index = (letter - 'a') + FONT_LOWER_START;
    } else {
        // symbol
        switch (letter) {
        case '\'':
            index = FONT_SYMBOL_START;
            break;
        case '*':
            index = FONT_SYMBOL_START + 1;
            break;
        case '@':
            index = FONT_SYMBOL_START + 2;
            break;
        case '\\':
            index = FONT_SYMBOL_START + 3;
            break;
        case '>':
            index = FONT_SYMBOL_START + 4;
            break;
        case '^':
            index = FONT_SYMBOL_START + 5;
            break;
        case ':':
            index = FONT_SYMBOL_START + 6;
            break;
        case ',':
            index = FONT_SYMBOL_START + 7;
            break;
        case '$':
            index = FONT_SYMBOL_START + 8;
            break;
        case '=':
            index = FONT_SYMBOL_START + 9;
            break;
        case '!':
            index = FONT_SYMBOL_START + 10;
            break;
        case '#':
            index = FONT_SYMBOL_START + 11;
            break;
        case '{':
            index = FONT_SYMBOL_START + 12;
            break;
        case '[':
            index = FONT_SYMBOL_START + 13;
            break;
        case '(':
            index = FONT_SYMBOL_START + 14;
            break;
        case '<':
            index = FONT_SYMBOL_START + 15;
            break;
        case '-':
            index = FONT_SYMBOL_START + 16;
            break;
        case '&':
            index = FONT_SYMBOL_START + 17;
            break;
        case '|':
            index = FONT_SYMBOL_START + 18;
            break;
        case '%':
            index = FONT_SYMBOL_START + 19;
            break;
        case '.':
            index = FONT_SYMBOL_START + 20;
            break;
        case '+':
            index = FONT_SYMBOL_START + 21;
            break;
        case '?':
            index = FONT_SYMBOL_START + 22;
            break;
        case '"':
            index = FONT_SYMBOL_START + 23;
            break;
        case '}':
            index = FONT_SYMBOL_START + 24;
            break;
        case ']':
            index = FONT_SYMBOL_START + 25;
            break;
        case ')':
            index = FONT_SYMBOL_START + 26;
            break;
        case ';':
            index = FONT_SYMBOL_START + 27;
            break;
        case '/':
            index = FONT_SYMBOL_START + 28;
            break;
        case '~':
            index = FONT_SYMBOL_START + 29;
            break;
        case '_':
            index = FONT_SYMBOL_START + 30;
            break;
        default:
            break;
        }
    }
    for (u32 y = 0; y < 24; y++){
        for (u32 x = 0; x < 16; x++) {
            if((font_data[0][y] & 1 << x) > 0){
              plot(x, y, color);
            }
        }
    }
}

bool is_char(char letter) {
    return is_num(letter) || is_capital(letter) || is_low(letter);
}

bool is_num(char letter) {
    if ((u8)letter > 47 && (u8)letter < 58) {
        return true;
    }
    return false;
}

bool is_capital(char letter) {
    if ((u8)letter > 64 && (u8)letter < 91) {
        return true;
    }
    return false;
}

bool is_low(char letter) {
    if ((u8)letter >= 96 && (u8)letter <= 123) {
        return true;
    }
    return false;
}
