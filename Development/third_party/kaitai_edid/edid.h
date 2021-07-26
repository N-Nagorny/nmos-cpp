#ifndef EDID_H_
#define EDID_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class edid_t : public kaitai::kstruct {

public:
    class est_timings_info_t;
    class dtd_features_bitmap_t;
    class std_timing_t;
    class chromacity_info_t;
    class dtd_timing_t;

    edid_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, edid_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~edid_t();

    class est_timings_info_t : public kaitai::kstruct {

    public:

        est_timings_info_t(kaitai::kstream* p__io, edid_t* p__parent = 0, edid_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~est_timings_info_t();

    private:
        bool m_can_720x400px_70hz;
        bool m_can_720x400px_88hz;
        bool m_can_640x480px_60hz;
        bool m_can_640x480px_67hz;
        bool m_can_640x480px_72hz;
        bool m_can_640x480px_75hz;
        bool m_can_800x600px_56hz;
        bool m_can_800x600px_60hz;
        bool m_can_800x600px_72hz;
        bool m_can_800x600px_75hz;
        bool m_can_832x624px_75hz;
        bool m_can_1024x768px_87hz_i;
        bool m_can_1024x768px_60hz;
        bool m_can_1024x768px_70hz;
        bool m_can_1024x768px_75hz;
        bool m_can_1280x1024px_75hz;
        bool m_can_1152x870px_75hz;
        uint64_t m_reserved;
        edid_t* m__root;
        edid_t* m__parent;

    public:

        /**
         * Supports 720 x 400 @ 70Hz
         */
        bool can_720x400px_70hz() const { return m_can_720x400px_70hz; }

        /**
         * Supports 720 x 400 @ 88Hz
         */
        bool can_720x400px_88hz() const { return m_can_720x400px_88hz; }

        /**
         * Supports 640 x 480 @ 60Hz
         */
        bool can_640x480px_60hz() const { return m_can_640x480px_60hz; }

        /**
         * Supports 640 x 480 @ 67Hz
         */
        bool can_640x480px_67hz() const { return m_can_640x480px_67hz; }

        /**
         * Supports 640 x 480 @ 72Hz
         */
        bool can_640x480px_72hz() const { return m_can_640x480px_72hz; }

        /**
         * Supports 640 x 480 @ 75Hz
         */
        bool can_640x480px_75hz() const { return m_can_640x480px_75hz; }

        /**
         * Supports 800 x 600 @ 56Hz
         */
        bool can_800x600px_56hz() const { return m_can_800x600px_56hz; }

        /**
         * Supports 800 x 600 @ 60Hz
         */
        bool can_800x600px_60hz() const { return m_can_800x600px_60hz; }

        /**
         * Supports 800 x 600 @ 72Hz
         */
        bool can_800x600px_72hz() const { return m_can_800x600px_72hz; }

        /**
         * Supports 800 x 600 @ 75Hz
         */
        bool can_800x600px_75hz() const { return m_can_800x600px_75hz; }

        /**
         * Supports 832 x 624 @ 75Hz
         */
        bool can_832x624px_75hz() const { return m_can_832x624px_75hz; }

        /**
         * Supports 1024 x 768 @ 87Hz(I)
         */
        bool can_1024x768px_87hz_i() const { return m_can_1024x768px_87hz_i; }

        /**
         * Supports 1024 x 768 @ 60Hz
         */
        bool can_1024x768px_60hz() const { return m_can_1024x768px_60hz; }

        /**
         * Supports 1024 x 768 @ 70Hz
         */
        bool can_1024x768px_70hz() const { return m_can_1024x768px_70hz; }

        /**
         * Supports 1024 x 768 @ 75Hz
         */
        bool can_1024x768px_75hz() const { return m_can_1024x768px_75hz; }

        /**
         * Supports 1280 x 1024 @ 75Hz
         */
        bool can_1280x1024px_75hz() const { return m_can_1280x1024px_75hz; }

        /**
         * Supports 1152 x 870 @ 75Hz
         */
        bool can_1152x870px_75hz() const { return m_can_1152x870px_75hz; }
        uint64_t reserved() const { return m_reserved; }
        edid_t* _root() const { return m__root; }
        edid_t* _parent() const { return m__parent; }
    };

    class dtd_features_bitmap_t : public kaitai::kstruct {

    public:

        enum digital_sync_types_t {
            DIGITAL_SYNC_TYPES_DIGITAL_COMPOSITE = 0,
            DIGITAL_SYNC_TYPES_DIGITAL_SEPARATE = 1
        };

        enum polarity_t {
            POLARITY_NEGATIVE = 0,
            POLARITY_POSITIVE = 1
        };

        enum stereo_viewing_modes_t {
            STEREO_VIEWING_MODES_FIELD_SEQ_RIGHT_DURING_STEREO_SYNC = 2,
            STEREO_VIEWING_MODES_TWO_WAY_INTERLEAVED_RIGHT_ON_EVEN = 3,
            STEREO_VIEWING_MODES_FIELD_SEQ_LEFT_DURING_STEREO_SYNC = 4,
            STEREO_VIEWING_MODES_TWO_WAY_INTERLEAVED_LEFT_ON_EVEN = 5,
            STEREO_VIEWING_MODES_FOUR_WAY_INTERLEAVED = 6,
            STEREO_VIEWING_MODES_SIDE_BY_SIDE_INTERLEAVED = 7
        };

        enum analog_sync_types_t {
            ANALOG_SYNC_TYPES_ANALOG_COMPOSITE = 0,
            ANALOG_SYNC_TYPES_BIPOLAR_ANALOG_COMPOSITE = 1
        };

        enum sync_on_lines_modes_t {
            SYNC_ON_LINES_MODES_SYNC_ONLY_ON_GREEN = 0,
            SYNC_ON_LINES_MODES_SYNC_ON_EACH_RGB = 1
        };

        dtd_features_bitmap_t(kaitai::kstream* p__io, edid_t::dtd_timing_t* p__parent = 0, edid_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~dtd_features_bitmap_t();

    private:
        bool f_stereo_viewing_support;
        bool m_stereo_viewing_support;

    public:
        bool stereo_viewing_support();

    private:
        bool f_digital_sync_type;
        digital_sync_types_t m_digital_sync_type;
        bool n_digital_sync_type;

    public:
        bool _is_null_digital_sync_type() { digital_sync_type(); return n_digital_sync_type; };

    private:

    public:
        digital_sync_types_t digital_sync_type();

    private:
        bool f_stereo_viewing_mode;
        stereo_viewing_modes_t m_stereo_viewing_mode;
        bool n_stereo_viewing_mode;

    public:
        bool _is_null_stereo_viewing_mode() { stereo_viewing_mode(); return n_stereo_viewing_mode; };

    private:

    public:
        stereo_viewing_modes_t stereo_viewing_mode();

    private:
        bool f_analog_sync_type;
        analog_sync_types_t m_analog_sync_type;
        bool n_analog_sync_type;

    public:
        bool _is_null_analog_sync_type() { analog_sync_type(); return n_analog_sync_type; };

    private:

    public:
        analog_sync_types_t analog_sync_type();

    private:
        bool f_vert_sync_polarity;
        polarity_t m_vert_sync_polarity;
        bool n_vert_sync_polarity;

    public:
        bool _is_null_vert_sync_polarity() { vert_sync_polarity(); return n_vert_sync_polarity; };

    private:

    public:
        polarity_t vert_sync_polarity();

    private:
        bool f_with_serration;
        bool m_with_serration;
        bool n_with_serration;

    public:
        bool _is_null_with_serration() { with_serration(); return n_with_serration; };

    private:

    public:
        bool with_serration();

    private:
        bool f_sync_on_lines;
        sync_on_lines_modes_t m_sync_on_lines;
        bool n_sync_on_lines;

    public:
        bool _is_null_sync_on_lines() { sync_on_lines(); return n_sync_on_lines; };

    private:

    public:
        sync_on_lines_modes_t sync_on_lines();

    private:
        bool f_horiz_sync_polarity;
        polarity_t m_horiz_sync_polarity;
        bool n_horiz_sync_polarity;

    public:
        bool _is_null_horiz_sync_polarity() { horiz_sync_polarity(); return n_horiz_sync_polarity; };

    private:

    public:
        polarity_t horiz_sync_polarity();

    private:
        bool m_is_interlaced;
        uint64_t m_stereo_viewing_support_mod;
        bool m_is_digital_sync;
        bool m_sync_type_mod;
        bool m_serration_mod;
        bool m_horiz_sync_polarity_mod;
        bool m_stereo_viewing_support_bit;
        edid_t* m__root;
        edid_t::dtd_timing_t* m__parent;

    public:
        bool is_interlaced() const { return m_is_interlaced; }

        /**
         * Upper 2 bits of Stereo Viewing Support
         */
        uint64_t stereo_viewing_support_mod() const { return m_stereo_viewing_support_mod; }
        bool is_digital_sync() const { return m_is_digital_sync; }
        bool sync_type_mod() const { return m_sync_type_mod; }
        bool serration_mod() const { return m_serration_mod; }
        bool horiz_sync_polarity_mod() const { return m_horiz_sync_polarity_mod; }

        /**
         * Lowest bit of Stereo Viewing Support
         */
        bool stereo_viewing_support_bit() const { return m_stereo_viewing_support_bit; }
        edid_t* _root() const { return m__root; }
        edid_t::dtd_timing_t* _parent() const { return m__parent; }
    };

    class std_timing_t : public kaitai::kstruct {

    public:

        enum aspect_ratios_t {
            ASPECT_RATIOS_RATIO_16_10 = 0,
            ASPECT_RATIOS_RATIO_4_3 = 1,
            ASPECT_RATIOS_RATIO_5_4 = 2,
            ASPECT_RATIOS_RATIO_16_9 = 3
        };

        std_timing_t(kaitai::kstream* p__io, edid_t* p__parent = 0, edid_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~std_timing_t();

    private:
        bool f_bytes_lookahead;
        std::string m_bytes_lookahead;

    public:
        std::string bytes_lookahead();

    private:
        bool f_is_used;
        bool m_is_used;

    public:
        bool is_used();

    private:
        bool f_horiz_active_pixels;
        int32_t m_horiz_active_pixels;
        bool n_horiz_active_pixels;

    public:
        bool _is_null_horiz_active_pixels() { horiz_active_pixels(); return n_horiz_active_pixels; };

    private:

    public:

        /**
         * Range of horizontal active pixels.
         */
        int32_t horiz_active_pixels();

    private:
        bool f_refresh_rate;
        int32_t m_refresh_rate;
        bool n_refresh_rate;

    public:
        bool _is_null_refresh_rate() { refresh_rate(); return n_refresh_rate; };

    private:

    public:

        /**
         * Vertical refresh rate, Hz.
         */
        int32_t refresh_rate();

    private:
        uint8_t m_horiz_active_pixels_mod;
        aspect_ratios_t m_aspect_ratio;
        uint64_t m_refresh_rate_mod;
        edid_t* m__root;
        edid_t* m__parent;

    public:

        /**
         * Range of horizontal active pixels, written in modified form:
         * `(horiz_active_pixels / 8) - 31`. This yields an effective
         * range of 256..2288, with steps of 8 pixels.
         */
        uint8_t horiz_active_pixels_mod() const { return m_horiz_active_pixels_mod; }

        /**
         * Aspect ratio of the image. Can be used to calculate number
         * of vertical pixels.
         */
        aspect_ratios_t aspect_ratio() const { return m_aspect_ratio; }

        /**
         * Refresh rate in Hz, written in modified form: `refresh_rate
         * - 60`. This yields an effective range of 60..123 Hz.
         */
        uint64_t refresh_rate_mod() const { return m_refresh_rate_mod; }
        edid_t* _root() const { return m__root; }
        edid_t* _parent() const { return m__parent; }
    };

    /**
     * Chromaticity information: colorimetry and white point
     * coordinates. All coordinates are stored as fixed precision
     * 10-bit numbers, bits are shuffled for compactness.
     */

    class chromacity_info_t : public kaitai::kstruct {

    public:

        chromacity_info_t(kaitai::kstream* p__io, edid_t* p__parent = 0, edid_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~chromacity_info_t();

    private:
        bool f_green_x_int;
        int32_t m_green_x_int;

    public:
        int32_t green_x_int();

    private:
        bool f_red_y;
        double m_red_y;

    public:

        /**
         * Red Y coordinate
         */
        double red_y();

    private:
        bool f_green_y_int;
        int32_t m_green_y_int;

    public:
        int32_t green_y_int();

    private:
        bool f_white_y;
        double m_white_y;

    public:

        /**
         * White Y coordinate
         */
        double white_y();

    private:
        bool f_red_x;
        double m_red_x;

    public:

        /**
         * Red X coordinate
         */
        double red_x();

    private:
        bool f_white_x;
        double m_white_x;

    public:

        /**
         * White X coordinate
         */
        double white_x();

    private:
        bool f_blue_x;
        double m_blue_x;

    public:

        /**
         * Blue X coordinate
         */
        double blue_x();

    private:
        bool f_white_x_int;
        int32_t m_white_x_int;

    public:
        int32_t white_x_int();

    private:
        bool f_white_y_int;
        int32_t m_white_y_int;

    public:
        int32_t white_y_int();

    private:
        bool f_green_x;
        double m_green_x;

    public:

        /**
         * Green X coordinate
         */
        double green_x();

    private:
        bool f_red_x_int;
        int32_t m_red_x_int;

    public:
        int32_t red_x_int();

    private:
        bool f_red_y_int;
        int32_t m_red_y_int;

    public:
        int32_t red_y_int();

    private:
        bool f_blue_x_int;
        int32_t m_blue_x_int;

    public:
        int32_t blue_x_int();

    private:
        bool f_blue_y;
        double m_blue_y;

    public:

        /**
         * Blue Y coordinate
         */
        double blue_y();

    private:
        bool f_green_y;
        double m_green_y;

    public:

        /**
         * Green Y coordinate
         */
        double green_y();

    private:
        bool f_blue_y_int;
        int32_t m_blue_y_int;

    public:
        int32_t blue_y_int();

    private:
        uint64_t m_red_x_1_0;
        uint64_t m_red_y_1_0;
        uint64_t m_green_x_1_0;
        uint64_t m_green_y_1_0;
        uint64_t m_blue_x_1_0;
        uint64_t m_blue_y_1_0;
        uint64_t m_white_x_1_0;
        uint64_t m_white_y_1_0;
        uint8_t m_red_x_9_2;
        uint8_t m_red_y_9_2;
        uint8_t m_green_x_9_2;
        uint8_t m_green_y_9_2;
        uint8_t m_blue_x_9_2;
        uint8_t m_blue_y_9_2;
        uint8_t m_white_x_9_2;
        uint8_t m_white_y_9_2;
        edid_t* m__root;
        edid_t* m__parent;

    public:

        /**
         * Red X, bits 1..0
         */
        uint64_t red_x_1_0() const { return m_red_x_1_0; }

        /**
         * Red Y, bits 1..0
         */
        uint64_t red_y_1_0() const { return m_red_y_1_0; }

        /**
         * Green X, bits 1..0
         */
        uint64_t green_x_1_0() const { return m_green_x_1_0; }

        /**
         * Green Y, bits 1..0
         */
        uint64_t green_y_1_0() const { return m_green_y_1_0; }

        /**
         * Blue X, bits 1..0
         */
        uint64_t blue_x_1_0() const { return m_blue_x_1_0; }

        /**
         * Blue Y, bits 1..0
         */
        uint64_t blue_y_1_0() const { return m_blue_y_1_0; }

        /**
         * White X, bits 1..0
         */
        uint64_t white_x_1_0() const { return m_white_x_1_0; }

        /**
         * White Y, bits 1..0
         */
        uint64_t white_y_1_0() const { return m_white_y_1_0; }

        /**
         * Red X, bits 9..2
         */
        uint8_t red_x_9_2() const { return m_red_x_9_2; }

        /**
         * Red Y, bits 9..2
         */
        uint8_t red_y_9_2() const { return m_red_y_9_2; }

        /**
         * Green X, bits 9..2
         */
        uint8_t green_x_9_2() const { return m_green_x_9_2; }

        /**
         * Green Y, bits 9..2
         */
        uint8_t green_y_9_2() const { return m_green_y_9_2; }

        /**
         * Blue X, bits 9..2
         */
        uint8_t blue_x_9_2() const { return m_blue_x_9_2; }

        /**
         * Blue Y, bits 9..2
         */
        uint8_t blue_y_9_2() const { return m_blue_y_9_2; }

        /**
         * White X, bits 9..2
         */
        uint8_t white_x_9_2() const { return m_white_x_9_2; }

        /**
         * White Y, bits 9..2
         */
        uint8_t white_y_9_2() const { return m_white_y_9_2; }
        edid_t* _root() const { return m__root; }
        edid_t* _parent() const { return m__parent; }
    };

    class dtd_timing_t : public kaitai::kstruct {

    public:

        dtd_timing_t(kaitai::kstream* p__io, edid_t* p__parent = 0, edid_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~dtd_timing_t();

    private:
        bool f_vert_blanking;
        int32_t m_vert_blanking;
        bool n_vert_blanking;

    public:
        bool _is_null_vert_blanking() { vert_blanking(); return n_vert_blanking; };

    private:

    public:

        /**
         * Vertical Blanking.
         */
        int32_t vert_blanking();

    private:
        bool f_pixel_clock;
        int32_t m_pixel_clock;
        bool n_pixel_clock;

    public:
        bool _is_null_pixel_clock() { pixel_clock(); return n_pixel_clock; };

    private:

    public:

        /**
         * Pixel Clock in Hz.
         */
        int32_t pixel_clock();

    private:
        bool f_horiz_active_pixels;
        int32_t m_horiz_active_pixels;
        bool n_horiz_active_pixels;

    public:
        bool _is_null_horiz_active_pixels() { horiz_active_pixels(); return n_horiz_active_pixels; };

    private:

    public:

        /**
         * Horizontal active pixels.
         */
        int32_t horiz_active_pixels();

    private:
        bool f_vert_active_lines;
        int32_t m_vert_active_lines;
        bool n_vert_active_lines;

    public:
        bool _is_null_vert_active_lines() { vert_active_lines(); return n_vert_active_lines; };

    private:

    public:

        /**
         * Vertical active pixels.
         */
        int32_t vert_active_lines();

    private:
        bool f_horiz_front_porch;
        int32_t m_horiz_front_porch;
        bool n_horiz_front_porch;

    public:
        bool _is_null_horiz_front_porch() { horiz_front_porch(); return n_horiz_front_porch; };

    private:

    public:

        /**
         * Horizontal Front Porch in pixels.
         */
        int32_t horiz_front_porch();

    private:
        bool f_horiz_sync_pulse;
        int32_t m_horiz_sync_pulse;
        bool n_horiz_sync_pulse;

    public:
        bool _is_null_horiz_sync_pulse() { horiz_sync_pulse(); return n_horiz_sync_pulse; };

    private:

    public:

        /**
         * Horizontal Sync Pulse Width in pixels.
         */
        int32_t horiz_sync_pulse();

    private:
        bool f_horiz_image_size;
        int32_t m_horiz_image_size;
        bool n_horiz_image_size;

    public:
        bool _is_null_horiz_image_size() { horiz_image_size(); return n_horiz_image_size; };

    private:

    public:

        /**
         * Horizontal Image Size in mm.
         */
        int32_t horiz_image_size();

    private:
        bool f_vert_sync_pulse;
        int32_t m_vert_sync_pulse;
        bool n_vert_sync_pulse;

    public:
        bool _is_null_vert_sync_pulse() { vert_sync_pulse(); return n_vert_sync_pulse; };

    private:

    public:

        /**
         * Vertical Sync Pulse Width in pixels.
         */
        int32_t vert_sync_pulse();

    private:
        bool f_vert_front_porch;
        int32_t m_vert_front_porch;
        bool n_vert_front_porch;

    public:
        bool _is_null_vert_front_porch() { vert_front_porch(); return n_vert_front_porch; };

    private:

    public:

        /**
         * Vertical Front Porch in pixels.
         */
        int32_t vert_front_porch();

    private:
        bool f_bytes_lookahead;
        std::string m_bytes_lookahead;

    public:
        std::string bytes_lookahead();

    private:
        bool f_horiz_blanking;
        int32_t m_horiz_blanking;
        bool n_horiz_blanking;

    public:
        bool _is_null_horiz_blanking() { horiz_blanking(); return n_horiz_blanking; };

    private:

    public:

        /**
         * Horizontal Blanking.
         */
        int32_t horiz_blanking();

    private:
        bool f_is_dtd;
        bool m_is_dtd;

    public:
        bool is_dtd();

    private:
        bool f_vert_image_size;
        int32_t m_vert_image_size;
        bool n_vert_image_size;

    public:
        bool _is_null_vert_image_size() { vert_image_size(); return n_vert_image_size; };

    private:

    public:

        /**
         * Vertical Image Size in mm.
         */
        int32_t vert_image_size();

    private:
        uint16_t m_pixel_clock_mod;
        uint8_t m_horiz_active_pixels_8lsbits;
        uint8_t m_horiz_blanking_8lsbits;
        uint64_t m_horiz_active_pixels_4msbits;
        uint64_t m_horiz_blanking_4msbits;
        uint8_t m_vert_active_lines_8lsbits;
        uint8_t m_vert_blanking_8lsbits;
        uint64_t m_vert_active_lines_4msbits;
        uint64_t m_vert_blanking_4msbits;
        uint8_t m_horiz_front_porch_8lsbits;
        uint8_t m_horiz_sync_pulse_8lsbits;
        uint64_t m_vert_front_porch_4lsbits;
        uint64_t m_vert_sync_pulse_4lsbits;
        uint64_t m_horiz_front_porch_2msbits;
        uint64_t m_horiz_sync_pulse_2msbits;
        uint64_t m_vert_front_porch_2msbits;
        uint64_t m_vert_sync_pulse_2msbits;
        uint8_t m_horiz_image_size_8lsbits;
        uint8_t m_vert_image_size_8lsbits;
        uint64_t m_horiz_image_size_4msbits;
        uint64_t m_vert_image_size_4msbits;
        uint8_t m_horiz_border_pixels;
        uint8_t m_vert_border_lines;
        dtd_features_bitmap_t* m_dtd_features;
        edid_t* m__root;
        edid_t* m__parent;

    public:

        /**
         * Pixel Clock / 10,000
         */
        uint16_t pixel_clock_mod() const { return m_pixel_clock_mod; }

        /**
         * Horizontal Addressable Video in pixels --- contains lower 8 bits
         */
        uint8_t horiz_active_pixels_8lsbits() const { return m_horiz_active_pixels_8lsbits; }

        /**
         * Horizontal Blanking in pixels --- contains lower 8 bits
         */
        uint8_t horiz_blanking_8lsbits() const { return m_horiz_blanking_8lsbits; }

        /**
         * Horizontal Addressable Video in pixels --- contains upper 4 bits
         */
        uint64_t horiz_active_pixels_4msbits() const { return m_horiz_active_pixels_4msbits; }

        /**
         * Horizontal Blanking in pixels --- contains upper 4 bits
         */
        uint64_t horiz_blanking_4msbits() const { return m_horiz_blanking_4msbits; }

        /**
         * Vertical Addressable Video in lines --- contains lower 8 bits
         */
        uint8_t vert_active_lines_8lsbits() const { return m_vert_active_lines_8lsbits; }

        /**
         * Vertical Blanking in pixels --- contains lower 8 bits
         */
        uint8_t vert_blanking_8lsbits() const { return m_vert_blanking_8lsbits; }

        /**
         * Vertical Addressable Video in pixels --- contains upper 4 bits
         */
        uint64_t vert_active_lines_4msbits() const { return m_vert_active_lines_4msbits; }

        /**
         * Vertical Blanking in pixels --- contains upper 4 bits
         */
        uint64_t vert_blanking_4msbits() const { return m_vert_blanking_4msbits; }

        /**
         * Horizontal Front Porch in pixels --- contains lower 8 bits
         */
        uint8_t horiz_front_porch_8lsbits() const { return m_horiz_front_porch_8lsbits; }

        /**
         * Horizontal Sync Pulse Width in pixels --- contains lower 8 bits
         */
        uint8_t horiz_sync_pulse_8lsbits() const { return m_horiz_sync_pulse_8lsbits; }

        /**
         * Vertical Front Porch in pixels --- contains lower 4 bits
         */
        uint64_t vert_front_porch_4lsbits() const { return m_vert_front_porch_4lsbits; }

        /**
         * Vertical Sync Pulse Width in pixels --- contains lower 4 bits
         */
        uint64_t vert_sync_pulse_4lsbits() const { return m_vert_sync_pulse_4lsbits; }

        /**
         * Horizontal Front Porch in pixels --- contains upper 2 bits
         */
        uint64_t horiz_front_porch_2msbits() const { return m_horiz_front_porch_2msbits; }

        /**
         * Horizontal Sync Pulse Width in pixels --- contains upper 2 bits
         */
        uint64_t horiz_sync_pulse_2msbits() const { return m_horiz_sync_pulse_2msbits; }

        /**
         * Vertical Front Porch in pixels --- contains upper 2 bits
         */
        uint64_t vert_front_porch_2msbits() const { return m_vert_front_porch_2msbits; }

        /**
         * Vertical Sync Pulse Width in pixels --- contains upper 2 bits
         */
        uint64_t vert_sync_pulse_2msbits() const { return m_vert_sync_pulse_2msbits; }

        /**
         * Horizontal Image Size in mm --- contains lower 8 bits
         */
        uint8_t horiz_image_size_8lsbits() const { return m_horiz_image_size_8lsbits; }

        /**
         * Vertical Image Size in mm --- contains lower 8 bits
         */
        uint8_t vert_image_size_8lsbits() const { return m_vert_image_size_8lsbits; }

        /**
         * Horizontal Image Size in mm --- contains upper 4 bits
         */
        uint64_t horiz_image_size_4msbits() const { return m_horiz_image_size_4msbits; }

        /**
         * Vertical Image Size in mm --- contains upper 4 bits
         */
        uint64_t vert_image_size_4msbits() const { return m_vert_image_size_4msbits; }

        /**
         * Right Horizontal Border or Left Horizontal Border in pixels
         */
        uint8_t horiz_border_pixels() const { return m_horiz_border_pixels; }

        /**
         * Top Vertical Border or Bottom Vertical Border in Lines
         */
        uint8_t vert_border_lines() const { return m_vert_border_lines; }
        dtd_features_bitmap_t* dtd_features() const { return m_dtd_features; }
        edid_t* _root() const { return m__root; }
        edid_t* _parent() const { return m__parent; }
    };

private:
    bool f_mfg_year;
    int32_t m_mfg_year;

public:
    int32_t mfg_year();

private:
    bool f_mfg_id_ch1;
    int32_t m_mfg_id_ch1;

public:
    int32_t mfg_id_ch1();

private:
    bool f_mfg_id_ch3;
    int32_t m_mfg_id_ch3;

public:
    int32_t mfg_id_ch3();

private:
    bool f_gamma;
    double m_gamma;
    bool n_gamma;

public:
    bool _is_null_gamma() { gamma(); return n_gamma; };

private:

public:
    double gamma();

private:
    bool f_mfg_id_ch2;
    int32_t m_mfg_id_ch2;

public:
    int32_t mfg_id_ch2();

private:
    std::string m_magic;
    uint16_t m_mfg_bytes;
    uint16_t m_product_code;
    uint32_t m_serial;
    uint8_t m_mfg_week;
    uint8_t m_mfg_year_mod;
    uint8_t m_edid_version_major;
    uint8_t m_edid_version_minor;
    uint8_t m_input_flags;
    uint8_t m_screen_size_h;
    uint8_t m_screen_size_v;
    uint8_t m_gamma_mod;
    uint8_t m_features_flags;
    chromacity_info_t* m_chromacity;
    est_timings_info_t* m_est_timings;
    std::vector<std_timing_t*>* m_std_timings;
    std::vector<dtd_timing_t*>* m_eighteen_byte_descriptors;
    edid_t* m__root;
    kaitai::kstruct* m__parent;
    std::vector<std::string>* m__raw_std_timings;
    std::vector<kaitai::kstream*>* m__io__raw_std_timings;
    std::vector<std::string>* m__raw_eighteen_byte_descriptors;
    std::vector<kaitai::kstream*>* m__io__raw_eighteen_byte_descriptors;

public:
    std::string magic() const { return m_magic; }
    uint16_t mfg_bytes() const { return m_mfg_bytes; }

    /**
     * Manufacturer product code
     */
    uint16_t product_code() const { return m_product_code; }

    /**
     * Serial number
     */
    uint32_t serial() const { return m_serial; }

    /**
     * Week of manufacture. Week numbering is not consistent between manufacturers.
     */
    uint8_t mfg_week() const { return m_mfg_week; }

    /**
     * Year of manufacture, less 1990. (1990-2245). If week=255, it is the model year instead.
     */
    uint8_t mfg_year_mod() const { return m_mfg_year_mod; }

    /**
     * EDID version, usually 1 (for 1.3)
     */
    uint8_t edid_version_major() const { return m_edid_version_major; }

    /**
     * EDID revision, usually 3 (for 1.3)
     */
    uint8_t edid_version_minor() const { return m_edid_version_minor; }
    uint8_t input_flags() const { return m_input_flags; }

    /**
     * Maximum horizontal image size, in centimetres (max 292 cm/115 in at 16:9 aspect ratio)
     */
    uint8_t screen_size_h() const { return m_screen_size_h; }

    /**
     * Maximum vertical image size, in centimetres. If either byte is 0, undefined (e.g. projector)
     */
    uint8_t screen_size_v() const { return m_screen_size_v; }

    /**
     * Display gamma, datavalue = (gamma*100)-100 (range 1.00-3.54)
     */
    uint8_t gamma_mod() const { return m_gamma_mod; }
    uint8_t features_flags() const { return m_features_flags; }

    /**
     * Phosphor or filter chromaticity structure, which provides info on colorimetry and white point
     * \sa Standard, section 3.7
     */
    chromacity_info_t* chromacity() const { return m_chromacity; }

    /**
     * Block of bit flags that indicates support of so called
     * "established timings", which is a commonly used subset of VESA
     * DMT (Discrete Monitor Timings) modes.
     * \sa Standard, section 3.8
     */
    est_timings_info_t* est_timings() const { return m_est_timings; }

    /**
     * Array of descriptions of so called "standard timings", which are
     * used to specify up to 8 additional timings not included in
     * "established timings".
     */
    std::vector<std_timing_t*>* std_timings() const { return m_std_timings; }

    /**
     * Array of 18 byte descriptors, which the first of them shall be
     * Detailed Timing Descriptor reflecting Preferred Timing Mode and
     * each of the rest is either a Detailed Timing Descriptor or
     * a Display Descriptor.
     */
    std::vector<dtd_timing_t*>* eighteen_byte_descriptors() const { return m_eighteen_byte_descriptors; }
    edid_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
    std::vector<std::string>* _raw_std_timings() const { return m__raw_std_timings; }
    std::vector<kaitai::kstream*>* _io__raw_std_timings() const { return m__io__raw_std_timings; }
    std::vector<std::string>* _raw_eighteen_byte_descriptors() const { return m__raw_eighteen_byte_descriptors; }
    std::vector<kaitai::kstream*>* _io__raw_eighteen_byte_descriptors() const { return m__io__raw_eighteen_byte_descriptors; }
};

#endif  // EDID_H_
