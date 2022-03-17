#ifndef __PRECISED_FLOAT_H__
#define __PRECISED_FLOAT_H__


#include <string>
#include <limits>
#include <utility>
#include <cmath>


class PrecisedFloat {
public:
    using mantissa_t    = unsigned long long;
    using magnitude_t   = unsigned short;
    using precision_t   = unsigned short;


    template<typename T>
    using enable_if_arithmetic_t = typename std::enable_if<std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, bool>::type;
    template<typename T>
    using enable_if_integer_t = typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, bool>::value, bool>::type;
    template<typename T>
    using enable_if_floating_point_t = typename std::enable_if<std::is_floating_point<T>::value, bool>::type;


    friend class std::numeric_limits<PrecisedFloat>;


    static constexpr magnitude_t MAGNITUDE_ORDER_LIMIT = std::numeric_limits<mantissa_t>::digits10 - 1;


    PrecisedFloat() = default;
    explicit PrecisedFloat(const std::string& string);
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    explicit PrecisedFloat(const T number);


    PrecisedFloat& operator=(const std::string& string);
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    PrecisedFloat& operator=(const T number);


    PrecisedFloat& operator+=(const PrecisedFloat& other) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    PrecisedFloat& operator+=(const T number) noexcept;
    PrecisedFloat operator+(const PrecisedFloat& other) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator+(const PrecisedFloat& p_float, const T number) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator+(const T number, const PrecisedFloat& p_float) noexcept;


    PrecisedFloat& operator-=(const PrecisedFloat& other) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    PrecisedFloat& operator-=(const T number) noexcept;
    PrecisedFloat operator-(const PrecisedFloat& other) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator-(const PrecisedFloat& p_float, const T number) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator-(const T number, const PrecisedFloat& p_float) noexcept;


    PrecisedFloat& operator*=(const PrecisedFloat& other) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    PrecisedFloat& operator*=(const T number) noexcept;
    PrecisedFloat operator*(const PrecisedFloat& other) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator*(const PrecisedFloat& p_float, const T number) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator*(const T number, const PrecisedFloat& p_float) noexcept;


    PrecisedFloat& operator/=(const PrecisedFloat& other) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    PrecisedFloat& operator/=(const T number) noexcept;
    PrecisedFloat operator/(const PrecisedFloat& other) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator/(const PrecisedFloat& p_float, const T number) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator/(const T number, const PrecisedFloat& p_float) noexcept;


    bool operator==(const PrecisedFloat& other) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator==(const PrecisedFloat& p_float, const T number) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator==(const T number, const PrecisedFloat& p_float) noexcept;


    bool operator!=(const PrecisedFloat& other) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator!=(const PrecisedFloat& p_float, const T number) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator!=(const T number, const PrecisedFloat& p_float) noexcept;


    bool operator<(const PrecisedFloat& other) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator<(const PrecisedFloat& p_float, const T number) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator<(const T number, const PrecisedFloat& p_float) noexcept;


    bool operator>(const PrecisedFloat& other) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator>(const PrecisedFloat& p_float, const T number) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator>(const T number, const PrecisedFloat& p_float) noexcept;


    bool operator<=(const PrecisedFloat& other) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator<=(const PrecisedFloat& p_float, const T number) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator<=(const T number, const PrecisedFloat& p_float) noexcept;


    bool operator>=(const PrecisedFloat& other) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator>=(const PrecisedFloat& p_float, const T number) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator>=(const T number, const PrecisedFloat& p_float) noexcept;


    template<typename T,
             enable_if_arithmetic_t<T> = true>
    explicit operator T() const noexcept;


    std::string str() const noexcept;


    PrecisedFloat& precise(const precision_t precision = 6) noexcept;
    PrecisedFloat& round(const precision_t precision = 6) noexcept;
    PrecisedFloat& round_up(const precision_t precision = 6) noexcept;
    PrecisedFloat& round_down(const precision_t precision = 6) noexcept;


