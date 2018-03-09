#include <font.h>
#include <graphics.h>
#include <stdarg.h>

namespace Graphics::Terminal
{

static u32 cursor_x = 0;
static u32 cursor_y = 0;

static u32 color = 0xffffff;
/*
%d or %i: signed decimal integer
%x: lower case hex
%X: upper case hex
%e: lower case notation
%E: upper case notation
%b: binary
%s: string
%%: print %
*/

// note:
/*
lower to upper
    (letter - 'a') * ('Z' - 'A') / ('z' - 'a') + 'A'

*/
//most primitive printf function NDY
void printf(char *str, ...)
{
  va_list vl;
  u16 arg_num = 0;
  i64 unsafe_i64 = 0;
  u64 unsafe_u64 = 0;
  
  // hex words
  const char *hex_list = "0123456789abcdef\0";
  // count '%'
  char *temp = str;
  while (*temp != '\0')
  {
    if (*temp == '%')
    {
      arg_num++;
    }
    temp++;
  }
  // if at least one '%' found
  if (arg_num != 0)
  {
    va_start(vl, arg_num);
  }
  // loop
  while (*str != '\0')
  {
    // arguments
    if (*str == '%' && arg_num > 0)
    {
      char buff[255];
      u8 buff_index = 0;
      switch (*(str + 1))
      {
      /*  NOTE
      see what next to the current '%'
      we dont know the actual number of pushed in the stack
      so this is not safe at all, by default we assume it is a 64 bit
      integer
      */
      //as signed integer
      case 'd':
      case 'i': //same shit
      {
        unsafe_i64 = va_arg(vl, i64);
        //print a '-' sign if the integer is smaller than 0
        if(unsafe_i64 < 0){
          put_char('-', color);
        }

        // Workflow:
        // me: Ayy! unsafe_i64!
        // unsafe_i64: I feel depressed, you know...just like I am so negetive than everyone was.
        // me: You should go out and date some -1 numbers!
        unsafe_i64 = unsafe_i64 < 0 ? unsafe_i64 * -1 : unsafe_i64;
        while (unsafe_i64 > 0)
        {
          buff[buff_index++] = '0' + unsafe_i64 % 10;
          unsafe_i64 /= 10; // divide by 10
        }
        break;
      }
      // as Lower hex string
      case 'x':{
      // treat pushed bytes as unsigned integer
        unsafe_u64 = va_arg(vl, u64);
        while (unsafe_u64 > 0)
        {
          buff[buff_index++] = hex_list[unsafe_u64 % 16];
          unsafe_u64 /= 16; // divide by 16
        }
        break;
      }
      // as Upper hex string
      case 'X':{
        unsafe_u64 = va_arg(vl, u64);
        while (unsafe_u64 > 0)
        {
          char mapped_char = hex_list[unsafe_u64 % 16];
          // convert lower char to upper
          if(unsafe_u64 % 16 >= 0xa){
            mapped_char = (mapped_char - 'a') * ('Z' - 'A') / ('z' - 'a') + 'A';
          }
          buff[buff_index++] = mapped_char;
          unsafe_u64 /= 16; // divide by 16
        }
        break;
      }
      // as binary
      case 'b':{
        unsafe_u64 = va_arg(vl, u64);
        while (unsafe_u64 != 0)
        {
          if(unsafe_u64 & 1){
            buff[buff_index++] = '1';
          }else{
            buff[buff_index++] = '0';
          }
          unsafe_u64 >>= 1; // divide by 2
        }
        break;
      }
      //as char*
      case 's':{
        char *ptr = (char *)va_arg(vl, u64);
        if(ptr == null) return;

        while(*ptr != '\0'){
          put_char(*ptr, color);
          ptr++;
        }
        break;
      }
      default:
        put_char('%', color);
        break;
      }
      // print querried chars
      if(buff_index != 0){

        for(i16 i = --buff_index; i > -1; i--){
          put_char(buff[i], color);
        }
      }
      // decrease counter
      arg_num--;
      str++; //pass to next char
    }
    else //if not '%'
    {
      put_char(*str, color);
    }
    str++;
  }
}

void put_char(char letter, u32 color)
{
  // if there are no space for extra letter in current line
  if ((cursor_x + 1) * FONT_WIDTH > Graphics::get_width())
  {
    // if no space for new line
    if ((cursor_y + 1) * FONT_HEIGHT > Graphics::get_height())
  {
    set_pos(0, 0);
  }else{
    set_pos(0, cursor_y + 1);
  }
  }
  u8 index = 0;
  // Is number
  if ((u8)letter > '0' - 1 && (u8)letter < '9' + 1)
  {
    index = (letter - '0') + FONT_NUMBER_START;
  }
  else // Is capital letter
      if ((u8)letter > 'A' - 1 && (u8)letter < 'Z' + 1)
  {
    index = (letter - 'A') + FONT_CAPITAL_START;
  }
  else // Is lower letter
      if ((u8)letter > 'a' - 1 && (u8)letter < 'z' + 1)
  {
    index = (letter - 'a') + FONT_LOWER_START;
  }
  // symbol
  else
  {
    switch (letter)
    {
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
    case '\n':
      set_pos(0, cursor_y + 1);
      return;
      break;
    case ' ':
      set_pos(cursor_x + 1, cursor_y);
      return;
      break;
    }
  }
  for (u32 y = 0; y < FONT_HEIGHT; y++)
  {
    for (u32 x = 0; x < FONT_WIDTH; x++)
    {
      if ((font_data[index][y] & 1 << x) > 0)
      {
        Graphics::plot(cursor_x * FONT_WIDTH + x, cursor_y * FONT_HEIGHT + y,
                       color);
      }
    }
  }
  set_pos(cursor_x + 1, cursor_y);
}

void set_pos(u32 x, u32 y)
{
  if (x * FONT_WIDTH > Graphics::get_width())
  {
    return;
  }
  if (y * FONT_HEIGHT > Graphics::get_height())
  {
    return;
  }
  cursor_x = x;
  cursor_y = y;
}

void set_color(u32 c) { color = c; }

} // namespace Graphics::Terminal