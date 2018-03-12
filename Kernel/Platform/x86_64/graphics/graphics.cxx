#include <graphics.h>
#include <font.h>

namespace Graphics{

static u32 cursor_x = 0;
static u32 cursor_y = 0;

static u32 color = 0xffffff;

u32 Red(u32);
u32 Green(u32);
u32 Blue(u32);

static struct {
    u8 *frame_buff;
    u64 buffer_size;
    u32 width;
    u32 height;
    u8 pixel_size;
    u8 red_index;
    u8 green_index;
    u8 blue_index;
} video_info;

void init(SOS_BOOT_VIDEO_INFO *info) {
    video_info.frame_buff = (u8 *)info->FrameBufferBase;
    video_info.buffer_size = info->FrameBufferSize;
    video_info.width = info->HorizontalResolution;
    video_info.height = info->VerticalResolution;
    video_info.pixel_size = info->PixelSize;
    video_info.red_index = info->RIndex;
    video_info.green_index = info->GIndex;
    video_info.blue_index = info->BIndex;
}

void plot(u32 x, u32 y, u32 color) {
    u64 pos = (y * video_info.width + x) * video_info.pixel_size;
    video_info.frame_buff[pos + video_info.red_index] = Red(color);
    video_info.frame_buff[pos + video_info.green_index] = Green(color);
    video_info.frame_buff[pos + video_info.blue_index] = Blue(color);
}

void clear_screen(){
    clear_screen(DEFAULT_COLOR);
}

void clear_screen(u32 color) {
    for (u32 i = 0; i < video_info.buffer_size; i += video_info.pixel_size) {
        video_info.frame_buff[i + video_info.red_index] = Red(color);
        video_info.frame_buff[i + video_info.green_index] = Green(color);
        video_info.frame_buff[i + video_info.blue_index] = Blue(color);
    }
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

void put_char(char letter)
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
    case '\t':
      if((cursor_x + 2) * FONT_WIDTH <= Graphics::get_width()){
      set_pos(cursor_x + 2, cursor_y);
      }
      //NDY
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

void set_color(u32 c) { color = c; }


u32 get_width(){
    return video_info.width;
}

u32 get_height(){
    return video_info.height;
}

u32 Red(u32 color) { return (color & 0xff0000) >> 16; }
u32 Green(u32 color) { return (color & 0xff00) >> 8; }
u32 Blue(u32 color) { return (color & 0xff); }
}