// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "edid.h"
#include "kaitai/exceptions.h"

edid_t::edid_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, edid_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_chromacity = 0;
    m_est_timings = 0;
    m_std_timings = 0;
    m__raw_std_timings = 0;
    m__io__raw_std_timings = 0;
    m_eighteen_byte_descriptors = 0;
    m__raw_eighteen_byte_descriptors = 0;
    m__io__raw_eighteen_byte_descriptors = 0;
    f_mfg_year = false;
    f_mfg_id_ch1 = false;
    f_mfg_id_ch3 = false;
    f_gamma = false;
    f_mfg_id_ch2 = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void edid_t::_read() {
    m_magic = m__io->read_bytes(8);
    if (!(magic() == std::string("\x00\xFF\xFF\xFF\xFF\xFF\xFF\x00", 8))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x00\xFF\xFF\xFF\xFF\xFF\xFF\x00", 8), magic(), _io(), std::string("/seq/0"));
    }
    m_mfg_bytes = m__io->read_u2be();
    m_product_code = m__io->read_u2le();
    m_serial = m__io->read_u4le();
    m_mfg_week = m__io->read_u1();
    m_mfg_year_mod = m__io->read_u1();
    m_edid_version_major = m__io->read_u1();
    m_edid_version_minor = m__io->read_u1();
    m_input_flags = m__io->read_u1();
    m_screen_size_h = m__io->read_u1();
    m_screen_size_v = m__io->read_u1();
    m_gamma_mod = m__io->read_u1();
    m_features_flags = m__io->read_u1();
    m_chromacity = new chromacity_info_t(m__io, this, m__root);
    m_est_timings = new est_timings_info_t(m__io, this, m__root);
    int l_std_timings = 8;
    m__raw_std_timings = new std::vector<std::string>();
    m__raw_std_timings->reserve(l_std_timings);
    m__io__raw_std_timings = new std::vector<kaitai::kstream*>();
    m__io__raw_std_timings->reserve(l_std_timings);
    m_std_timings = new std::vector<std_timing_t*>();
    m_std_timings->reserve(l_std_timings);
    for (int i = 0; i < l_std_timings; i++) {
        m__raw_std_timings->push_back(m__io->read_bytes(2));
        kaitai::kstream* io__raw_std_timings = new kaitai::kstream(m__raw_std_timings->at(m__raw_std_timings->size() - 1));
        m__io__raw_std_timings->push_back(io__raw_std_timings);
        m_std_timings->push_back(new std_timing_t(io__raw_std_timings, this, m__root));
    }
    int l_eighteen_byte_descriptors = 4;
    m__raw_eighteen_byte_descriptors = new std::vector<std::string>();
    m__raw_eighteen_byte_descriptors->reserve(l_eighteen_byte_descriptors);
    m__io__raw_eighteen_byte_descriptors = new std::vector<kaitai::kstream*>();
    m__io__raw_eighteen_byte_descriptors->reserve(l_eighteen_byte_descriptors);
    m_eighteen_byte_descriptors = new std::vector<dtd_timing_t*>();
    m_eighteen_byte_descriptors->reserve(l_eighteen_byte_descriptors);
    for (int i = 0; i < l_eighteen_byte_descriptors; i++) {
        m__raw_eighteen_byte_descriptors->push_back(m__io->read_bytes(18));
        kaitai::kstream* io__raw_eighteen_byte_descriptors = new kaitai::kstream(m__raw_eighteen_byte_descriptors->at(m__raw_eighteen_byte_descriptors->size() - 1));
        m__io__raw_eighteen_byte_descriptors->push_back(io__raw_eighteen_byte_descriptors);
        m_eighteen_byte_descriptors->push_back(new dtd_timing_t(io__raw_eighteen_byte_descriptors, this, m__root));
    }
}

edid_t::~edid_t() {
    _clean_up();
}

