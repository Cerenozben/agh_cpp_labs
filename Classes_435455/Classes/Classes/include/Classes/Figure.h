#pragma once

#include <cstdint>
namespace classes
{
// student code begin
enum class FigureType : uint8_t
{
    SQUARE = 0,
    RECTANGLE = 1,
    TRIANGLE = 2,
    UNKNOWN = 255
};
class Figure
{
public:
    virtual ~Figure() = default;

    Figure() = default;
    Figure(const Figure &) = default;
    Figure(Figure &&) = delete;
    Figure &operator=(const Figure &) = default;
    Figure &operator=(Figure &&) = default;

    virtual double area() const = 0;
    virtual FigureType type() const = 0;
};
class Square : public Figure
{
private:
    double side_;

public:
    explicit Square(double s = 0.0) : side_(s) {}
    double area() const override { return side_ * side_; }
    FigureType type() const override { return FigureType::SQUARE; }
};
class Rectangle : public Figure
{
private:
    double width_;
    double height_;

public:
    explicit Rectangle(double w = 0.0, double h = 0.0) : width_(w), height_(h) {}
    double area() const override { return width_ * height_; }
    FigureType type() const override { return FigureType::RECTANGLE; }
};
class Triangle : public Figure
{
private:
    double base_;
    double height_;

public:
    explicit Triangle(double b = 0.0, double h = 0.0) : base_(b), height_(h) {}
    double area() const override { return (base_ * height_) / 2; }
    FigureType type() const override { return FigureType::TRIANGLE; }
};
// student code end

}  // namespace classes
