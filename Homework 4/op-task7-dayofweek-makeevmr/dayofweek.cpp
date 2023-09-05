#include <iostream>


bool leap_year(int year) {
    if (year % 4 == 0) {
        if (year % 100 != 0) {
            return true;
        }
        if (year % 400 == 0) {
            return true;
        }
        return false;
    }
    return false;
}

void date_checker(const char *gregorian_date) {
    const char *gregorian_date_copy = gregorian_date;
    int dot_counter = 0;
    int gregorian_date_index = -1;
    int dot_1_index = -1;
    int dot_2_index = -1;
    while (*gregorian_date != '\0') {
        ++gregorian_date_index;
        if (*gregorian_date == '.') {
            dot_counter += 1;
            if (dot_1_index == -1) {
                dot_1_index = gregorian_date_index;
            } else if (dot_2_index == -1) {
                dot_2_index = gregorian_date_index;
            }
        }
        ++gregorian_date;
    }
    if (dot_counter != 2) {
        throw "Unknown";
    }
    if (dot_1_index != 1 && dot_1_index != 2) {
        throw "Unknown";
    }
    if (dot_2_index - dot_1_index - 1 != 1 && dot_2_index - dot_1_index - 1 != 2) {
        throw "Unknown";
    }
    if (gregorian_date_index - dot_2_index > 4) {
        throw "Unknown";
    }
    int day = 0;
    int day_power = 1;
    for (int i = dot_1_index - 1; i >= 0; --i) {
        day += static_cast<int>(gregorian_date_copy[i] - 48) * day_power;
        day_power *= 10;
    }
    int month = 0;
    int month_power = 1;
    for (int j = dot_2_index - 1; j > dot_1_index; --j) {
        month += static_cast<int>(gregorian_date_copy[j] - 48) * month_power;
        month_power *= 10;
    }
    int year = 0;
    int year_power = 1;
    for (int k = gregorian_date_index; k > dot_2_index; --k) {
        year += static_cast<int>(gregorian_date_copy[k] - 48) * year_power;
        year_power *= 10;
    }
    if (day < 1 || day > 31) {
        throw "Unknown";
    }
    if (month < 1 || month > 12) {
        throw "Unknown";
    }
    if (day == 29 && month == 2) {
        if (!leap_year(year)) {
            throw "Unknown";
        }
    }
}


int64_t JDN_calculator(int64_t day, int64_t month, int64_t year) {
    int64_t a = (14 - month) / 12;
    int64_t y = year + 4800 - a;
    int64_t m = month + 12 * a - 3;
    int64_t JDN = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return JDN;
}

void day_of_week(const char *gregorian) {
    char str_day[3];
    int str_day_index = 0;
    while (*gregorian != '.') {
        str_day[str_day_index] = *gregorian;
        ++gregorian;
        ++str_day_index;
    }
    ++gregorian;
    str_day[str_day_index] = '\0';
    int day = atoi(str_day);
    char str_month[3];
    int str_month_index = 0;
    while (*gregorian != '.') {
        str_month[str_month_index] = *gregorian;
        ++gregorian;
        ++str_month_index;
    }
    ++gregorian;
    str_month[str_month_index] = '\0';
    int month = atoi(str_month);
    char str_year[5];
    int str_year_index = 0;
    while (*gregorian != '\0') {
        str_year[str_year_index] = *gregorian;
        ++gregorian;
        ++str_year_index;
    }
    str_year[str_year_index] = '\0';
    int year = atoi(str_year);
    int64_t JDN = JDN_calculator(day, month, year);
    switch (JDN % 7) {
        case 0:
            std::cout << "Monday" << std::endl;
            break;
        case 1:
            std::cout << "Tuesday" << std::endl;
            break;
        case 2:
            std::cout << "Wednesday" << std::endl;
            break;
        case 3:
            std::cout << "Thursday" << std::endl;
            break;
        case 4:
            std::cout << "Friday" << std::endl;
            break;
        case 5:
            std::cout << "Saturday" << std::endl;
            break;
        case 6:
            std::cout << "Sunday" << std::endl;
            break;
    }
    ++year;
    if (day == 29 && month == 2) {
        while (!leap_year(year) || (JDN_calculator(day, month, year) % 7 != 4)) {
            ++year;
        }
    } else {
        while ((JDN_calculator(day, month, year)) % 7 != 4) {
            ++year;
        }
    }
    std::cout << year;
}

int main() {
    char gregorian_date[11];
    std::cin >> gregorian_date;
    try {
        date_checker(gregorian_date);
        day_of_week(gregorian_date);
    }
    catch (const char *error) {
        std::cout << error << std::endl;
    }
    return 0;
}