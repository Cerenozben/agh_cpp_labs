#pragma once
#include <string>
#include <vector>

namespace gdbLab
{
void getZarr(std::string str, std::vector<size_t> &z);

std::vector<size_t> search(const std::string &text, const std::string &pattern);

}  // namespace gdbLab
