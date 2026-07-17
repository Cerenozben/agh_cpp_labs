# Classes

&nbsp;

## **Enum class**

### **Implementation of the enum should be done in Figure.h**

- Create enum class FigureType with type uint8_t
- Define 4 enumerators:
  - SQUARE with value 0
  - RECTANGLE with value 1
  - TRIANGLE with value 2
  - UNKNOWN with value 255

### TestEnumClass at this point should work

&nbsp;

## **Interface class**

### **Implementation of the interface should be done in Figure.h**

- Implement class Figure
- Define two pure virtual functions in class Figure:
  - double area() const;
  - FigureType type() const;

The `area` method returns the area of the figure using the appropriate mathematical formula.
Method type return type of figure as the enumerator defined in the FigureType enum class.

### TestInterface at this point should work

&nbsp;

## **Inheritance**

### **Implementation should be done in Figure.h**

Implement classes Square, Rectangle & Triangle.

#### Class Square

- Implement class Square, which inherits (in a public way) from Class Figure
- The class should provide a default constructor that takes one argument, which means the square side length.
- The class **must** overload all methods defined by the interface class Figure.

#### Class Rectangle

- Implement class Rectangle, which inherits (in a public way) from Class Figure
- The class should provide a default constructor that takes two arguments, which means the rectangle's side lengths.
- The class **must** overload all methods defined by the interface class Figure.

#### Class Triangle

- Implement class Triangle, which inherits (in a public way) from Class Figure
- The class should provide a default constructor that takes two arguments, which means the base of the triangle and its height
- First argument of the default constructor should refer to the base of the triangle.
- The class **must** overload all methods defined by the interface class Figure.

### TestInheritance at this point should work

&nbsp;

## **PrimitiveFactory**

### **Implementation should be done in PrimitiveFactory.h/PrimitiveFactory.cpp**

- Implement class PrimitiveFactory
- Define the method **createFigure** in class PrimitiveFactory, which meets the following rules:
  - The first argument should have the type of enum class FigureType
  - The second argument should have the type of double with a default value of 0.0
  - The third argument should have the type of double with a default value of 0.0
  - The method should return the pointer to the newly created figure with the proper type or nullptr if the figure type is Unknown
- Example usage of class **PrimitiveFactory** and method **createFigure**:
  - `classes::PrimitiveFactory figuresFactory{};`
  - `auto figure1 = figuresFactory.createFigure(classes::FigureType::SQUARE, 2.0);`
  - `auto figure2 = figuresFactory.createFigure(classes::FigureType::RECTANGLE, 2.0, 3.0);`

### TestFactory at this point should work

&nbsp;

## **Iterator**

### **Implementation should be done in FiguresIterator.h**

- Open the link: <https://en.cppreference.com/w/cpp/iterator/iterator> and see the example implementation of an input iterator
- In the block reserved for student code in file FiguresIterator.h, implement the following methods:
  - iterator &operator++()
  - iterator operator++(int)
  - bool operator==(iterator other) const
  - bool operator!=(iterator other) const
  - reference operator\*() const

See the example implementation of the implemented iterator in Classes/test/TestIterator.cpp

### TestIterator at this point should work

## **Products**

This time, there will be no detailed description of the steps to be followed to implement the solution.
Only an API that defines the interface of each of the required classes is provided, as well as a set of unit tests to pass.
We leave the way of implementation to you.
You have to use the external, open-source PicoJson library.
Optionally, you can use the MagicEnum library.
Both of them provide documentation with some representative examples in a README.md file.

Warning: `Do NOT modify any file in Classes/include/Classes/Interfaces`

Look at Classes/include/Classes/Products/ProductsList.hpp

Write classes:

- IndustrialServerRack
- GlassWare
- ExplosiveBarrel
- ElectronicParts
- AstronautsIceCream
- AcetoneBarrel
- TV

Each class should inherit from **IProduct**.
The constructor of each class should take **const std::string &name** and **const float size** as arguments.

ProductDescriptionJson string structure should look like this:

```json
{
  "class": "TV",
  "name": "Sony Bravia 9",
  "size": 20.0,
  "flags": ["KEEP_DRY", "ESD_SENSITIVE"]
}
```

See _Classes/include/Classes/Interfaces/IProduct.hpp_ to learn more about what methods should be overridden.
See _Classes/test/TestClassesProductFactory.cpp_ to check which flags each product has.

**Hint:** Every product implementation requires using similar or the same methods; consider introducing an intermediate class between a final override and IProduct.

### TestClassesProducts at this point should work

## Products Factory

Analyze the implementation of the ProductFactory class. This class provides the createProduct method:

```cpp
classesInterface::IProductPtr createProduct(const std::string &className, const std::string &name, const float size) const
```

This method realizes the factory pattern - creation of Product based on provided arguments.

### TestClassesProductFactory at this point should work - without any changes from your side
