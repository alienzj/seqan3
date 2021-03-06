#include <seqan3/core/algorithm/pipeable_config_element.hpp>
#include <seqan3/core/configuration/configuration.hpp>
#include <seqan3/core/debug_stream.hpp>

// Initial setup used in the actual example:
enum struct my_id : int
{
    bar_id,
    foo_id
};

struct bar : public seqan3::pipeable_config_element<bar>
{
public:
    float value{};

    bar() = default;
    bar(bar const &) = default;
    bar(bar &&) = default;
    bar & operator=(bar const &) = default;
    bar & operator=(bar &&) = default;
    ~bar() = default;

    bar(float v) : value{v}
    {}

    static constexpr my_id id{my_id::bar_id};
};

template <typename t>
class foo : public seqan3::pipeable_config_element<foo<t>>
{
public:
    t value{};

    foo() = default;
    foo(foo const &) = default;
    foo(foo &&) = default;
    foo & operator=(foo const &) = default;
    foo & operator=(foo &&) = default;
    ~foo() = default;

    foo(t v) : value{std::move(v)}
    {}

    static constexpr my_id id{my_id::foo_id};
};

template <typename t>
foo(t) -> foo<t>;

int main()
{
    seqan3::configuration my_cfg{foo{1}}; // Only foo<int> is present.
    seqan3::debug_stream << my_cfg.get_or(foo{std::string{"hello"}}).value << '\n';  // finds foo<int> -> prints: 1
    seqan3::debug_stream << my_cfg.get_or(bar{2.4}).value << '\n';  // bar not present -> prints: 2.4
}
