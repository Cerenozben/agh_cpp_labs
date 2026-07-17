#pragma once

#include <iterator>
#include <vector>

#include "Figure.h"

namespace classes
{
using FigureWithDescription = std::pair<classes::Figure *, std::string>;

class FiguresIterator
{
public:
    // NOLINTNEXTLINE
    class iterator
    {
        std::vector<FigureWithDescription>::iterator it_;

    public:
        iterator(const iterator &) = default;
        iterator(iterator &&) = default;
        iterator &operator=(const iterator &) = default;
        iterator &operator=(iterator &&) = default;
        explicit iterator(const std::vector<FigureWithDescription>::iterator it) : it_(it) {}

        // NOLINTBEGIN
        // iterator traits
        using iterator_category = std::input_iterator_tag;  // iterator_category
        using value_type = FigureWithDescription;           // value_type
        using difference_type = size_t;                     // difference_type
        using pointer = const FigureWithDescription *;      // pointer
        using reference = FigureWithDescription &;          // reference
        // NOLINTEND

        // student code begin
        iterator &operator++()
        {
            ++it_;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp = *this;
            ++it_;
            return temp;
        }
        bool operator==(iterator other) const { return it_ == other.it_; }
        bool operator!=(iterator other) const { return it_ != other.it_; }
        reference operator*() const { return *it_; }
        // student code end
    };

    iterator begin() { return iterator(figures_.begin()); }
    iterator end() { return iterator(figures_.end()); }

private:
    std::vector<FigureWithDescription> figures_{};

public:
    FiguresIterator() = default;
    FiguresIterator(const FiguresIterator &) = default;
    FiguresIterator(FiguresIterator &&) = delete;
    FiguresIterator &operator=(const FiguresIterator &) = default;
    FiguresIterator &operator=(FiguresIterator &&) = delete;
    ~FiguresIterator() = default;

    void addFigure(classes::Figure *figure, const std::string &description) { figures_.emplace_back(figure, description); }
};

}  // namespace classes
