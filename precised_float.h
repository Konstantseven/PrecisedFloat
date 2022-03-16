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


    template<typename T>
    using enable_if_arithmetic_t = typename std::enable_if<std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, bool>::type;
    template<typename T>
    using enable_if_integer_t = typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, bool>::value, bool>::type;
    template<typename T>
    using enable_if_floating_point_t = typename std::enable_if<std::is_floating_point<T>::value, bool>::type;


    friend class std::numeric_limits<PrecisedFloat>;


    static constexpr magnitude_t MAGNITUDE_ORDER_LIMIT = std::numeric_limits<mantissa_t>::digits10 - 1;


    PrecisedFloat() = default;
    explicit PrecisedFloat(const std::string& s);
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    explicit PrecisedFloat(const T n);


    PrecisedFloat& operator=(const std::string& s);
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    PrecisedFloat& operator=(const T n);


    PrecisedFloat& operator+=(const PrecisedFloat& pf) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    PrecisedFloat& operator+=(const T n) noexcept;
    PrecisedFloat operator+(const PrecisedFloat& pf) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator+(const PrecisedFloat& lhs, const T rhs) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator+(const T lhs, const PrecisedFloat& rhs) noexcept;


    PrecisedFloat& operator-=(const PrecisedFloat& pf) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    PrecisedFloat& operator-=(const T n) noexcept;
    PrecisedFloat operator-(const PrecisedFloat& pf) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator-(const PrecisedFloat& lhs, const T rhs) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator-(const T lhs, const PrecisedFloat& rhs) noexcept;


    PrecisedFloat& operator*=(const PrecisedFloat& pf) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    PrecisedFloat& operator*=(const T n) noexcept;
    PrecisedFloat operator*(const PrecisedFloat& pf) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator*(const PrecisedFloat& lhs, const T rhs) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator*(const T lhs, const PrecisedFloat& rhs) noexcept;


    PrecisedFloat& operator/=(const PrecisedFloat& pf) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T> = true>
    PrecisedFloat& operator/=(const T n) noexcept;
    PrecisedFloat operator/(const PrecisedFloat& pf) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator/(const PrecisedFloat& lhs, const T rhs) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend PrecisedFloat operator/(const T lhs, const PrecisedFloat& rhs) noexcept;


    bool operator==(const PrecisedFloat& pf) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator==(const PrecisedFloat& lhs, const T rhs) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator==(const T lhs, const PrecisedFloat& rhs) noexcept;


    bool operator!=(const PrecisedFloat& pf) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator!=(const PrecisedFloat& lhs, const T rhs) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator!=(const T lhs, const PrecisedFloat& rhs) noexcept;


    bool operator<(const PrecisedFloat& pf) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator<(const PrecisedFloat& lhs, const T rhs) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator<(const T lhs, const PrecisedFloat& rhs) noexcept;


    bool operator>(const PrecisedFloat& pf) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator>(const PrecisedFloat& lhs, const T rhs) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator>(const T lhs, const PrecisedFloat& rhs) noexcept;


    bool operator<=(const PrecisedFloat& pf) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator<=(const PrecisedFloat& lhs, const T rhs) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator<=(const T lhs, const PrecisedFloat& rhs) noexcept;


    bool operator>=(const PrecisedFloat& pf) const noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator>=(const PrecisedFloat& lhs, const T rhs) noexcept;
    template<typename T,
             enable_if_arithmetic_t<T>>
    friend bool operator>=(const T lhs, const PrecisedFloat& rhs) noexcept;


    template<typename T,
             enable_if_arithmetic_t<T> = true>
    explicit operator T() const noexcept;

    std::string str() const noexcept;

    PrecisedFloat& precise(const std::size_t precision = 6) noexcept;
    PrecisedFloat& round(const std::size_t precision = 6) noexcept;
    PrecisedFloat& round_up(const std::size_t precision = 6) noexcept;
    PrecisedFloat& round_down(const std::size_t precision = 6) noexcept;

    bool is_nan() const noexcept;

