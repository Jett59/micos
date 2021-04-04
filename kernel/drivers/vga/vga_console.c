#include <vga/vga_console.h>
#include <strings.h>
#include <memory/pointers.h>
#include <drivers/init.h>

static u16_t cursor_pos;
static conmode_t conmode;
static vga_text_cell tmp_buffer [VGA_WIDTH * VGA_HEIGHT + VGA_WIDTH]; /*temp buffer for the new line function*/

static vga_text_cell * text_buffer;

void vga_init (void);

static volatile DRIVER vga_driver = {
    .init = &vga_init
};

void vga_init (void)
{
    text_buffer = get_pointer (VGA_TEXT_BUFFER);
    vga_driver.init = get_pointer (0); /*to make driver header actually compile*/
}

/*
 * scrolls the visible video ram segment down.
*/
void scroll_down ()
{
    u16_t tmp = cursor_pos / VGA_WIDTH;
    tmp--;
    cursor_pos = tmp * VGA_WIDTH; /*round down to the previous start of line*/
    memcpy (& (tmp_buffer[0]), text_buffer, VGA_WIDTH * VGA_HEIGHT * sizeof (vga_text_cell));
    memcpy (text_buffer, & (tmp_buffer [VGA_WIDTH]), VGA_WIDTH * VGA_HEIGHT * sizeof (vga_text_cell));
}

/*
 * moves to the next line.
*/
void newline ()
{
    u16_t newRow = (cursor_pos / VGA_WIDTH) + 1;
    if (newRow >= VGA_HEIGHT) {
        scroll_down ();
    }else {
        cursor_pos = newRow * VGA_WIDTH;
    }
}

/*
 * ensures that the console has enough space to write the next character. This function is called before any character is written to the screen.
 * If there is not enough space for the next character, this function moves to the next line first.
*/
void console_prepare ()
{
    if (cursor_pos >= VGA_WIDTH * VGA_HEIGHT){
        scroll_down ();
    }
}

void putcell (vga_text_cell cell)
{
    console_prepare ();
    * (text_buffer + cursor_pos) = cell;
    cursor_pos++;
}

int putchar (char c)
{
    if (c == '\n'){
        newline ();
        return (int)c;
    }
    vga_text_cell cell;
    cell.mode = conmode;
    cell.c = c;
    putcell (cell);
    return (int)c;
}

int puts (const char * str)
{
    vga_text_cell cell;
    cell.mode = conmode;
    do {
        cell.c = * str;
        if (cell.c == '\n') {
            newline ();
            continue;
        }
        putcell (cell);
    }while (* (++str));
    newline ();
    return 0;
}

void console_mode (conmode_t mode)
{
    conmode = mode;
}

conmode_t get_conmode ()
{
    return conmode;
}