    bool is_nan() const noexcept;

private:
    enum class State {
        NaN = -1,
        NEGATIVE,
        POSITIVE
    };


    static constexpr char ZERO_CHAR     = '0';
    static constexpr char DOT_CHAR      = '.';
    static constexpr char MINUS_CHAR    = '-';


    explicit constexpr PrecisedFloat(const State state, const magnitude_t magnitude_order, const mantissa_t mantissa) : state{state},
                                                                                                                        magnitude_order{magnitude_order},
                                                                                                                        mantissa{mantissa}
                                                                                                                        {};


    void set_from(const std::string& string);
    template<typename T,
             enable_if_integer_t<T> = true>
    void set_from(const T integer) noexcept;
    template<typename T,
             enable_if_floating_point_t<T> = true>
    void set_from(const T floating_point) noexcept;
    void make_addition(const PrecisedFloat& p_float) noexcept;
    void make_subtraction(const PrecisedFloat& p_float) noexcept;
    void switch_sign() noexcept;
    void set_nan() noexcept;


    int char_to_int(const char c) const noexcept;


    State          state              = State::NaN;
    magnitude_t    magnitude_order    = 0;
    mantissa_t     mantissa           = 0;
};


namespace std {
    template<>
    struct numeric_limits<PrecisedFloat> {
        static constexpr bool                  is_specialized       = true;
        static constexpr bool                  is_signed            = true;
        static constexpr bool                  is_integer           = false;
        static constexpr bool                  is_exact             = true;
        static constexpr int                   radix                = 10;
        static constexpr int                   min_exponent         = -PrecisedFloat::MAGNITUDE_ORDER_LIMIT;
        static constexpr int                   min_exponent10       = -PrecisedFloat::MAGNITUDE_ORDER_LIMIT;
        static constexpr int                   max_exponent         = PrecisedFloat::MAGNITUDE_ORDER_LIMIT;
        static constexpr int                   max_exponent10       = PrecisedFloat::MAGNITUDE_ORDER_LIMIT;
        static constexpr bool                  has_infinity         = true;
        static constexpr bool                  has_quiet_NaN        = true;
        static constexpr bool                  has_signaling_NaN    = false;
        static constexpr float_denorm_style    has_denorm           = denorm_absent;
        static constexpr bool                  has_denorm_loss      = false;
        static constexpr bool                  is_iec559            = false;
        static constexpr bool                  is_bounded           = true;
        static constexpr bool                  is_modulo            = false;
        static constexpr bool                  traps                = true;
        static constexpr bool                  tinyness_before      = false;
        static constexpr float_round_style     round_style          = round_to_nearest;


        static constexpr PrecisedFloat min() noexcept {
            return PrecisedFloat{PrecisedFloat::State::POSITIVE, 0, 0};
        }

        static constexpr PrecisedFloat max() noexcept {
            return PrecisedFloat{PrecisedFloat::State::POSITIVE, 0,
                                 mantissa_upper_bound_max(PrecisedFloat::MAGNITUDE_ORDER_LIMIT) - 1};
        }

        static constexpr PrecisedFloat lowest() noexcept {
            return PrecisedFloat{PrecisedFloat::State::NEGATIVE, 0,
                                 mantissa_upper_bound_max(PrecisedFloat::MAGNITUDE_ORDER_LIMIT) - 1};
        }

        static constexpr PrecisedFloat epsilon() noexcept {
            return PrecisedFloat{PrecisedFloat::State::POSITIVE, 0, 0};
        }

        static constexpr PrecisedFloat round_error() noexcept {
            return PrecisedFloat{PrecisedFloat::State::POSITIVE, 0, 0};
        }

        static constexpr PrecisedFloat infinity() noexcept {
            return PrecisedFloat{PrecisedFloat::State::POSITIVE,
                                 std::numeric_limits<PrecisedFloat::magnitude_t>::max(),
                                 std::numeric_limits<PrecisedFloat::mantissa_t>::max()};
        }

        static constexpr PrecisedFloat quiet_NaN() noexcept {
            return {};
        }

