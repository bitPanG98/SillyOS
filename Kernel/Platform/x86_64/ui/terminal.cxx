#include <ui.h>
#include <graphics.h>
#include <font.h>

/*
  Terminal on graphics
*/
namespace UI::Terminal
{

const u8 size_ratio = 2; //1 = 1:1px on screen, 2 = 1:2*2px on screen

static u32 cursor_x = 0; //unit: pixel
static u32 cursor_y = 0; //unit: pixel

static u32 max_x = 0;
static u32 max_y = 0;

static u32 text_color = DEFAULT_TEXT_COLOR;
static u32 bg_color = DEFAULT_BG_COLOR; //NDY

void plot_virtal(u32 x, u32 y, u32 c);

void init()
{
  //initialize max_x, max_y
  max_x = Graphics::get_width() / (FONT_WIDTH + FONT_GAP_SIZE) * size_ratio;
  max_y = Graphics::get_height() / (FONT_HEIGHT + FONT_GAP_SIZE) * size_ratio;
  Graphics::clear_screen(bg_color);
}

void write(char *str)
{
  while(*str != '\0'){
    put(*str);
    str++;
  }
}

void put(char letter)
{
  //border checking
  if(!valid_pos(cursor_x + 1, cursor_y)){
    //no more space on this line
    if(!valid_pos(cursor_x, cursor_y + 1)){
      //no more space on canvas
      Graphics::clear_screen(bg_color);
      set_pos(0, 0);
    }else{
      //go new line
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
      if(valid_pos(cursor_x, cursor_y + 1)){
        set_pos(0, cursor_y + 1);
      } //dont want to destory current view, so dont implement else condition.
      return;
      break;
    case ' ':
      cursor_x++;
      return;
      break;
    case '\t':
      if (valid_pos(cursor_x + 4, cursor_y))
      {
        cursor_x += 4;
      }
      return;
      break;
    default:
      //print NULL
      index = 0;
      break;
    }
  }

  //ploting pixels
  for (u32 y = 0; y < FONT_HEIGHT; y++)
  {
    for (u32 x = 0; x < FONT_WIDTH; x++)
    {
      u32 color = bg_color;
      if (font_data[index][y] & (1 << x))
      {
        color = text_color;
      }

      //plotting scaled font
      plot_virtal(FONT_WIDTH - x, y, color);
    }
  }
  set_pos(cursor_x + 1, cursor_y);
}

void plot_virtal(u32 x, u32 y, u32 c){
  for(u8 py = 0; py < size_ratio; py++){
    for(u8 px = 0; px < size_ratio; px++){
      Graphics::plot(size_ratio * (cursor_x * (FONT_WIDTH + FONT_GAP_SIZE) +  x) + px, size_ratio * (cursor_y * FONT_HEIGHT + y) + py,
                       c);
    }
  }
}

void set_pos(u32 x, u32 y)
{
  if (valid_pos(x, y))
  {
    cursor_x = x;
    cursor_y = y;
  }
}

void get_pos(u32 *x, u32 *y)
{
  if (x != null)
  {
    *x = cursor_x;
  }
  if (y != null)
  {
    *y = cursor_y;
  }
}

bool valid_pos(u32 x, u32 y)
{
  return (x <= max_x) && (y <= max_y);
}

void set_color(u32 c) { text_color = c; }
}