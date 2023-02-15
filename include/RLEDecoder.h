/* RLEDecoder.h
 *
 * decode a 8-bit RLE bitmap to the screen using a custom pallete table
 *
 * This describes a 512x256 bitmap that's encoded in a custom RLE format. The
 * caller provides top-left coordinate of the 128x64 window of the bitmap to
 * display on the screen.
 *
 * If a non-zero highlight color is provided, the pixels using that color will
 * be drawn as a checkerboard where odd values of row+col are white and even
 * value are black.
 *
 * Data is encoded one row at a time byte touples.  The first byte is the number
 * of touples in the row - 2. Then that number of bytes pairs follow, with each
 * one having the number of pixels in the run - 1, followed by the color value.
 * Runs do not span multiple rows.
 */

#include <Arduboy2.h>

// 256-entry palette with each indexed color mapping to 0 (black) or 1 (white)
struct RLEPalette {
    uint8_t bits[256 / 8] = { 0 };
    void reset() {
        memset(bits, 0, sizeof(bits));
    }
    bool get(uint8_t index) const {
        uint8_t byteIndex = index >> 3;
        uint8_t bitIndex = index & 7;
        return bitRead(bits[byteIndex], bitIndex);
    }
    void set(uint8_t index, bool value) {
        uint8_t byteIndex = index >> 3;
        uint8_t bitIndex = index & 7;
        bitWrite(bits[byteIndex], bitIndex, value);
    }
};

class RLEBitmap {
public:
    // must be initialized with a PROGMEM pointer
    RLEBitmap(const uint8_t* data): data(data) { }

    uint8_t const* findRow(uint16_t rowNum) const {
        auto row = data;
        while (rowNum--) {
            uint16_t skip_count = pgm_read_byte(row++);
            row += skip_count * 2;
        }
        return row;
    }

    uint8_t const* drawRow(uint8_t const* row, int16_t x_offset, int16_t y, RLEPalette const& palette) const {
        int16_t x = 0;
        uint8_t skip_count = pgm_read_byte(row++);
        uint8_t const* next_row = row + skip_count * 2;
        while (x_offset > 0) {
            x_offset -= pgm_read_byte(row++); 
            if (x_offset >= 0) {
                ++row; // skip over color
            }
            else {
                uint8_t color = palette.get(pgm_read_byte(row++));
                Arduboy2::drawFastHLine(x, y, -x_offset, color);
                x += -x_offset;
            }
        }
        while (x < WIDTH) {
            uint8_t span = pgm_read_byte(row++);
            span = min(span, WIDTH - x);
            uint8_t color = palette.get(pgm_read_byte(row++));
            Arduboy2::drawFastHLine(x, y, span, color);
            x += span;
        }
        return next_row;
    }

    void decodeRLEToWindow(
        uint16_t x, uint16_t y,
        RLEPalette const& palette) {
        uint8_t const* row = findRow(y);
        y = 0;
        while (y < HEIGHT) {
            row = drawRow(row, x, y, palette);
            ++y;
        }
    }

private:
    const uint8_t* data;
};