    private:
        static constexpr PrecisedFloat::mantissa_t mantissa_upper_bound_max(const std::size_t order_limit) {
            return order_limit > 0 ? mantissa_upper_bound_max(order_limit - 1) * std::numeric_limits<PrecisedFloat>::radix
                                   : std::numeric_limits<PrecisedFloat>::radix;
        }
    };
} // namespace std


PrecisedFloat::PrecisedFloat(const std::string& string) {
    set_from(string);
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat::PrecisedFloat(const T number) {
    set_from(number);
}


PrecisedFloat& PrecisedFloat::operator=(const std::string& string) {
    set_from(string);

    return *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat& PrecisedFloat::operator=(const T number) {
    set_from(number);

    return *this;
}


PrecisedFloat& PrecisedFloat::operator+=(const PrecisedFloat& other) noexcept {
    if (other.state == State::NaN) {
        set_nan();
    } else if (state == other.state) {
        make_addition(other);
    } else if (state != State::NaN) {
        make_subtraction(other);
    }

    return *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat& PrecisedFloat::operator+=(const T number) noexcept {
    return *this += PrecisedFloat{number};
}

PrecisedFloat PrecisedFloat::operator+(const PrecisedFloat& other) const noexcept {
    PrecisedFloat temp_p_float{*this};
    temp_p_float += other;

    return temp_p_float;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator+(const PrecisedFloat& p_float, const T number) noexcept {
    PrecisedFloat temp_p_float{number};
    temp_p_float += p_float;

    return temp_p_float;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator+(const T number, const PrecisedFloat& p_float) noexcept {
    PrecisedFloat temp_p_float{number};
    temp_p_float += p_float;

    return temp_p_float;
}


PrecisedFloat& PrecisedFloat::operator-=(const PrecisedFloat& other) noexcept {
    if (other.state == State::NaN) {
        set_nan();
    } else if (state == other.state) {
        make_subtraction(other);
    } else if (state != State::NaN) {
        make_addition(other);
    }

    return *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat& PrecisedFloat::operator-=(const T number) noexcept {
    return *this -= PrecisedFloat{number};
}

PrecisedFloat PrecisedFloat::operator-(const PrecisedFloat& other) const noexcept {
    PrecisedFloat temp_p_float{*this};
    temp_p_float -= other;

    return temp_p_float;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator-(const PrecisedFloat& p_float, const T number) noexcept {
    PrecisedFloat temp_p_float{number};
    temp_p_float -= p_float;

    return temp_p_float;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator-(const T number, const PrecisedFloat& p_float) noexcept {
    PrecisedFloat temp_p_float{number};
    temp_p_float -= p_float;

    return temp_p_float;
}


PrecisedFloat& PrecisedFloat::operator*=(const PrecisedFloat& other) noexcept {
    if (other.state == State::NaN) {
        set_nan();
        return *this;
    }
    else if (state == State::NaN) {
        return *this;
    }
    else if (other.state == State::NEGATIVE) {
        switch_sign();
    }

    mantissa *= other.mantissa;
    magnitude_order += other.magnitude_order;

    return *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat& PrecisedFloat::operator*=(const T number) noexcept {
    return *this *= PrecisedFloat{number};
}

PrecisedFloat PrecisedFloat::operator*(const PrecisedFloat& other) const noexcept {
    PrecisedFloat temp_p_float{*this};
    temp_p_float *= other;

    return temp_p_float;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator*(const PrecisedFloat& p_float, const T number) noexcept {
    PrecisedFloat temp_p_float{number};
    temp_p_float *= p_float;

    return temp_p_float;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator*(const T number, const PrecisedFloat& p_float) noexcept {
    PrecisedFloat temp_p_float{number};
    temp_p_float *= p_float;

    return temp_p_float;
}


PrecisedFloat& PrecisedFloat::operator/=(const PrecisedFloat& other) noexcept {
    if (state == State::NaN || mantissa == 0) {
        return *this;
    } else if (other.state == State::NaN || other.mantissa == 0) {
        set_nan();
        return *this;
    }

    PrecisedFloat temp_p_float;

    temp_p_float.state = state;
    if (other.state == State::NEGATIVE) {
        temp_p_float.switch_sign();
    }

    auto temp_p_float_mantissa = other.mantissa;

    const auto magnitude_order_diff = std::abs(magnitude_order - other.magnitude_order);
    const auto mantissa_shift = std::pow(std::numeric_limits<PrecisedFloat>::radix, magnitude_order_diff);
    if (magnitude_order < other.magnitude_order) {
        mantissa *= mantissa_shift;
    } else {
        temp_p_float_mantissa *= mantissa_shift;
    }

    while (mantissa >= temp_p_float_mantissa) {
        mantissa -= temp_p_float_mantissa;
        ++temp_p_float.mantissa;
    }

    while (mantissa != 0 && temp_p_float.magnitude_order < MAGNITUDE_ORDER_LIMIT) {
        mantissa *= std::numeric_limits<PrecisedFloat>::radix;

        const auto remainder = mantissa / temp_p_float_mantissa;
        temp_p_float.mantissa = temp_p_float.mantissa * std::numeric_limits<PrecisedFloat>::radix + remainder;

        mantissa -= temp_p_float_mantissa * remainder;
        ++temp_p_float.magnitude_order;
    }

    return *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat & PrecisedFloat::operator/=(const T number) noexcept {
    return *this /= PrecisedFloat{number};
}

PrecisedFloat PrecisedFloat::operator/(const PrecisedFloat& other) const noexcept {
    PrecisedFloat temp_p_float{*this};
    temp_p_float /= other;

    return temp_p_float;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator/(const PrecisedFloat& p_float, const T number) noexcept {
    PrecisedFloat temp_p_float{p_float};
    temp_p_float /= number;

    return temp_p_float;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator/(const T number, const PrecisedFloat& p_float) noexcept {
    PrecisedFloat temp_p_float{number};
    temp_p_float /= p_float;

    return temp_p_float;
}


bool PrecisedFloat::operator==(const PrecisedFloat& other) const noexcept {
    return state == other.state &&
           magnitude_order == other.magnitude_order &&
           mantissa == other.mantissa;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator==(const PrecisedFloat& p_float, const T number) noexcept {
    return p_float == PrecisedFloat{number};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator==(const T number, const PrecisedFloat& p_float) noexcept {
    return PrecisedFloat{number} == p_float;
}


bool PrecisedFloat::operator!=(const PrecisedFloat& other) const noexcept {
    return !(*this == other);
}
template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator!=(const PrecisedFloat& p_float, const T number) noexcept {
    return p_float != PrecisedFloat{number};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator!=(const T number, const PrecisedFloat& p_float) noexcept {
    return PrecisedFloat{number} != p_float;
}


bool PrecisedFloat::operator<(const PrecisedFloat& other) const noexcept {
    if (*this == other || state == State::NaN || other.state == State::NaN) {
        return false;
    }

    if (state != other.state) {
        return state == State::NEGATIVE;
    }

    return (*this - other).state == State::NEGATIVE;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator<(const PrecisedFloat& p_float, const T number) noexcept {
    return p_float < PrecisedFloat{number};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator<(const T number, const PrecisedFloat& p_float) noexcept {
    return PrecisedFloat{number} != p_float;
}


bool PrecisedFloat::operator>(const PrecisedFloat& other) const noexcept {
    return other < *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator>(const PrecisedFloat& p_float, const T number) noexcept {
    return p_float > PrecisedFloat{number};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator>(const T number, const PrecisedFloat& p_float) noexcept {
    return PrecisedFloat{number} > p_float;
}


bool PrecisedFloat::operator<=(const PrecisedFloat& other) const noexcept {
    return !(other < *this);
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator<=(const PrecisedFloat& p_float, const T number) noexcept {
    return p_float <= PrecisedFloat{number};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator<=(const T number, const PrecisedFloat& p_float) noexcept {
    return PrecisedFloat{number} <= p_float;
}


bool PrecisedFloat::operator>=(const PrecisedFloat& other) const noexcept {
    return !(*this < other);
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator>=(const PrecisedFloat& p_float, const T number) noexcept {
    return p_float >= PrecisedFloat{number};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator>=(const T number, const PrecisedFloat& p_float) noexcept {
    return PrecisedFloat{number} >= p_float;
}


template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat::operator T() const noexcept {
    return static_cast<T>(mantissa) / std::pow(std::numeric_limits<PrecisedFloat>::radix, magnitude_order);
}

template<typename T,
         PrecisedFloat::enable_if_integer_t<T>>
void PrecisedFloat::set_from(const T integer) noexcept {
    mantissa = integer;
    state = integer < 0 ? State::NEGATIVE : State::POSITIVE;
    magnitude_order = 0;
}


template<typename T,
         PrecisedFloat::enable_if_floating_point_t<T>>
void PrecisedFloat::set_from(const T floating_point) noexcept {
    constexpr auto BUFFER_MAX_LENGTH    = std::numeric_limits<T>::max_exponent10 + 20;
    constexpr auto FORMAT               = std::is_same<long double, T>::value ? "%.*Lf" : "%.*f";
    constexpr auto MAX_PRECISION        = std::numeric_limits<T>::digits10;

    char buffer[BUFFER_MAX_LENGTH];
    const auto buffer_length = std::snprintf(buffer, BUFFER_MAX_LENGTH, FORMAT, MAX_PRECISION, floating_point);

    set_from(std::string(buffer, buffer_length));
}

std::string PrecisedFloat::str() const noexcept {
    std::string string;

    if (state == State::NaN) {
        string = "NaN";
    } else {
        string = std::to_string(mantissa);

        if (magnitude_order == 0) {
            string.append(".0");
        } else {
            if (string.size() <= magnitude_order) {
                const auto zero_number = magnitude_order - string.size() + 1;
                string.insert(0, zero_number, ZERO_CHAR);
            }

            const auto dot_position = string.size() - magnitude_order;
            string.insert(dot_position, 1, DOT_CHAR);
        }

        if (state == State::NEGATIVE) {
            string.insert(0, 1, MINUS_CHAR);
        }
    }

    return string;
}

void PrecisedFloat::make_addition(const PrecisedFloat& p_float) noexcept {
    if (magnitude_order == p_float.magnitude_order) {
        mantissa += p_float.mantissa;

        return;
    }

    const auto magnitude_order_diff = std::abs(magnitude_order - p_float.magnitude_order);
    const auto mantissa_shift = std::pow(std::numeric_limits<PrecisedFloat>::radix, magnitude_order_diff);
    if (magnitude_order < p_float.magnitude_order) {
        magnitude_order = p_float.magnitude_order;

        mantissa = mantissa * mantissa_shift + p_float.mantissa;
    } else {
        mantissa += p_float.mantissa * mantissa_shift;
    }
}

void PrecisedFloat::make_subtraction(const PrecisedFloat& p_float) noexcept {
    const auto compare_mantissas_and_process = [this] (const mantissa_t p_float_mantissa) {
        if (mantissa < p_float_mantissa) {
            switch_sign();
            return p_float_mantissa - mantissa;
        }

        return mantissa - p_float_mantissa;
    };

    if (magnitude_order == p_float.magnitude_order) {
        mantissa = compare_mantissas_and_process(p_float.mantissa);

        return;
    }

    const auto magnitude_order_diff = std::abs(magnitude_order - p_float.magnitude_order);
    const auto mantissa_shift = std::pow(std::numeric_limits<PrecisedFloat>::radix, magnitude_order_diff);
    if (magnitude_order < p_float.magnitude_order) {
        magnitude_order = p_float.magnitude_order;
        mantissa *= mantissa_shift;

        mantissa = compare_mantissas_and_process(p_float.mantissa);
    } else {
        const auto p_float_mantissa = p_float.mantissa * mantissa_shift;

        mantissa = compare_mantissas_and_process(p_float_mantissa);
    }
}

void PrecisedFloat::switch_sign() noexcept {
    if (state == State::POSITIVE) {
        state = State::NEGATIVE;
    } else if (state == State::NEGATIVE) {
        state = State::POSITIVE;
    }
}

void PrecisedFloat::set_nan() noexcept {
    state = State::NaN;
    magnitude_order = 0;
    mantissa = 0;
}

int PrecisedFloat::char_to_int(const char c) const noexcept {
    return c - ZERO_CHAR;
}

PrecisedFloat& PrecisedFloat::precise(const precision_t precision) noexcept {
    if (magnitude_order <= precision || state == State::NaN)
        return *this;

    mantissa /= std::pow(std::numeric_limits<PrecisedFloat>::radix, magnitude_order - precision);
    --mantissa;

    magnitude_order = precision;

    // Common part - may be moved to the separate function
    while (mantissa % std::numeric_limits<PrecisedFloat>::radix == 0 && mantissa != 0) {
        mantissa /= std::numeric_limits<PrecisedFloat>::radix;
        --magnitude_order;
    }

    return *this;
}

PrecisedFloat& PrecisedFloat::round(const precision_t precision) noexcept {
    if (magnitude_order <= precision || state == State::NaN)
        return *this;

    mantissa /= std::pow(std::numeric_limits<PrecisedFloat>::radix, magnitude_order - precision + 1);
    bool round_up = mantissa % std::numeric_limits<PrecisedFloat>::radix >= 5;
    mantissa /= std::numeric_limits<PrecisedFloat>::radix;
    if (round_up)
        ++mantissa;

    magnitude_order = precision;

    // Common part - may be moved to the separate function
    while (mantissa % std::numeric_limits<PrecisedFloat>::radix == 0 && mantissa != 0) {
        mantissa /= std::numeric_limits<PrecisedFloat>::radix;
        magnitude_order--;
    }

    return *this;
}

PrecisedFloat& PrecisedFloat::round_up(const precision_t precision) noexcept {
    if (magnitude_order <= precision || state == State::NaN)
        return *this;

    mantissa /= std::pow(std::numeric_limits<PrecisedFloat>::radix, magnitude_order - precision);
    ++mantissa;

    magnitude_order = precision;

    // Common part - may be moved to the separate function
    while (mantissa % std::numeric_limits<PrecisedFloat>::radix == 0 && mantissa != 0) {
        mantissa /= std::numeric_limits<PrecisedFloat>::radix;
        magnitude_order--;
    }
    return *this;
}

PrecisedFloat& PrecisedFloat::round_down(const precision_t precision) noexcept {
    return precise(precision);
}

bool PrecisedFloat::is_nan() const noexcept {
    return state == State::NaN;
}

void PrecisedFloat::set_from(const std::string& string) {
    auto iterator = string.cbegin();

    if (*iterator == MINUS_CHAR) {
        state = State::NEGATIVE;
        ++iterator;
    }
    else if (std::isdigit(*iterator)) {
        state = State::POSITIVE;
    }
    else {
        return;
    }

    const auto count_trailing_zeros = [] (const std::string& string) -> precision_t {
        precision_t trailing_zeros = 0;
        for (auto iterator = string.crbegin(); *iterator == ZERO_CHAR && iterator + 1 != string.crend() && *(iterator + 1) != DOT_CHAR; ++iterator) {
            ++trailing_zeros;
        }

        return trailing_zeros;
    };

    bool dot_found = false;
    const auto end_without_zeros = string.cend() - count_trailing_zeros(string);
    for (; iterator < end_without_zeros; ++iterator) {
        if (*iterator == DOT_CHAR) {
            if (dot_found || iterator + 1 == end_without_zeros) { // problematic case 0.0000000
                set_nan();
                break;
            }
            dot_found = true;
            continue;
        }

        if (dot_found) {
            ++magnitude_order;
        }

        if (!std::isdigit(*iterator)) {
            set_nan();
            break;
        }

        mantissa = mantissa * std::numeric_limits<PrecisedFloat>::radix + char_to_int(*iterator);
    }
}

#endif // __PRECISED_FLOAT_H__
