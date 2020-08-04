#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

struct HtmlBuilder;

struct HtmlElement
{
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const string &name, const string &text)
        : name(name),
          text(text)
    {
    }

    string str(int indent = 0) const
    {
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0)
            oss << string(indent_size * (indent + 1), ' ') << text << endl;

        for (const auto &e : elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    static unique_ptr<HtmlBuilder> build(string root_name)
    {
        return make_unique<HtmlBuilder>(root_name);
    }
};

struct HtmlBuilder
{
    HtmlBuilder(string root_name)
    {
        root.name = root_name;
    }

    // 공백 상태에서 시작한다.
    HtmlBuilder &add_child(string child_name, string child_text)
    {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    // 포인터에 기반한다.
    HtmlBuilder *add_child_2(string child_name, string child_text)
    {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return this;
    }

    string str()
    {
        return root.str();
    }

    operator HtmlElement() const { return root; }
    HtmlElement root;
};

int main()
{
    auto builder = HtmlElement::build("ul");
    builder
        ->add_child_2("li", "hello")
        ->add_child_2("li", "world");

    cout << builder->str() << endl;
    return 0;
}