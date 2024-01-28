#include <string>
#include <iostream>


class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const  {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        auto tmp = data;
        std::reverse(tmp.begin(), tmp.end());
        text_->render(tmp);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text, const std::string& url) : DecoratedText(text), url_(url) {}
    void render(const std::string& data) const {
        std::cout << "<a href=" << url_ << ">";
        text_->render(data);
        std::cout << "</a>";
    }
private:
    std::string url_;
};


int main() {

    {
        auto text_block = new ItalicText(new BoldText(new Text()));
        text_block->render("Hello world");
        delete text_block;
    }

    std::cout << std::endl;

    {
        auto text_block = new Link(new Reversed(new Paragraph(new Text())), "www.netology.ru");
        text_block->render("Hello world");
        delete text_block;
    }

}