void edid_t::_clean_up() {
    if (m_chromacity) {
        delete m_chromacity; m_chromacity = 0;
    }
    if (m_est_timings) {
        delete m_est_timings; m_est_timings = 0;
    }
    if (m__raw_std_timings) {
        delete m__raw_std_timings; m__raw_std_timings = 0;
    }
    if (m__io__raw_std_timings) {
        for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_std_timings->begin(); it != m__io__raw_std_timings->end(); ++it) {
            delete *it;
        }
        delete m__io__raw_std_timings; m__io__raw_std_timings = 0;
    }
    if (m_std_timings) {
        for (std::vector<std_timing_t*>::iterator it = m_std_timings->begin(); it != m_std_timings->end(); ++it) {
            delete *it;
        }
        delete m_std_timings; m_std_timings = 0;
    }
    if (m__raw_eighteen_byte_descriptors) {
        delete m__raw_eighteen_byte_descriptors; m__raw_eighteen_byte_descriptors = 0;
    }
    if (m__io__raw_eighteen_byte_descriptors) {
        for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_eighteen_byte_descriptors->begin(); it != m__io__raw_eighteen_byte_descriptors->end(); ++it) {
            delete *it;
        }
        delete m__io__raw_eighteen_byte_descriptors; m__io__raw_eighteen_byte_descriptors = 0;
    }
    if (m_eighteen_byte_descriptors) {
        for (std::vector<dtd_timing_t*>::iterator it = m_eighteen_byte_descriptors->begin(); it != m_eighteen_byte_descriptors->end(); ++it) {
            delete *it;
        }
        delete m_eighteen_byte_descriptors; m_eighteen_byte_descriptors = 0;
    }
}

