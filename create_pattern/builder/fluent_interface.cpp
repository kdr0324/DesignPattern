#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct HtmlElement
{
    string name;
    string text;
    vector<HtmlElement> elements;

    HtmlElement() {}
    HtmlElement(const string &name, const string &text)
        : name(name), text(text) {}
    
    string str(int indent = 0) const
    {
        ostringstream oss;
        oss << "<" << name << ">" << text << "";
        for(auto e : elements)
            oss << "<" << e.name << ">" << e.text << "</" << e.name << ">";
        oss << "</" << name <<">";
        return oss.str();
    }
};

struct HtmlBuilder
{
    HtmlElement root;
    HtmlBuilder(string root_name) { root.name = root_name; }

    HtmlBuilder& add_child(string child_name, string child_text)
    {
        HtmlElement e (child_name, child_text);
        root.elements.emplace_back(e);

        return *this;
    }

    string str() { return root.str(); }
};

int main()
{
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << endl;
    return 0;
}