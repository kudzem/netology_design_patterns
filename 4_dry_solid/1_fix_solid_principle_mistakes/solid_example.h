#include <fstream>

class Formatter
{
public:
    virtual ~Formatter() = default;
    virtual std::string format(const std::string& data) const = 0;
};

class FormatterHTML : public Formatter {
    virtual std::string format(const std::string& data)  const override {
        return "<html>" + data + "<html/>";
    };
};

class FormatterText : public Formatter {
    virtual std::string format(const std::string& data)  const override {
        return data;
    };
};

class FormatterJSON : public Formatter {
    virtual std::string format(const std::string& data)  const override {
        return "{ \"data\": \"" + data + "\"}";
    };
};


std::ostream& formatAndPrint(std::ostream& output, const std::string& data, const Formatter& formatter)
{
    output << formatter.format(data);
    return output;
}