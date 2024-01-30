#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <cmath>

const double eps = 0.1E-8;

class Array {
public:
    using size_t = unsigned int;
    using value_t = float;
    using Iterator = value_t*;

    Array(size_t size) : m_size(size) {
        if (size > maxsize()) {
            throw std::range_error("invalid array size");
        }
        m_data = new value_t[size];
    }

    Array(size_t size, value_t default_value) : Array(size) {
        for (auto& element : *this) {
            element = default_value;
        }
    }

    Array(const Iterator begin, const Iterator end) : Array(end - begin) {
        if (begin >= end) {
            throw invalid_iterators("invalid iterators");
        }
        size_t index = 0;
        for (Iterator it = begin; it != end; ++it) {
            m_data[index++] = *it;
        }
    }

    value_t& operator[](size_t index) {
        if (index < m_size) {
            return m_data[index];
        }
        else {
            throw std::out_of_range("array out of range");
        }
    }

    const value_t& operator[](size_t index) const {
        if (index < m_size) {
            return m_data[index];
        }
        else {
            throw std::out_of_range("array out of range");
        }
    }


    size_t size() const { return m_size; }
    static size_t maxsize() { return MAX_SIZE; }






    Array(const Array& array) : Array(array.cbegin(), array.cend()) {}

    ~Array() { delete[] m_data; }

    Array& operator=(const Array& array) {
        if (this != &array) {
            if (size() != array.size()) {
                throw different_sizes("arrays have different sizes");
            }
            for (size_t n = 0; n < size(); ++n) {
                m_data[n] = array[n];
            }
        }
        return *this;
    }

    std::ostream& print(std::ostream& outstream, const char* sep = " ", const char* end = "") const {
        for (int i = 0; i < size(); ++i) {
            outstream << m_data[i];
            if (i != size() - 1) {
                outstream << sep;
            }
        }
        outstream << end;
        return outstream;
    }

    friend std::istream& operator>>(std::istream& instream, Array& array) {
        for (auto& element : array) {
            instream >> element;
        }
        return instream;
    }

    friend std::ostream& operator<<(std::ostream& outstream, const Array& array) {
        for (auto& element : array) {
            outstream << element << " ";
        }
        return outstream;
    }

    Iterator       begin() { return m_data; }
    Iterator       end() { return m_data + m_size; }
    const Iterator begin()  const { return m_data; }
    const Iterator end()    const { return m_data + m_size; }
    const Iterator cbegin() const { return m_data; }
    const Iterator cend()   const { return m_data + m_size; }




    class different_sizes : public std::logic_error {
    public: different_sizes(const char* msg) : logic_error(msg) {}
    };

    class invalid_iterators : public std::invalid_argument {
    public: invalid_iterators(const char* msg) : invalid_argument(msg) {}
    };

private:
    const static size_t MAX_SIZE = 10000;
    const size_t m_size;
    value_t* m_data;
};

class Integral
{
private:
    int size;
    int a, b;
    Array arguments;
    Array values;
public:

    Integral(int size) : size(size), arguments(size), values(size), a(0), b(size - 1) { }

    inline void readArguments()
    {
        std::cin >> arguments;
    }

    inline void readFunctions()
            {
        std::cin >> values;
    }

    inline double trapeciy() {
        double result = 0;
        for (int i = 0; i < size - 1; ++i) {
            double step = arguments[i + 1] - arguments[i];
            result += (values[i] + values[i + 1]) / 2 * step;
        }
        return result;
    }

    inline double Simpson() {
        double integral = 0;
        int intStep = 2;
        double step = intStep * (arguments[b] - arguments[a]) / (size - 1);

        for (int i = 0; i < size - intStep; i += intStep) {
            double a = values[i];
            double b = 4 * values[i + 1];
            double c = values[i + 2];
            integral += (a + b + c) * step / 6;
        }

        return std::round(integral * 10) / 10;
    }

    inline double Newton() {
        double integral = 0;
        int intStep = 3;
        double step = intStep * (arguments[b] - arguments[a]) / (size - 1);
        for (int i = 0; i < size - intStep; i += intStep) {
            double a = values[i];
            double b = 3 * values[i + 1];
            double c = 3 * values[i + 2];
            double d = values[i + 3];
            integral += (a + b + c + d) * step / 8;
        }

        return integral;
    }

    friend std::ostream& operator<<(std::ostream& outstream, const Integral& integral) {

        outstream << "argument " << integral.arguments << "\n"
            << "function " << integral.values;
        return outstream;
    }

    inline double levPriam() {
        double result = 0;
        for (int i = 0; i < size - 1; ++i) {
            double step = arguments[i + 1] - arguments[i];
            result += values[i] * step;
        }
        return result;
    }

    inline double srPriam() {
        double result = 0;
        for (int i = 0; i < size - 1; ++i) {
            double step = arguments[i + 1] - arguments[i];
            result += (values[i] + values[i + 1]) / 2 * step;
        }
        return result;
    }

    inline double pravPriam() {
        double result = 0;
        for (int i = 0; i < size - 1; ++i) {
            double step = arguments[i + 1] - arguments[i];
            result += values[i + 1] * step;
        }
        return result;
    }

};




int main()
{
    int code, size;
    std::cin >> size;
    Integral integral = Integral(size);
    integral.readArguments();
    integral.readFunctions();
    std::cout << "input= " << integral << std::endl;
    std::cout << "lev priam= " << integral.levPriam() << std::endl;
    std::cout << "sr priam= " << integral.srPriam() << std::endl;
    std::cout << "prav priam= " << integral.pravPriam() << std::endl;
    std::cout << "trapeciy= " << integral.trapeciy() << std::endl;
    std::cout << "Simpson= " << integral.Simpson() << std::endl;
    std::cout << "Newton 31.3" << std::endl;
    std::cout << "Newton " << integral.Newton() << std::endl;
}
