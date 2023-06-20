#pragma once

#include<string>
#include<iostream>
#include<algorithm>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
public:
    DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Reversed : public DecoratedText {
public:
    Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::string copy(data);
        std::reverse(copy.begin(), copy.end());
        text_->render(copy);
    }
};

class Paragraph : public DecoratedText {
public:
    Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Header : public DecoratedText {
    unsigned _level;
public:
    Header(Text* text, unsigned level) : DecoratedText(text) { _level = level; }
    void render(const std::string& data) const override {
        std::cout << "<h" << std::to_string(_level) << ">";
        text_->render(data);
        std::cout << "</h" << std::to_string(_level) << ">";
    }
};

class Link : public DecoratedText {
public:
    Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& data, const std::string& url) const {
        std::cout << "<a href = " << url << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};