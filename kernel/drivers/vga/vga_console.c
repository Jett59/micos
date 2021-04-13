#include <vga/vga_console.h>
#include <strings.h>
#include <memory/pointers.h>
#include <drivers/init.h>

static u16_t cursor_pos;
static vga_text_cell tmp_buffer [VGA_WIDTH * VGA_HEIGHT + VGA_WIDTH]; /*temp buffer for the new line function*/

static vga_text_cell * text_buffer;

void vga_init (void);

static volatile DRIVER vga_driver = {
    .init = &vga_init,
    .priority = 0
};

void vga_init (void)
{
    text_buffer = get_pointer (VGA_TEXT_BUFFER);
    vga_driver.init = get_pointer (0); /*to make driver header actually compile*/
}

/*
 * scrolls the visible video ram segment down.
*/
static void scroll_down ()
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
static void newline ()
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
void vga_console_prepare ()
{
    if (cursor_pos >= VGA_WIDTH * VGA_HEIGHT){
        scroll_down ();
    }
}

void vga_print_char (char c, conmode_t conmode)
{
    if (c == '\n') {
        newline ();
        return;
    }
    vga_text_cell cell = {
        .c = c,
        .mode = conmode
    };
    vga_console_prepare ();
    * text_buffer = cell;
    cursor_pos ++;
}
