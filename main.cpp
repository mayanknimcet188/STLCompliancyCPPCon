#include <iostream>
#include <vector>
template <typename T, typename Predicate>
std::vector<typename std::vector<T>::iterator> find_all(std::vector<T> &values, Predicate pred)
{
    std::vector<typename std::vector<T>::iterator> matches;
    for (auto iter = begin(values); iter != end(values); ++iter)
    {
        if (pred(*iter))
            matches.push_back(iter);
    }
    return matches;
}

int main()
{
    using my_container = std::vector<int>;
    my_container values{3, 4, 5, 4, 5, 6, 5, 8};
    auto matches = find_all(values, [](int i)
                            { return i == 5; });

    std::cout << "Found " << matches.size() << " matches: " << std::endl;
    for (const auto &it : matches)
    {
        std::cout << *it << " at position " << (it - cbegin(values)) << std::endl;
    }
    return 0;
}