#include "stdafx.h"
#include "Syntax.h"

Syntax::Syntax(uint32_t startIndex, uint32_t length)
    : m_startIndex(startIndex), m_length(length)
{
}
Syntax::~Syntax()
{
}

uint32_t Syntax::startIndex() const
{
    return this->m_startIndex;
}
uint32_t Syntax::length() const
{
    return this->m_length;
}
uint32_t Syntax::endIndex() const
{
    return this->m_startIndex + this->m_length;
}

std::string Syntax::stringify() const
{
    thread_local static std::stringstream buffer;
    buffer.clear();
    this->stringify(buffer);
    return buffer.str();
}
void Syntax::stringify(std::stringstream &stream) const
{
    stream << "[" << this->startIndex() << ", " << this->endIndex() << ") ";
    this->repr(stream);
}

std::stringstream &operator<<(std::stringstream &stream, const Syntax &syntax)
{
    syntax.repr(stream);
}
std::ostream &operator<<(std::ostream &stream, const Syntax &syntax)
{
    thread_local static std::stringstream sstream;
    sstream.clear();
    sstream << syntax;
    stream << sstream.str();
}
