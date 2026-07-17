#pragma once

#include "Classes/Figure.h"

namespace classes
{
// student code begin
class PrimitiveFactory
{
public:
    Figure *createFigure(FigureType type, double arg1 = 0.0, double arg2 = 0.0);
};
// student code end

}  // namespace classes
