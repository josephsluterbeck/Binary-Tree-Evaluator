#ifndef NOT_FOUND_EXCEPTION_H
#define NOT_FOUND_EXCEPTION_H

#include <stdexcept>
#include <string>

class NotFoundException : public std::logic_error {
public:
    explicit NotFoundException(const std::string& message = "")
        : std::logic_error("Not Found Exception: " + message) {}
};

#endif