edid_t::est_timings_info_t::est_timings_info_t(kaitai::kstream* p__io, edid_t* p__parent, edid_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void edid_t::est_timings_info_t::_read() {
    m_can_720x400px_70hz = m__io->read_bits_int_be(1);
    m_can_720x400px_88hz = m__io->read_bits_int_be(1);
    m_can_640x480px_60hz = m__io->read_bits_int_be(1);
    m_can_640x480px_67hz = m__io->read_bits_int_be(1);
    m_can_640x480px_72hz = m__io->read_bits_int_be(1);
    m_can_640x480px_75hz = m__io->read_bits_int_be(1);
    m_can_800x600px_56hz = m__io->read_bits_int_be(1);
    m_can_800x600px_60hz = m__io->read_bits_int_be(1);
    m_can_800x600px_72hz = m__io->read_bits_int_be(1);
    m_can_800x600px_75hz = m__io->read_bits_int_be(1);
    m_can_832x624px_75hz = m__io->read_bits_int_be(1);
    m_can_1024x768px_87hz_i = m__io->read_bits_int_be(1);
    m_can_1024x768px_60hz = m__io->read_bits_int_be(1);
    m_can_1024x768px_70hz = m__io->read_bits_int_be(1);
    m_can_1024x768px_75hz = m__io->read_bits_int_be(1);
    m_can_1280x1024px_75hz = m__io->read_bits_int_be(1);
    m_can_1152x870px_75hz = m__io->read_bits_int_be(1);
    m_reserved = m__io->read_bits_int_be(7);
}

edid_t::est_timings_info_t::~est_timings_info_t() {
    _clean_up();
}

void edid_t::est_timings_info_t::_clean_up() {
}

edid_t::dtd_features_bitmap_t::dtd_features_bitmap_t(kaitai::kstream* p__io, edid_t::dtd_timing_t* p__parent, edid_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_stereo_viewing_support = false;
    f_digital_sync_type = false;
    f_stereo_viewing_mode = false;
    f_analog_sync_type = false;
    f_vert_sync_polarity = false;
    f_with_serration = false;
    f_sync_on_lines = false;
    f_horiz_sync_polarity = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void edid_t::dtd_features_bitmap_t::_read() {
    m_is_interlaced = m__io->read_bits_int_be(1);
    m_stereo_viewing_support_mod = m__io->read_bits_int_be(2);
    m_is_digital_sync = m__io->read_bits_int_be(1);
    m_sync_type_mod = m__io->read_bits_int_be(1);
    m_serration_mod = m__io->read_bits_int_be(1);
    m_horiz_sync_polarity_mod = m__io->read_bits_int_be(1);
    m_stereo_viewing_support_bit = m__io->read_bits_int_be(1);
}

edid_t::dtd_features_bitmap_t::~dtd_features_bitmap_t() {
    _clean_up();
}

void edid_t::dtd_features_bitmap_t::_clean_up() {
}

bool edid_t::dtd_features_bitmap_t::stereo_viewing_support() {
    if (f_stereo_viewing_support)
        return m_stereo_viewing_support;
    m_stereo_viewing_support = stereo_viewing_support_mod() != 0;
    f_stereo_viewing_support = true;
    return m_stereo_viewing_support;
}

edid_t::dtd_features_bitmap_t::digital_sync_types_t edid_t::dtd_features_bitmap_t::digital_sync_type() {
    if (f_digital_sync_type)
        return m_digital_sync_type;
    n_digital_sync_type = true;
    if (is_digital_sync()) {
        n_digital_sync_type = false;
        m_digital_sync_type = static_cast<edid_t::dtd_features_bitmap_t::digital_sync_types_t>(sync_type_mod());
    }
    f_digital_sync_type = true;
    return m_digital_sync_type;
}

edid_t::dtd_features_bitmap_t::stereo_viewing_modes_t edid_t::dtd_features_bitmap_t::stereo_viewing_mode() {
    if (f_stereo_viewing_mode)
        return m_stereo_viewing_mode;
    n_stereo_viewing_mode = true;
    if (stereo_viewing_support()) {
        n_stereo_viewing_mode = false;
        m_stereo_viewing_mode = static_cast<edid_t::dtd_features_bitmap_t::stereo_viewing_modes_t>((((stereo_viewing_support_bit()) ? 1 : 0) | (stereo_viewing_support_mod() << 1)));
    }
    f_stereo_viewing_mode = true;
    return m_stereo_viewing_mode;
}

edid_t::dtd_features_bitmap_t::analog_sync_types_t edid_t::dtd_features_bitmap_t::analog_sync_type() {
    if (f_analog_sync_type)
        return m_analog_sync_type;
    n_analog_sync_type = true;
    if (!(is_digital_sync())) {
        n_analog_sync_type = false;
        m_analog_sync_type = static_cast<edid_t::dtd_features_bitmap_t::analog_sync_types_t>(sync_type_mod());
    }
    f_analog_sync_type = true;
    return m_analog_sync_type;
}

edid_t::dtd_features_bitmap_t::polarity_t edid_t::dtd_features_bitmap_t::vert_sync_polarity() {
    if (f_vert_sync_polarity)
        return m_vert_sync_polarity;
    n_vert_sync_polarity = true;
    if ( ((sync_type_mod() == true) && (is_digital_sync())) ) {
        n_vert_sync_polarity = false;
        m_vert_sync_polarity = static_cast<edid_t::dtd_features_bitmap_t::polarity_t>(serration_mod());
    }
    f_vert_sync_polarity = true;
    return m_vert_sync_polarity;
}

bool edid_t::dtd_features_bitmap_t::with_serration() {
    if (f_with_serration)
        return m_with_serration;
    n_with_serration = true;
    if (!( ((sync_type_mod() == true) && (is_digital_sync())) )) {
        n_with_serration = false;
        m_with_serration = serration_mod();
    }
    f_with_serration = true;
    return m_with_serration;
}

edid_t::dtd_features_bitmap_t::sync_on_lines_modes_t edid_t::dtd_features_bitmap_t::sync_on_lines() {
    if (f_sync_on_lines)
        return m_sync_on_lines;
    n_sync_on_lines = true;
    if (!(is_digital_sync())) {
        n_sync_on_lines = false;
        m_sync_on_lines = static_cast<edid_t::dtd_features_bitmap_t::sync_on_lines_modes_t>(horiz_sync_polarity_mod());
    }
    f_sync_on_lines = true;
    return m_sync_on_lines;
}

edid_t::dtd_features_bitmap_t::polarity_t edid_t::dtd_features_bitmap_t::horiz_sync_polarity() {
    if (f_horiz_sync_polarity)
        return m_horiz_sync_polarity;
    n_horiz_sync_polarity = true;
    if (is_digital_sync()) {
        n_horiz_sync_polarity = false;
        m_horiz_sync_polarity = static_cast<edid_t::dtd_features_bitmap_t::polarity_t>(horiz_sync_polarity_mod());
    }
    f_horiz_sync_polarity = true;
    return m_horiz_sync_polarity;
}

edid_t::std_timing_t::std_timing_t(kaitai::kstream* p__io, edid_t* p__parent, edid_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_bytes_lookahead = false;
    f_is_used = false;
    f_horiz_active_pixels = false;
    f_refresh_rate = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void edid_t::std_timing_t::_read() {
    m_horiz_active_pixels_mod = m__io->read_u1();
    m_aspect_ratio = static_cast<edid_t::std_timing_t::aspect_ratios_t>(m__io->read_bits_int_be(2));
    m_refresh_rate_mod = m__io->read_bits_int_be(6);
}

edid_t::std_timing_t::~std_timing_t() {
    _clean_up();
}

void edid_t::std_timing_t::_clean_up() {
    if (f_bytes_lookahead) {
    }
}

std::string edid_t::std_timing_t::bytes_lookahead() {
    if (f_bytes_lookahead)
        return m_bytes_lookahead;
    std::streampos _pos = m__io->pos();
    m__io->seek(0);
    m_bytes_lookahead = m__io->read_bytes(2);
    m__io->seek(_pos);
    f_bytes_lookahead = true;
    return m_bytes_lookahead;
}

bool edid_t::std_timing_t::is_used() {
    if (f_is_used)
        return m_is_used;
    m_is_used = bytes_lookahead() != std::string("\x01\x01", 2);
    f_is_used = true;
    return m_is_used;
}

int32_t edid_t::std_timing_t::horiz_active_pixels() {
    if (f_horiz_active_pixels)
        return m_horiz_active_pixels;
    n_horiz_active_pixels = true;
    if (is_used()) {
        n_horiz_active_pixels = false;
        m_horiz_active_pixels = ((horiz_active_pixels_mod() + 31) * 8);
    }
    f_horiz_active_pixels = true;
    return m_horiz_active_pixels;
}

int32_t edid_t::std_timing_t::refresh_rate() {
    if (f_refresh_rate)
        return m_refresh_rate;
    n_refresh_rate = true;
    if (is_used()) {
        n_refresh_rate = false;
        m_refresh_rate = (refresh_rate_mod() + 60);
    }
    f_refresh_rate = true;
    return m_refresh_rate;
}

edid_t::chromacity_info_t::chromacity_info_t(kaitai::kstream* p__io, edid_t* p__parent, edid_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_green_x_int = false;
    f_red_y = false;
    f_green_y_int = false;
    f_white_y = false;
    f_red_x = false;
    f_white_x = false;
    f_blue_x = false;
    f_white_x_int = false;
    f_white_y_int = false;
    f_green_x = false;
    f_red_x_int = false;
    f_red_y_int = false;
    f_blue_x_int = false;
    f_blue_y = false;
    f_green_y = false;
    f_blue_y_int = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void edid_t::chromacity_info_t::_read() {
    m_red_x_1_0 = m__io->read_bits_int_be(2);
    m_red_y_1_0 = m__io->read_bits_int_be(2);
    m_green_x_1_0 = m__io->read_bits_int_be(2);
    m_green_y_1_0 = m__io->read_bits_int_be(2);
    m_blue_x_1_0 = m__io->read_bits_int_be(2);
    m_blue_y_1_0 = m__io->read_bits_int_be(2);
    m_white_x_1_0 = m__io->read_bits_int_be(2);
    m_white_y_1_0 = m__io->read_bits_int_be(2);
    m__io->align_to_byte();
    m_red_x_9_2 = m__io->read_u1();
    m_red_y_9_2 = m__io->read_u1();
    m_green_x_9_2 = m__io->read_u1();
    m_green_y_9_2 = m__io->read_u1();
    m_blue_x_9_2 = m__io->read_u1();
    m_blue_y_9_2 = m__io->read_u1();
    m_white_x_9_2 = m__io->read_u1();
    m_white_y_9_2 = m__io->read_u1();
}

edid_t::chromacity_info_t::~chromacity_info_t() {
    _clean_up();
}

void edid_t::chromacity_info_t::_clean_up() {
}

int32_t edid_t::chromacity_info_t::green_x_int() {
    if (f_green_x_int)
        return m_green_x_int;
    m_green_x_int = ((green_x_9_2() << 2) | green_x_1_0());
    f_green_x_int = true;
    return m_green_x_int;
}

double edid_t::chromacity_info_t::red_y() {
    if (f_red_y)
        return m_red_y;
    m_red_y = (red_y_int() / 1024.0);
    f_red_y = true;
    return m_red_y;
}

int32_t edid_t::chromacity_info_t::green_y_int() {
    if (f_green_y_int)
        return m_green_y_int;
    m_green_y_int = ((green_y_9_2() << 2) | green_y_1_0());
    f_green_y_int = true;
    return m_green_y_int;
}

double edid_t::chromacity_info_t::white_y() {
    if (f_white_y)
        return m_white_y;
    m_white_y = (white_y_int() / 1024.0);
    f_white_y = true;
    return m_white_y;
}

double edid_t::chromacity_info_t::red_x() {
    if (f_red_x)
        return m_red_x;
    m_red_x = (red_x_int() / 1024.0);
    f_red_x = true;
    return m_red_x;
}

double edid_t::chromacity_info_t::white_x() {
    if (f_white_x)
        return m_white_x;
    m_white_x = (white_x_int() / 1024.0);
    f_white_x = true;
    return m_white_x;
}

double edid_t::chromacity_info_t::blue_x() {
    if (f_blue_x)
        return m_blue_x;
    m_blue_x = (blue_x_int() / 1024.0);
    f_blue_x = true;
    return m_blue_x;
}

int32_t edid_t::chromacity_info_t::white_x_int() {
    if (f_white_x_int)
        return m_white_x_int;
    m_white_x_int = ((white_x_9_2() << 2) | white_x_1_0());
    f_white_x_int = true;
    return m_white_x_int;
}

int32_t edid_t::chromacity_info_t::white_y_int() {
    if (f_white_y_int)
        return m_white_y_int;
    m_white_y_int = ((white_y_9_2() << 2) | white_y_1_0());
    f_white_y_int = true;
    return m_white_y_int;
}

double edid_t::chromacity_info_t::green_x() {
    if (f_green_x)
        return m_green_x;
    m_green_x = (green_x_int() / 1024.0);
    f_green_x = true;
    return m_green_x;
}

int32_t edid_t::chromacity_info_t::red_x_int() {
    if (f_red_x_int)
        return m_red_x_int;
    m_red_x_int = ((red_x_9_2() << 2) | red_x_1_0());
    f_red_x_int = true;
    return m_red_x_int;
}

int32_t edid_t::chromacity_info_t::red_y_int() {
    if (f_red_y_int)
        return m_red_y_int;
    m_red_y_int = ((red_y_9_2() << 2) | red_y_1_0());
    f_red_y_int = true;
    return m_red_y_int;
}

int32_t edid_t::chromacity_info_t::blue_x_int() {
    if (f_blue_x_int)
        return m_blue_x_int;
    m_blue_x_int = ((blue_x_9_2() << 2) | blue_x_1_0());
    f_blue_x_int = true;
    return m_blue_x_int;
}

double edid_t::chromacity_info_t::blue_y() {
    if (f_blue_y)
        return m_blue_y;
    m_blue_y = (blue_y_int() / 1024.0);
    f_blue_y = true;
    return m_blue_y;
}

double edid_t::chromacity_info_t::green_y() {
    if (f_green_y)
        return m_green_y;
    m_green_y = (green_y_int() / 1024.0);
    f_green_y = true;
    return m_green_y;
}

int32_t edid_t::chromacity_info_t::blue_y_int() {
    if (f_blue_y_int)
        return m_blue_y_int;
    m_blue_y_int = ((blue_y_9_2() << 2) | blue_y_1_0());
    f_blue_y_int = true;
    return m_blue_y_int;
}

edid_t::dtd_timing_t::dtd_timing_t(kaitai::kstream* p__io, edid_t* p__parent, edid_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_dtd_features = 0;
    f_vert_blanking = false;
    f_pixel_clock = false;
    f_horiz_active_pixels = false;
    f_vert_active_lines = false;
    f_horiz_front_porch = false;
    f_horiz_sync_pulse = false;
    f_horiz_image_size = false;
    f_vert_sync_pulse = false;
    f_vert_front_porch = false;
    f_bytes_lookahead = false;
    f_horiz_blanking = false;
    f_is_dtd = false;
    f_vert_image_size = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void edid_t::dtd_timing_t::_read() {
    m_pixel_clock_mod = m__io->read_u2le();
    m_horiz_active_pixels_8lsbits = m__io->read_u1();
    m_horiz_blanking_8lsbits = m__io->read_u1();
    m_horiz_active_pixels_4msbits = m__io->read_bits_int_be(4);
    m_horiz_blanking_4msbits = m__io->read_bits_int_be(4);
    m__io->align_to_byte();
    m_vert_active_lines_8lsbits = m__io->read_u1();
    m_vert_blanking_8lsbits = m__io->read_u1();
    m_vert_active_lines_4msbits = m__io->read_bits_int_be(4);
    m_vert_blanking_4msbits = m__io->read_bits_int_be(4);
    m__io->align_to_byte();
    m_horiz_front_porch_8lsbits = m__io->read_u1();
    m_horiz_sync_pulse_8lsbits = m__io->read_u1();
    m_vert_front_porch_4lsbits = m__io->read_bits_int_be(4);
    m_vert_sync_pulse_4lsbits = m__io->read_bits_int_be(4);
    m_horiz_front_porch_2msbits = m__io->read_bits_int_be(2);
    m_horiz_sync_pulse_2msbits = m__io->read_bits_int_be(2);
    m_vert_front_porch_2msbits = m__io->read_bits_int_be(2);
    m_vert_sync_pulse_2msbits = m__io->read_bits_int_be(2);
    m__io->align_to_byte();
    m_horiz_image_size_8lsbits = m__io->read_u1();
    m_vert_image_size_8lsbits = m__io->read_u1();
    m_horiz_image_size_4msbits = m__io->read_bits_int_be(4);
    m_vert_image_size_4msbits = m__io->read_bits_int_be(4);
    m__io->align_to_byte();
    m_horiz_border_pixels = m__io->read_u1();
    m_vert_border_lines = m__io->read_u1();
    m_dtd_features = new dtd_features_bitmap_t(m__io, this, m__root);
}

edid_t::dtd_timing_t::~dtd_timing_t() {
    _clean_up();
}

void edid_t::dtd_timing_t::_clean_up() {
    if (m_dtd_features) {
        delete m_dtd_features; m_dtd_features = 0;
    }
    if (f_bytes_lookahead) {
    }
}

int32_t edid_t::dtd_timing_t::vert_blanking() {
    if (f_vert_blanking)
        return m_vert_blanking;
    n_vert_blanking = true;
    if (is_dtd()) {
        n_vert_blanking = false;
        m_vert_blanking = (vert_blanking_8lsbits() | (vert_blanking_4msbits() << 8));
    }
    f_vert_blanking = true;
    return m_vert_blanking;
}

int32_t edid_t::dtd_timing_t::pixel_clock() {
    if (f_pixel_clock)
        return m_pixel_clock;
    n_pixel_clock = true;
    if (is_dtd()) {
        n_pixel_clock = false;
        m_pixel_clock = (pixel_clock_mod() * 10000);
    }
    f_pixel_clock = true;
    return m_pixel_clock;
}

int32_t edid_t::dtd_timing_t::horiz_active_pixels() {
    if (f_horiz_active_pixels)
        return m_horiz_active_pixels;
    n_horiz_active_pixels = true;
    if (is_dtd()) {
        n_horiz_active_pixels = false;
        m_horiz_active_pixels = (horiz_active_pixels_8lsbits() | (horiz_active_pixels_4msbits() << 8));
    }
    f_horiz_active_pixels = true;
    return m_horiz_active_pixels;
}

int32_t edid_t::dtd_timing_t::vert_active_lines() {
    if (f_vert_active_lines)
        return m_vert_active_lines;
    n_vert_active_lines = true;
    if (is_dtd()) {
        n_vert_active_lines = false;
        m_vert_active_lines = (vert_active_lines_8lsbits() | (vert_active_lines_4msbits() << 8));
    }
    f_vert_active_lines = true;
    return m_vert_active_lines;
}

int32_t edid_t::dtd_timing_t::horiz_front_porch() {
    if (f_horiz_front_porch)
        return m_horiz_front_porch;
    n_horiz_front_porch = true;
    if (is_dtd()) {
        n_horiz_front_porch = false;
        m_horiz_front_porch = (horiz_front_porch_8lsbits() | (horiz_front_porch_2msbits() << 8));
    }
    f_horiz_front_porch = true;
    return m_horiz_front_porch;
}

int32_t edid_t::dtd_timing_t::horiz_sync_pulse() {
    if (f_horiz_sync_pulse)
        return m_horiz_sync_pulse;
    n_horiz_sync_pulse = true;
    if (is_dtd()) {
        n_horiz_sync_pulse = false;
        m_horiz_sync_pulse = (horiz_sync_pulse_8lsbits() | (horiz_sync_pulse_2msbits() << 8));
    }
    f_horiz_sync_pulse = true;
    return m_horiz_sync_pulse;
}

int32_t edid_t::dtd_timing_t::horiz_image_size() {
    if (f_horiz_image_size)
        return m_horiz_image_size;
    n_horiz_image_size = true;
    if (is_dtd()) {
        n_horiz_image_size = false;
        m_horiz_image_size = (horiz_image_size_8lsbits() | (horiz_image_size_4msbits() << 8));
    }
    f_horiz_image_size = true;
    return m_horiz_image_size;
}

int32_t edid_t::dtd_timing_t::vert_sync_pulse() {
    if (f_vert_sync_pulse)
        return m_vert_sync_pulse;
    n_vert_sync_pulse = true;
    if (is_dtd()) {
        n_vert_sync_pulse = false;
        m_vert_sync_pulse = (vert_sync_pulse_4lsbits() | (vert_sync_pulse_2msbits() << 4));
    }
    f_vert_sync_pulse = true;
    return m_vert_sync_pulse;
}

int32_t edid_t::dtd_timing_t::vert_front_porch() {
    if (f_vert_front_porch)
        return m_vert_front_porch;
    n_vert_front_porch = true;
    if (is_dtd()) {
        n_vert_front_porch = false;
        m_vert_front_porch = (vert_front_porch_4lsbits() | (vert_front_porch_2msbits() << 4));
    }
    f_vert_front_porch = true;
    return m_vert_front_porch;
}

std::string edid_t::dtd_timing_t::bytes_lookahead() {
    if (f_bytes_lookahead)
        return m_bytes_lookahead;
    std::streampos _pos = m__io->pos();
    m__io->seek(0);
    m_bytes_lookahead = m__io->read_bytes(2);
    m__io->seek(_pos);
    f_bytes_lookahead = true;
    return m_bytes_lookahead;
}

int32_t edid_t::dtd_timing_t::horiz_blanking() {
    if (f_horiz_blanking)
        return m_horiz_blanking;
    n_horiz_blanking = true;
    if (is_dtd()) {
        n_horiz_blanking = false;
        m_horiz_blanking = (horiz_blanking_8lsbits() | (horiz_blanking_4msbits() << 8));
    }
    f_horiz_blanking = true;
    return m_horiz_blanking;
}

bool edid_t::dtd_timing_t::is_dtd() {
    if (f_is_dtd)
        return m_is_dtd;
    m_is_dtd = bytes_lookahead() != std::string("\x00\x00", 2);
    f_is_dtd = true;
    return m_is_dtd;
}

int32_t edid_t::dtd_timing_t::vert_image_size() {
    if (f_vert_image_size)
        return m_vert_image_size;
    n_vert_image_size = true;
    if (is_dtd()) {
        n_vert_image_size = false;
        m_vert_image_size = (vert_image_size_8lsbits() | (vert_image_size_4msbits() << 8));
    }
    f_vert_image_size = true;
    return m_vert_image_size;
}

int32_t edid_t::mfg_year() {
    if (f_mfg_year)
        return m_mfg_year;
    m_mfg_year = (mfg_year_mod() + 1990);
    f_mfg_year = true;
    return m_mfg_year;
}

int32_t edid_t::mfg_id_ch1() {
    if (f_mfg_id_ch1)
        return m_mfg_id_ch1;
    m_mfg_id_ch1 = ((mfg_bytes() & 31744) >> 10);
    f_mfg_id_ch1 = true;
    return m_mfg_id_ch1;
}

int32_t edid_t::mfg_id_ch3() {
    if (f_mfg_id_ch3)
        return m_mfg_id_ch3;
    m_mfg_id_ch3 = (mfg_bytes() & 31);
    f_mfg_id_ch3 = true;
    return m_mfg_id_ch3;
}

double edid_t::gamma() {
    if (f_gamma)
        return m_gamma;
    n_gamma = true;
    if (gamma_mod() != 255) {
        n_gamma = false;
        m_gamma = ((gamma_mod() + 100) / 100.0);
    }
    f_gamma = true;
    return m_gamma;
}

int32_t edid_t::mfg_id_ch2() {
    if (f_mfg_id_ch2)
        return m_mfg_id_ch2;
    m_mfg_id_ch2 = ((mfg_bytes() & 992) >> 5);
    f_mfg_id_ch2 = true;
    return m_mfg_id_ch2;
}
