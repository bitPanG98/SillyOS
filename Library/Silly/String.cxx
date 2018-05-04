#include <String.h>

// %d or %i: signed decimal integer
// %x: lower case hex
// %X: upper case hex
// %e: lower case notation
// %E: upper case notation
// %b: binary
// %s: string
// %%: print %
// %c: color
char* Format(const char* fmt, ...){
    static char buff[MAX_STRING_LENGTH];
    SetMemory(buff, 0, MAX_STRING_LENGTH);
    va_list vl;
    va_start(vl, fmt);
    u32 result = vFormat(buff, fmt, vl);
    va_end(vl);
    if(result == 0) return (char *)null;
    return buff;
}

u32 vFormat(char *buff, const char *fmt, va_list vl)
{
    u8 percent_num = 0;
    i64 unsafe_i64 = 0;
    u64 unsafe_u64 = 0;
    u32 buff_index = 0;
    char *temp = (char *)fmt;
    //get number of percent sign
    while (*temp != '\0')
    {
        if (*temp == '%')
        {
            percent_num++;
        }
        temp++;
    }
    //reset tempo pointer
    temp = (char *)fmt;
    while (*temp != '\0' && buff_index <= 255)
    {
        //argument found
        if (*temp == '%' && percent_num != 0)
        {
            switch (*(temp + 1))
            {
            //decimal
            case 'i':
            case 'd':
            {
                unsafe_i64 = va_arg(vl, i64);
                buff_index += ToInt(unsafe_i64, 'd', buff + buff_index);
                break;
            }
            //octal
            case 'o':
            {
                unsafe_u64 = va_arg(vl, u64);
                buff_index += ToInt(unsafe_u64, 'o', buff + buff_index);
                break;
            }
            //binary
            case 'b':
            {
                unsafe_u64 = va_arg(vl, u64);
                buff_index += ToInt(unsafe_u64, 'b', &(buff[buff_index]));
                break;
            }
            //lower heximal
            case 'x':
            {
                unsafe_u64 = va_arg(vl, u64);
                buff_index += ToInt(unsafe_u64, 'x', &(buff[buff_index]));
                break;
            }
            //upper heximal
            case 'X':
            {
                unsafe_u64 = va_arg(vl, u64);
                buff_index += ToInt(unsafe_u64, 'X', &(buff[buff_index]));
                break;
            }
            //string
            case 's':
            {
                char *ptr = (char *)va_arg(vl, u64);
                if (ptr == null)
                    return 0;

                while (*ptr != '\0')
                {
                    buff[buff_index++] = *ptr;
                    ptr++;
                }
                break;
            }
            //treat unknown argumnt as normal text
            default:
            {
                buff[buff_index++] = *(temp + 1);
                break;
            }
            }//switch end

            percent_num--;
            temp++; //skip current '%'
        } //not a argument
        else
        {
            buff[buff_index++] = *temp;
        }
        temp++;
    }
    buff[buff_index] = '\0';
    return buff_index;
}

u8 ToInt(u64 num, char base, char *buff)
{
    const char *hex_lower = "0123456789abcdef";
    u8 written = 0;
    char temp[MAX_STRING_LENGTH];
    //wipe before use
    SetMemory(temp, 0, MAX_STRING_LENGTH);
    switch (base)
    {
    //binary
    case 'b':
    {
        if (num == 0)
        {
            temp[written++] = '0';
        }
        while (num != 0)
        {
            if (num & 1)
            {
                temp[written++] = '1';
            }
            else
            {
                temp[written++] = '0';
            }
            num >>= 1; // divide by 2
        }
        break;
    }
    //decimal
    case 'd':
    {
        i64 signed_num = (i64)num;
        bool negetive = false;
        //print a '-' sign if the integer is smaller than 0
        if (signed_num == 0)
        {
            temp[written++] = '0';
            break;
        }
        if (signed_num < 0)
        {
            negetive = true;
        }

        // Workflow:
        // me: Ayy! signed_num!
        // signed_num: I feel depressed, you know...just like I am so negetive than everyone was.
        // me: You should go out and date some -1 numbers!
        signed_num = signed_num < 0 ? signed_num * -1 : signed_num;
        while (signed_num > 0)
        {
            temp[written++] = '0' + signed_num % 10;
            signed_num /= 10; // divide by 10
        }
        //add '-' sign to the end of the string.
        if (negetive)
            temp[written++] = '-';
        break;
    }
    //octal
    case 'o':
    {
        if (num == 0)
        {
            temp[written++] = hex_lower[0];
        }
        while (num > 0)
        {
            temp[written++] = hex_lower[num % 8];
            num /= 8; // divide by 16
        }
        break;
    }
    //lower case heximal
    case 'x':
    {
        if (num == 0)
        {
            temp[written++] = hex_lower[0];
        }
        while (num > 0)
        {
            temp[written++] = hex_lower[num % 16];
            num /= 16; // divide by 16
        }
        break;
    }
    //upper case heximal
    case 'X':
    {
        if (num == 0)
        {
            temp[written++] = hex_lower[0];
        }
        while (num > 0)
        {
            temp[written++] = hex_lower[num % 16];
            num /= 16; // divide by 16
        }
        ToUpper(temp);
        break;
    }
    default:
        break;
    }
    //reverse buffer
    if (written != 0)
    {
        u8 buff_i = 0;
        for (i16 i = --written; i > -1; i--)
        {
            buff[buff_i++] = temp[i];
        }
        return buff_i;
    }
    return 0;
}

void ToLower(char *text)
{
    char *temp = text;
    while (*temp != '\0')
    {
        //do nothing with non-upper characters
        if (*temp < 'A' || *temp > 'Z')
            continue;
        //convert upper chars to lower
        *temp = (*temp - 'A') + 'a';
        temp++;
    }
}
void ToUpper(char *text)
{
    char *temp = text;
    while (*temp != '\0')
    {
        //do nothing with non-lower characters
        if (*temp < 'a' || *temp > 'z')
            continue;
        //convert lower chars to upper
        *temp = (*temp - 'a') + 'A';
        temp++;
    }
}

u64 CopyMemory(void *des, const void *src, u64 n)
{
    u64 i = 0;
    while (i != n)
    {
        ((u8 *)des)[i] = ((u8 *)src)[i];
        i++;
    }
    return i;
}

u64 SetMemory(void *des, u8 src, u64 n)
{
    u64 i = 0;
    while (i != n)
    {
        ((u8 *)des)[i++] = src;
    }
    return i;
}

bool CmpMemory(void *to, void *from, u64 n)
{
    u64 i = 0;
    while (i != n)
    {
        if (*((u8 *)from) != *((u8 *)to))
            return false;
        i++;
    }
    return true;
}
