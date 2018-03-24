#include <ui.h>
#include <peripheral.h>

namespace UI::Logging
{
/* UNSAFE! */
void log(char *str, ...)
{
    va_list vl;
    u16 arg_num = 0;
    i64 unsafe_i64 = 0;
    u64 unsafe_u64 = 0;
    u8 buff_index = 0;
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
                if (unsafe_i64 == 0)
                {
                    buff[buff_index++] = '0';
                }
                if (unsafe_i64 < 0)
                {
                    Peripheral::Serial::put('-');
                    UI::Terminal::put('-');
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
            case 'x':
            {
                // treat pushed bytes as unsigned integer
                unsafe_u64 = va_arg(vl, u64);
                if (unsafe_u64 == 0)
                {
                    buff[buff_index++] = hex_list[0];
                }
                while (unsafe_u64 > 0)
                {
                    buff[buff_index++] = hex_list[unsafe_u64 % 16];
                    unsafe_u64 /= 16; // divide by 16
                }
                break;
            }
            // as Upper hex string
            case 'X':
            {
                unsafe_u64 = va_arg(vl, u64);
                if (unsafe_u64 == 0)
                {
                    buff[buff_index++] = hex_list[0];
                }
                while (unsafe_u64 > 0)
                {
                    char mapped_char = hex_list[unsafe_u64 % 16];
                    // convert lower char to upper
                    if (unsafe_u64 % 16 >= 0xa)
                    {
                        mapped_char = (mapped_char - 'a') * ('Z' - 'A') / ('z' - 'a') + 'A';
                    }
                    buff[buff_index++] = mapped_char;
                    unsafe_u64 /= 16; // divide by 16
                }
                break;
            }
            // as binary
            case 'b':
            {
                unsafe_u64 = va_arg(vl, u64);
                if (unsafe_u64 == 0)
                {
                    buff[buff_index++] = '0';
                }
                while (unsafe_u64 != 0)
                {
                    if (unsafe_u64 & 1)
                    {
                        buff[buff_index++] = '1';
                    }
                    else
                    {
                        buff[buff_index++] = '0';
                    }
                    unsafe_u64 >>= 1; // divide by 2
                }
                break;
            }
            //as char*
            case 's':
            {
                char *ptr = (char *)va_arg(vl, u64);
                if (ptr == null)
                    return;

                Peripheral::Serial::write(ptr);

                while (*ptr != '\0')
                {
                    UI::Terminal::put(*ptr);
                    ptr++;
                }
                break;
            }
            default:
                Peripheral::Serial::put('%');
                UI::Terminal::put('%');
                break;
            }
            // print querried chars
            if (buff_index != 0)
            {

                for (i16 i = --buff_index; i > -1; i--)
                {
                    Peripheral::Serial::put(buff[i]);
                    UI::Terminal::put(buff[i]);
                }
            }
            // decrease counter
            arg_num--;
            str++; //pass to next char
        }
        else //if not '%'
        {
            Peripheral::Serial::put(*str);
            UI::Terminal::put(*str);
        }
        str++;
    }
}

void assert(bool condition)
{
}
}