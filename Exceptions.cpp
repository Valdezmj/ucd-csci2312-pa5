//
// Created by Michael Valdez on 12/14/15.
//
#include "Exceptions.h"
namespace Gaming {
    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width,
                                                               unsigned height) : DimensionEx(width, height, minWidth,
                                                                                              minHeight) {
        setName("InsufficientDimensionsEx");
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
        __exp_width = expWidth;
        __exp_height = expHeight;
        __width = width;
        __height = height;
    }

    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        ex.__print_args(os);
        return os;
    }

    unsigned DimensionEx::getExpWidth() const {
        return __exp_width;
    }

    unsigned DimensionEx::getExpHeight() const {
        return __exp_height;
    }

    unsigned DimensionEx::getWidth() const {
        return __width;
    }

    unsigned DimensionEx::getHeight() const {
        return __height;
    }

    void GamingException::setName(std::string name) {
        __name = name;
    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
        os << "---Insufficient dimensions---\n";
        os << "Expected width: " << this->getExpWidth() << std::endl;
        os << "Expected height: " << this->getExpHeight() << std::endl;
        os << "Acceptable width: " << this->getWidth() << std::endl;
        os << "Acceptable width: " << this->getHeight() << std::endl;
        os << "Suggest fixing the dimensions being passed in your constructor\n";
    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const {
        os << "---Out of bounds dimensions---\n";
        os << "Width: " << this->getExpWidth() << std::endl;
        os << "Height: " << this->getExpHeight() << std::endl;
        os << "Max width: " << this->getWidth() << std::endl;
        os << "Max width: " << this->getHeight() << std::endl;
        os << "Suggest making sure you pass in correct bounds\n";
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) :
            DimensionEx(width, height, maxWidth, maxHeight) {
        setName("OutOfBoundsEx");
    }
}