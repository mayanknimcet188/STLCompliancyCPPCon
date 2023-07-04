#include <iostream>
#include <vector>
#include <iterator>

template <typename InputIterator, typename OutputIterator, typename Predicate>
OutputIterator find_all(InputIterator first, InputIterator last, OutputIterator output, Predicate pred)
{
    while (first != last)
    {
        if (pred(*first))
        {
            *output = first;
            ++output;
        }
        ++first;
    }

    return output;
}

int main()
{
    using my_container = std::vector<int>;
    my_container values{3, 4, 5, 4, 5, 6, 5, 8};
    std::vector<my_container::iterator> matches;
    find_all(begin(values), end(values), std::back_inserter(matches), [](int i)
             { return i == 5; });

    std::cout << "Found " << matches.size() << " matches: " << std::endl;
    for (const auto &it : matches)
    {
        std::cout << *it << " at position " << (it - cbegin(values)) << std::endl;
    }
    return 0;
}