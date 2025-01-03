#pragma once

#include <iostream>

class GameException : public std::exception {

    private:
        const char* message;
        int exception_category;

    public: 

        enum exception_category_levels {
            ABORT = 0,
        };

        GameException(const char* msg, exception_category_levels exc_category) : message(msg), exception_category(exc_category) {};
        const char* what();
        exception_category_levels get_exception_category() const;
};
