#include <fonts/renderer.h>
#include <display.h>

#define PSF_FONT_MAGIC 0x864ab572

typedef struct {
    u32_t magic;         /* magic bytes to identify PSF */
    u32_t version;       /* zero */
    u32_t header_size;    /* offset of bitmaps in file, 32 */
    u32_t flags;         /* 0 if there's no unicode table */
    u32_t number_glyphs;      /* number of glyphs */
    u32_t glyph_bytes; /* size of each glyph */
    u32_t height;        /* height in pixels */
    u32_t width;         /* width in pixels */
} psf_font_header;

extern psf_font_header font_start;

static u8_t* glyph_pointer;

void initialise_font() {
    if (font_start.magic == PSF_FONT_MAGIC) {
        glyph_pointer = ((u8_t*)&font_start) + font_start.header_size;
    }
}

static display_pixel default_pixel_color = {
    .red = 0xff,
    .green = 0xff,
    .blue = 0xff,
    .alpha = 0xff
};

void render_character(int x, int y, u32_t code_point) {
    u8_t* glyph = glyph_pointer + code_point * font_start.glyph_bytes;
    if (font_start.width == 8) {
        for (int glyph_y = 0; glyph_y < font_start.height; glyph_y ++) {
            for (int glyph_x = 0; glyph_x < font_start.width; glyph_x ++) {
                u8_t row = *(glyph + y);
                write_pixel(x * font_start.width + glyph_x, y * font_start.height + glyph_y, default_pixel_color);
            }
        }
    }
}