private:
    enum class State {
        NaN = -1,
        NEGATIVE,
        POSITIVE
    };


    explicit constexpr PrecisedFloat(const State s, const magnitude_t mg, const mantissa_t mn) : state{s},
                                                                                                 magnitude_order{mg},
                                                                                                 mantissa{mn}
                                                                                                 { };


    static constexpr char ZERO_CHAR     = '0';
    static constexpr char DOT_CHAR      = '.';
    static constexpr char MINUS_CHAR    = '-';


    void set_from(const std::string& float_as_string);
    template<typename T,
             enable_if_integer_t<T> = true>
    void set_from(const T integer) noexcept;
    template<typename T,
             enable_if_floating_point_t<T> = true>
    void set_from(const T floating_point) noexcept;
    void make_addition(const PrecisedFloat& pf) noexcept;
    void make_subtraction(const PrecisedFloat& pf) noexcept;
    void switch_sign() noexcept;
    void set_nan() noexcept;


    int char_to_int(const char c) const noexcept;


    State          state              = State::NaN;
    magnitude_t    magnitude_order    = 0;
    mantissa_t     mantissa           = 0;
};


PrecisedFloat::PrecisedFloat(const std::string& s) {
    set_from(s);
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat::PrecisedFloat(const T n) {
    set_from(n);
}


PrecisedFloat& PrecisedFloat::operator=(const std::string& s) {
    set_from(s);

    return *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat& PrecisedFloat::operator=(const T n) {
    set_from(n);

    return *this;
}


PrecisedFloat& PrecisedFloat::operator+=(const PrecisedFloat& pf) noexcept {
    if (pf.state == State::NaN)
        set_nan();
    else if (state == pf.state)
        make_addition(pf);
    else if (state != State::NaN)
        make_subtraction(pf);

    return *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat& PrecisedFloat::operator+=(const T n) noexcept {
    return *this += PrecisedFloat{n};
}

PrecisedFloat PrecisedFloat::operator+(const PrecisedFloat& pf) const noexcept {
    PrecisedFloat tpf{*this};
    tpf += pf;

    return tpf;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator+(const PrecisedFloat& lhs, const T rhs) noexcept {
    PrecisedFloat pf{rhs};
    pf += lhs;

    return pf;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator+(const T lhs, const PrecisedFloat& rhs) noexcept {
    PrecisedFloat pf{lhs};
    pf += rhs;

    return pf;
}


PrecisedFloat& PrecisedFloat::operator-=(const PrecisedFloat& pf) noexcept {
    if (pf.state == State::NaN)
        set_nan();
    else if (state == pf.state)
        make_subtraction(pf);
    else if (state != State::NaN)
        make_addition(pf);

    return *this;

}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat& PrecisedFloat::operator-=(const T n) noexcept {
    return *this -= PrecisedFloat{n};
}

PrecisedFloat PrecisedFloat::operator-(const PrecisedFloat& pf) const noexcept {
    PrecisedFloat tpf{ *this };
    tpf -= pf;

    return tpf;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator-(const PrecisedFloat& lhs, const T rhs) noexcept {
    PrecisedFloat pf{rhs};
    pf -= lhs;

    return pf;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator-(const T lhs, const PrecisedFloat& rhs) noexcept {
    PrecisedFloat pf{lhs};
    pf -= rhs;

    return pf;
}


PrecisedFloat& PrecisedFloat::operator*=(const PrecisedFloat& pf) noexcept {
    if (pf.state == State::NaN) {
        set_nan();
        return *this;
    }
    else if (state == State::NaN) {
        return *this;
    }
    else if (pf.state == State::NEGATIVE) {
        switch_sign();
    }

    mantissa *= pf.mantissa;
    magnitude_order += pf.magnitude_order;

    return *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat& PrecisedFloat::operator*=(const T n) noexcept {
    return *this *= PrecisedFloat{n};
}

PrecisedFloat PrecisedFloat::operator*(const PrecisedFloat& pf) const noexcept {
    PrecisedFloat tpf{ *this };
    tpf *= pf;

    return tpf;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator*(const PrecisedFloat& lhs, const T rhs) noexcept {
    PrecisedFloat pf{rhs};
    pf *= lhs;

    return pf;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator*(const T lhs, const PrecisedFloat& rhs) noexcept {
    PrecisedFloat pf{lhs};
    pf *= rhs;

    return pf;
}


PrecisedFloat& PrecisedFloat::operator/=(const PrecisedFloat& pf) noexcept {
    if (state == State::NaN || mantissa == 0) {
        return *this;
    }
    else if (pf.state == State::NaN || pf.mantissa == 0) {
        set_nan();
        return *this;
    }

    PrecisedFloat tpf;

    tpf.state = state;
    if (pf.state == State::NEGATIVE) {
        tpf.switch_sign();
    }

    auto o_mantissa = pf.mantissa;

    const auto magnitude_order_diff = std::abs(magnitude_order - pf.magnitude_order);
    const auto mantissa_shift = std::pow(10, magnitude_order_diff);
    if (magnitude_order < pf.magnitude_order) {
        mantissa *= mantissa_shift;
    }
    else {
        o_mantissa *= mantissa_shift;
    }

    while (mantissa >= o_mantissa) {
        mantissa -= o_mantissa;
        ++tpf.mantissa;
    }

    while (mantissa != 0 && tpf.magnitude_order < MAGNITUDE_ORDER_LIMIT) {
        mantissa *= 10;

        const magnitude_t remainder = mantissa / o_mantissa;
        tpf.mantissa = tpf.mantissa * 10 + remainder;

        mantissa -= o_mantissa * remainder;
        ++tpf.magnitude_order;
    }

    return *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat & PrecisedFloat::operator/=(const T n) noexcept {
    return *this /= PrecisedFloat{n};
}

PrecisedFloat PrecisedFloat::operator/(const PrecisedFloat& pf) const noexcept {
    PrecisedFloat tpf{ *this };
    tpf /= pf;

    return tpf;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator/(const PrecisedFloat& lhs, const T rhs) noexcept {
    PrecisedFloat pf{lhs};
    pf /= rhs;

    return pf;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
PrecisedFloat operator/(const T lhs, const PrecisedFloat& rhs) noexcept {
    PrecisedFloat pf{lhs};
    pf /= rhs;

    return pf;
}


bool PrecisedFloat::operator==(const PrecisedFloat& pf) const noexcept {
    return state == pf.state
        && magnitude_order == pf.magnitude_order
        && mantissa == pf.mantissa;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator==(const PrecisedFloat& lhs, const T rhs) noexcept {
    return lhs == PrecisedFloat{rhs};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator==(const T lhs, const PrecisedFloat& rhs) noexcept {
    return PrecisedFloat{lhs} == rhs;
}


bool PrecisedFloat::operator!=(const PrecisedFloat& pf) const noexcept {
    return !(*this == pf);
}
template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator!=(const PrecisedFloat& lhs, const T rhs) noexcept {
    return lhs != PrecisedFloat{rhs};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator!=(const T lhs, const PrecisedFloat& rhs) noexcept {
    return PrecisedFloat{lhs} != rhs;
}


bool PrecisedFloat::operator<(const PrecisedFloat& pf) const noexcept {
    if (*this == pf || state == State::NaN || pf.state == State::NaN)
        return false;

    if (state != pf.state)
        return state == State::NEGATIVE;

    return (*this - pf).state == State::NEGATIVE;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator<(const PrecisedFloat& lhs, const T rhs) noexcept {
    return lhs < PrecisedFloat{rhs};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator<(const T lhs, const PrecisedFloat& rhs) noexcept {
    return PrecisedFloat{lhs} != rhs;
}


bool PrecisedFloat::operator>(const PrecisedFloat& pf) const noexcept {
    return pf < *this;
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator>(const PrecisedFloat& lhs, const T rhs) noexcept {
    return lhs > PrecisedFloat{rhs};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator>(const T lhs, const PrecisedFloat& rhs) noexcept {
    return PrecisedFloat{lhs} > rhs;
}


bool PrecisedFloat::operator<=(const PrecisedFloat& pf) const noexcept {
    return !(pf < *this);
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator<=(const PrecisedFloat& lhs, const T rhs) noexcept {
    return lhs <= PrecisedFloat{rhs};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator<=(const T lhs, const PrecisedFloat& rhs) noexcept {
    return PrecisedFloat{lhs} <= rhs;
}


bool PrecisedFloat::operator>=(const PrecisedFloat& pf) const noexcept {
    return !(*this < pf);
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator>=(const PrecisedFloat& lhs, const T rhs) noexcept {
    return lhs >= PrecisedFloat{rhs};
}

template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T> = true>
bool operator>=(const T lhs, const PrecisedFloat& rhs) noexcept {
    return PrecisedFloat{lhs} >= rhs;
}


template<typename T,
         PrecisedFloat::enable_if_arithmetic_t<T>>
PrecisedFloat::operator T() const noexcept {
    return static_cast<T>(mantissa) / std::pow(10, magnitude_order);
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
    constexpr auto BUFFER_MAX_LENGTH = std::numeric_limits<T>::max_exponent10 + 20;
    constexpr auto FORMAT = std::is_same<long double, T>::value ? "%.*Lf" : "%.*f";
    constexpr auto MAX_PRECISION = std::numeric_limits<T>::digits10;

    char buffer[BUFFER_MAX_LENGTH];
    const auto buffer_lenght = std::snprintf(buffer, BUFFER_MAX_LENGTH, FORMAT, MAX_PRECISION, floating_point);

    set_from(std::string(buffer, buffer_lenght));
}

std::string PrecisedFloat::str() const noexcept {
    std::string float_as_string;

    if (state == State::NaN) {
        float_as_string = "NaN";
    }
    else {
        float_as_string = std::to_string(mantissa);

        if (magnitude_order == 0) {
            float_as_string.append(".0");
        }
        else {
            if (float_as_string.size() <= magnitude_order) {
                // Additional zero is added to become the part before dot delimiter
                const auto leading_zeros_number = magnitude_order - float_as_string.size() + 1;
                float_as_string.insert(0, leading_zeros_number, ZERO_CHAR);
            }

            const auto dot_position = float_as_string.size() - magnitude_order;
            float_as_string.insert(dot_position, 1, DOT_CHAR);
        }

        if (state == State::NEGATIVE) {
            float_as_string.insert(0, 1, MINUS_CHAR);
        }
    }

    return float_as_string;
}

void PrecisedFloat::make_addition(const PrecisedFloat& f) noexcept {
    if (magnitude_order == f.magnitude_order) {
        mantissa += f.mantissa;

        return;
    }

    const auto magnitude_order_diff = std::abs(magnitude_order - f.magnitude_order);
    const auto mantissa_shift = std::pow(10, magnitude_order_diff);
    if (magnitude_order < f.magnitude_order) {
        magnitude_order = f.magnitude_order;

        mantissa = mantissa * mantissa_shift + f.mantissa;
    }
    else {
        mantissa += f.mantissa * mantissa_shift;
    }
}

void PrecisedFloat::make_subtraction(const PrecisedFloat& f) noexcept {
    const auto compare_and_process = [this](const mantissa_t mantissa, const mantissa_t f_mantissa) -> mantissa_t {
        if (mantissa < f_mantissa) {
            switch_sign();
            return f_mantissa - mantissa;
        }

        return mantissa - f_mantissa;
    };

    if (magnitude_order == f.magnitude_order) {
        mantissa = compare_and_process(mantissa, f.mantissa);

        return;
    }

    const auto magnitude_order_diff = std::abs(magnitude_order - f.magnitude_order);
    const auto mantissa_shift = std::pow(10, magnitude_order_diff);
    if (magnitude_order < f.magnitude_order) {
        magnitude_order = f.magnitude_order;
        mantissa *= mantissa_shift;

        mantissa = compare_and_process(mantissa, f.mantissa);
    }
    else {
        const auto f_mantissa = f.mantissa * mantissa_shift;

        mantissa = compare_and_process(mantissa, f_mantissa);
    }
}

void PrecisedFloat::switch_sign() noexcept {
    state = state == State::POSITIVE ? State::NEGATIVE : State::POSITIVE;
    if (state == State::POSITIVE)
        state = State::NEGATIVE;
    else if (state == State::NEGATIVE)
        state = State::POSITIVE;
}

void PrecisedFloat::set_nan() noexcept {
    state = State::NaN;
    magnitude_order = 0;
    mantissa = 0;
}

int PrecisedFloat::char_to_int(const char c) const noexcept {
    return c - ZERO_CHAR;
}

PrecisedFloat& PrecisedFloat::precise(const std::size_t precision) noexcept {
    if (magnitude_order <= precision || state == State::NaN)
        return *this;

    mantissa /= std::pow(10, magnitude_order - precision);
    --mantissa;

    magnitude_order = precision;

    // Common part - may be moved to the separate function
    while (mantissa % 10 == 0 && mantissa != 0) {
        mantissa /= 10;
        --magnitude_order;
    }

    return *this;
}

PrecisedFloat& PrecisedFloat::round(const std::size_t precision) noexcept {
    if (magnitude_order <= precision || state == State::NaN)
        return *this;

    mantissa /= std::pow(10, magnitude_order - precision + 1);
    bool round_up = mantissa % 10 >= 5;
    mantissa /= 10;
    if (round_up)
        ++mantissa;

    magnitude_order = precision;

    // Common part - may be moved to the separate function
    while (mantissa % 10 == 0 && mantissa != 0) {
        mantissa /= 10;
        magnitude_order--;
    }

    return *this;
}

PrecisedFloat& PrecisedFloat::round_up(const std::size_t precision) noexcept {
    if (magnitude_order <= precision || state == State::NaN)
        return *this;

    mantissa /= std::pow(10, magnitude_order - precision);
    ++mantissa;

    magnitude_order = precision;

    // Common part - may be moved to the separate function
    while (mantissa % 10 == 0 && mantissa != 0) {
        mantissa /= 10;
        magnitude_order--;
    }
    return *this;
}

PrecisedFloat& PrecisedFloat::round_down(const std::size_t precision) noexcept {
    return precise(precision);
}

bool PrecisedFloat::is_nan() const noexcept {
    return state == State::NaN;
}

void PrecisedFloat::set_from(const std::string& string_float) {
    auto it = string_float.cbegin();

    if (*it == MINUS_CHAR) {
        state = State::NEGATIVE;
        ++it;
    }
    else if (std::isdigit(*it)) {
        state = State::POSITIVE;
    }
    else {
        return;
    }

    const auto count_trailing_zeros = [](const std::string& string_float) -> std::size_t {
        std::size_t zeros = 0;
        for (auto it = string_float.crbegin(); *it == ZERO_CHAR && it + 1 != string_float.crend() && *(it + 1) != DOT_CHAR; ++it) {
            ++zeros;
        }

        return zeros;
    };

    bool dot_is_found = false;
    const auto end_without_zeros = string_float.cend() - count_trailing_zeros(string_float);
    for (; it < end_without_zeros; ++it) {
        if (*it == DOT_CHAR) {
            if (dot_is_found || it + 1 == end_without_zeros) { // problematic case 0.0000000
                set_nan();
                break;
            }
            dot_is_found = true;
            continue;
        }
        if (dot_is_found) {
            ++magnitude_order;
        }

        if (!std::isdigit(*it)) {
            set_nan();
            break;
        }

        mantissa = mantissa * 10 + char_to_int(*it);
    }
}



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
            return order_limit > 0 ? mantissa_upper_bound_max(order_limit - 1) * 10 : 10;
        }
    };
} // namespace std

#endif // __PRECISED_FLOAT_H__
