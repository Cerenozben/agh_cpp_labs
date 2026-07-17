# Structures

&nbsp;

## **Variant**

---

- About Variant:
  - <https://en.cppreference.com/w/cpp/utility/variant>
  - <https://en.cppreference.com/w/cpp/utility/variant/get>
- About visitor:
  - <https://refactoring.guru/design-patterns/visitor>
  - <https://en.cppreference.com/w/cpp/utility/variant/visit>
  - <https://www.cppstories.com/2018/09/visit-variants/>

---

### Make PrintVisitor Structure

- [ ] declare alias "PrintVariant" for std::variant<bool, int, float>
- [ ] declare & define PrintVisitor (similar to "struct VisitPackage" from <https://www.cppstories.com/2018/09/visit-variants/>)
- [ ] print "bool" for bool
- [ ] print "int" for int
- [ ] print "float" for float

### TestPrintVisitor at this point should work

---

### Make ToStringVisitor Structure

- [ ] declare alias "ToStringVariant" for std::variant<bool, int, double, float>
- [ ] declare & define ToStringVisitor - std::visit should return std::string
- [ ] return bool as a string as alphanumerical
- [ ] return int in hex
- [ ] return float/double "normally"

### TestToStringVisitor at this point should work

---

## **Dictionary**

---

### Constructors

- [ ] Create "Dictionary" structure
- [ ] declare and define "verbose" constructors + destructor
- [ ] look here: <https://en.cppreference.com/w/cpp/language/rule_of_three> - explanation about rule 0/3/5
- [ ] each of constructors should be functional
- [ ] default constructor should print on console "default constructor"
- [ ] copy constructor should print on console "copy constructor"
- [ ] move constructor should print on console "move constructor"
- [ ] copy assignment should print on console "copy assignment"
- [ ] move assignment should print on console "move assignment"
- [ ] destructor should print on console "destructor"

### TestConstructors at this point should work

---

### Add Field

- [ ] declare alias "CustomVariant" for std::variant<int, float, std::string>
- [ ] declare alias "DictionaryContainer" for map of string - CustomVariant
- [ ] add to Dictionary "items\_" field
- [ ] "items\_" field should be DictionaryContainer type
- [ ] make sure that constructors are still functional

### TestField at this point should work

---

### Add Initializer List constructor

- [ ] look at: <https://en.cppreference.com/w/cpp/utility/initializer_list>
- [ ] add to Dictionary Initializer List constructor
- [ ] "items\_" field should be initialized by this constructor similar to python dict

### TestInitializerList at this point should work

---

### Add array operator

- [ ] add to Dictionary array operator with string as a key
- [ ] operator should allow to edit corresponding value
- [ ] operator should allow to add new values

### TestArrayOperator at this point should work

---

### Add pop method

- [ ] add to Dictionary pop method
- [ ] pop method Removes the element with the specified key

### TestPop at this point should work

---

### Add values method

- [ ] add to Dictionary values method
- [ ] values method returns vector of values

### TestValues at this point should work

---

### Add keys method

- [ ] add to Dictionary keys method
- [ ] keys method returns vector of keys

### TestKeys at this point should work

---

### objects counter

- [ ] add to Dictionary class objects static "cnt\_" field
- [ ] add to Dictionary getObjCounter static method
- [ ] cnt\_ field should represent currently existing object of class Dictionary
- [ ] modify constructors & destructor accordingly

### TestObjectsCounter at this point should work

---

### const

- [ ] add to Dictionary const array operator with string as a key and without edit functionality
- [ ] modify values and keys methods to also be const

### TestConst at this point should work

---

### concatenation

- [ ] overload + operator for Dictionary + Dictionary
- [ ] overload += operator for Dictionary
- [ ] addition should merge two dictionaries

### TestConcatenation at this point should work

---

### toJson

- [ ] add toJson const method
- [ ] method should return string containing serialized dictionary in json format

### TestToJson at this point should work

---
