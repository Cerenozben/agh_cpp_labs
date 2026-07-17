#include <Classes/PrimitiveFactory.h>

namespace classes
{
// student code begin
Figure *PrimitiveFactory::createFigure(FigureType type, double arg1, double arg2)  // NOLINT
{
    switch (type)
    {
        case FigureType::SQUARE:
            return new Square(arg1);  // NOLINT
        case FigureType::RECTANGLE:
            return new Rectangle(arg1, arg2);  // NOLINT
        case FigureType::TRIANGLE:
            return new Triangle(arg1, arg2);  // NOLINT
        case FigureType::UNKNOWN:
        default:
            return nullptr;
    }
}
// student code end

}  // namespace classes